#!/bin/sh
# Connects Beszel to Pocket ID.
# Safe to run again: it skips what is already in place.
set -eu

POCKET_ID=http://pocket-id:1411
BESZEL=http://beszel:8090
PUBLIC_POCKET_ID=https://auth.icde.nl
REDIRECT=https://monitor.icde.nl/api/oauth2-redirect
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

# Pocket ID: register Beszel as a client, with the secret from .env.
status=$(json --output /dev/null --write-out '%{http_code}' \
	--header "X-API-KEY: $POCKET_ID_API_KEY" --request POST "$POCKET_ID/api/oidc/clients" \
	--data "{\"id\":\"beszel\",\"name\":\"Beszel\",\"callbackURLs\":[\"$REDIRECT\"]}")
case "$status" in
201)
	json --fail --output /dev/null \
		--header "X-API-KEY: $POCKET_ID_API_KEY" \
		--request POST "$POCKET_ID/api/oidc/clients/beszel/secrets" \
		--data "{\"secret\":\"$BESZEL_OIDC_SECRET\"}"
	echo 'Pocket ID: client beszel made.'
	;;
409)
	echo 'Pocket ID: client beszel is already there.'
	;;
*)
	echo "Pocket ID: making the client failed with status $status." >&2
	exit 1
	;;
esac

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
