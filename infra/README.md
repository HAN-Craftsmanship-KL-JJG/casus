# Infrastructure

Files that only the server needs.
`docs/uitrol.md` explains the deployment, with diagrams.

## Run on a laptop

Run this in the repository root, then open <http://localhost:8080>:

```sh
docker compose up -d
```

## Files

| File | Purpose |
| --- | --- |
| `../compose.yaml` | The stack, the same on a laptop and on the server |
| `../compose.override.yaml` | Laptop only: opens port 8080 |
| `compose.server.yaml` | Server only: connects the web server to the proxy |
| `../.doco-cd.yml` | doco-cd settings for production |
| `../.doco-cd.dev.yml` | doco-cd settings for development |
| `edge/` | The fixed part of the server: the proxy and doco-cd |
| `../.github/workflows/deploy.yml` | Tells doco-cd about a push |

Do not keep data in a relative bind mount such as `./data`.
doco-cd runs every commit from a fresh copy of the repository, so that data is lost.
Use a named volume.

## Set up a server

The server needs Docker Engine with the Compose plugin, and the DNS records from
`docs/uitrol.md`.

1. Copy the files in `edge/` to `/srv/edge/` on the server.
2. Create `/srv/edge/.env` with one line, `WEBHOOK_SECRET=<value>`, readable only by root.
   Generate the value with `openssl rand -hex 32`.
3. Store the same value as the secret `WEBHOOK_SECRET` in the GitHub environments `production`
   and `development`.
4. Run `docker compose up -d` in `/srv/edge/`.

doco-cd then deploys both environments.
Repeat steps 1 and 4 after a change in `edge/`.
