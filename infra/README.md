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

## Server

The prototype runs at <https://icde.nl>, on a server with Debian and Docker.
Caddy gets the certificates itself, so the server runs no other web server or proxy.
doco-cd on the server deploys this repository.
After a push to `main`, the workflow `.github/workflows/deploy.yml` calls the webhook of doco-cd,
and doco-cd runs the new version within seconds.
doco-cd also asks GitHub once per hour, in case a webhook call gets lost.

The workflow signs the call with the secret `WEBHOOK_SECRET`.
The secret is in the GitHub environment `production`, which only the branch `main` may use.
GitHub's own webhook setting is not used: it also calls for pushes to other branches, and doco-cd
would then deploy a branch that nobody reviewed.

| File | Purpose |
| --- | --- |
| `../.doco-cd.yml` | Tells doco-cd which Compose files to run. doco-cd only reads it in the root |
| `../compose.yaml` | The stack, the same on a laptop and on the server |
| `../compose.override.yaml` | Laptop only: opens port 8080 |
| `compose.server.yaml` | Server only: opens ports 80 and 443 and sets the domain name |
| `caddy/deploy.caddy` | Server only: passes the webhook path on to doco-cd |
| `doco-cd/compose.yaml` | doco-cd itself. Started once by hand on the server |
| `../.github/workflows/deploy.yml` | Calls the webhook of doco-cd after a push |

Start doco-cd before the first deployment: it creates the network `edge` that the web server joins.
Put `WEBHOOK_SECRET=<value>` in a file `.env` next to `doco-cd/compose.yaml` on the server, and
store the same value as the secret `WEBHOOK_SECRET` in the GitHub environment `production`.

Paths in `compose.server.yaml` are relative to the repository root, because Compose resolves
them against the first file it loads.

Do not keep data in a relative bind mount such as `./data`.
doco-cd runs every commit from a fresh copy of the repository, so that data is lost.
Use a named volume or an absolute path on the server.
