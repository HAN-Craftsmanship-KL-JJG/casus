#!/bin/sh
# Connects Beszel and pgAdmin to Pocket ID.
# Safe to run again: it skips what is already in place.
set -eu

POCKET_ID=http://pocket-id:1411
BESZEL=http://beszel:8090
PUBLIC_POCKET_ID=https://auth.icde.nl
BESZEL_REDIRECT=https://monitor.icde.nl/api/oauth2-redirect
PGADMIN_REDIRECT=https://db.icde.nl/oauth2/authorize
SOCKET=/beszel_socket/beszel.sock

# Reads one text field from a JSON answer.
field() {
	sed -n "s/.*\"$1\":\"\([^\"]*\)\".*/\1/p"
}

json() {
	curl --silent --show-error --header 'Content-Type: application/json' "$@"
}

echo 'Waiting for Pocket ID and Beszel.'
until curl --silent --fail --output /dev/null "$POCKET_ID/healthz" &&
	curl --silent --fail --output /dev/null "$BESZEL/api/health"
do
	sleep 2
done

# Pocket ID: register a client, with its secret from .env.
# Arguments: id, name, callback address, secret.
client() {
	status=$(json --output /dev/null --write-out '%{http_code}' \
		--header "X-API-KEY: $POCKET_ID_API_KEY" --request POST "$POCKET_ID/api/oidc/clients" \
		--data "{\"id\":\"$1\",\"name\":\"$2\",\"callbackURLs\":[\"$3\"]}")
	case "$status" in
	201)
		json --fail --output /dev/null \
			--header "X-API-KEY: $POCKET_ID_API_KEY" \
			--request POST "$POCKET_ID/api/oidc/clients/$1/secrets" \
			--data "{\"secret\":\"$4\"}"
		echo "Pocket ID: client $1 made."
		;;
	409)
		echo "Pocket ID: client $1 is already there."
		;;
	*)
		echo "Pocket ID: making the client $1 failed with status $status." >&2
		exit 1
		;;
	esac
}

client beszel Beszel "$BESZEL_REDIRECT" "$BESZEL_OIDC_SECRET"
client pgadmin pgAdmin "$PGADMIN_REDIRECT" "$PGADMIN_OIDC_SECRET"

# Pocket ID: mark every email address as verified.
# Beszel refuses an unverified address, and there is no mail server to verify one.
users=$(json --fail --header "X-API-KEY: $POCKET_ID_API_KEY" "$POCKET_ID/api/users")
for id in $(echo "$users" | grep -o '"id":"[^"]*","username"' | cut -d '"' -f 4); do
	user=$(json --fail --header "X-API-KEY: $POCKET_ID_API_KEY" "$POCKET_ID/api/users/$id")
	case "$user" in
	*'"email":null'*) ;;
	*'"emailVerified":false'*)
		echo "$user" | sed 's/"emailVerified":false/"emailVerified":true/' |
			json --fail --output /dev/null --header "X-API-KEY: $POCKET_ID_API_KEY" \
				--request PUT "$POCKET_ID/api/users/$id" --data @-
		echo "Pocket ID: email address of account $id marked as verified."
		;;
	esac
done

# Beszel: log in as the admin, who is also the superuser.
login="{\"identity\":\"$BESZEL_ADMIN_EMAIL\",\"password\":\"$BESZEL_ADMIN_PASSWORD\"}"
superuser=$(json --fail --request POST --data "$login" \
	"$BESZEL/api/collections/_superusers/auth-with-password" | field token)
admin=$(json --fail --request POST --data "$login" \
	"$BESZEL/api/collections/users/auth-with-password")
token=$(echo "$admin" | field token)
admin_id=$(echo "$admin" | field id)

# Beszel: add Pocket ID as the login provider.
provider="{\"name\":\"oidc\",\"displayName\":\"Pocket ID\",\"pkce\":true,
	\"clientId\":\"beszel\",\"clientSecret\":\"$BESZEL_OIDC_SECRET\",
	\"authURL\":\"$PUBLIC_POCKET_ID/authorize\",
	\"tokenURL\":\"$PUBLIC_POCKET_ID/api/oidc/token\",
	\"userInfoURL\":\"$PUBLIC_POCKET_ID/api/oidc/userinfo\"}"
json --fail --output /dev/null --header "Authorization: $superuser" \
	--request PATCH "$BESZEL/api/collections/users" \
	--data "{\"oauth2\":{\"enabled\":true,\"providers\":[$provider]}}"
echo 'Beszel: login through Pocket ID is set.'

# Beszel: give its public key to the agent.
json --fail --header "Authorization: $token" "$BESZEL/api/beszel/getkey" | field key >/key/hub.pub
echo 'Beszel: key for the agent written.'

# Beszel: add this server as a system, once.
systems=$(json --fail --header "Authorization: $token" \
	"$BESZEL/api/collections/systems/records?fields=host")
case "$systems" in
*"$SOCKET"*)
	echo 'Beszel: the server is already a system.'
	;;
*)
	json --fail --output /dev/null --header "Authorization: $token" \
		--request POST "$BESZEL/api/collections/systems/records" \
		--data "{\"name\":\"icde.nl\",\"host\":\"$SOCKET\",\"port\":\"45876\",\"users\":[\"$admin_id\"]}"
	echo 'Beszel: the server is added as a system.'
	;;
esac
