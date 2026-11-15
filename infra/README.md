# Infrastructure

Files that only the server needs.
`docs/uitrol.md` explains the deployment, with diagrams.
The stack itself is `compose.yaml` in the repository root.
It now holds only the web server with a placeholder page.
The application server, document server and database join when they exist.

## Run on a laptop

Run this in the repository root:

```sh
docker compose up -d
```

Open <http://localhost:8080>.
Compose loads `compose.yaml` and `compose.override.yaml`.

## Files

| File | Purpose |
| --- | --- |
| `../compose.yaml` | The stack, the same on a laptop and on the server |
| `../compose.override.yaml` | Laptop only: opens port 8080 |
| `compose.server.yaml` | Server only: connects the web server to the proxy |
| `../.doco-cd.yml` | doco-cd settings for production (`main`, <https://icde.nl>) |
| `../.doco-cd.dev.yml` | doco-cd settings for development (`develop`, <https://dev.icde.nl>) |
| `edge/compose.yaml` | The fixed part of the server: the proxy and doco-cd |
| `edge/Caddyfile` | Which domain name the proxy passes on to which container |
| `../.github/workflows/deploy.yml` | Calls the webhook of doco-cd after a push |

doco-cd only reads its settings files in the repository root.
Paths in `compose.server.yaml` are relative to the repository root, because Compose resolves
them against the first file it loads.

Do not keep data in a relative bind mount such as `./data`.
doco-cd runs every commit from a fresh copy of the repository, so that data is lost.
Use a named volume or an absolute path on the server.

## Set up a server

The server needs Debian with Docker Engine and the Compose plugin.
The DNS records in `docs/uitrol.md` must point to it.

1. Copy `edge/compose.yaml` and `edge/Caddyfile` to `/srv/edge/` on the server.
2. Create `/srv/edge/.env` with one line, `WEBHOOK_SECRET=<value>`, readable only by root.
   Generate the value with `openssl rand -hex 32`.
3. Store the same value as the secret `WEBHOOK_SECRET` in the GitHub environments `production`
   and `development`.
4. Run `docker compose up -d` in `/srv/edge/`.

doco-cd then deploys both environments on its own.
Repeat steps 1 and 4 after a change in `edge/`, because doco-cd does not deploy that directory.
