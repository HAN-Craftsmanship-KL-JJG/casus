# Infrastructure

How the server runs the prototype.
`docs/uitrol.md` explains the deployment, with diagrams.

The root `README.md` explains how to start the prototype on a laptop.

## Files

| File | Purpose |
| --- | --- |
| `../compose.yaml` | The stack on a laptop: builds the images and opens port 8080 |
| `../compose.server.yaml` | The stack on the server: pulls the images and joins the proxy |
| `../db/schema.sql` | The tables. PostgreSQL runs it once, in an empty database |
| `../.doco-cd.yml` | doco-cd settings for production |
| `../.doco-cd.dev.yml` | doco-cd settings for development |
| `edge/` | The fixed part of the server: the proxy and doco-cd |
| `../.github/workflows/deploy.yml` | Builds the images and tells doco-cd about a push |

The server never builds an image.
The workflow pushes each image to `ghcr.io` with the branch as tag, and the server pulls it.

After a change in `db/schema.sql`, delete the database so PostgreSQL runs the file again:
`docker compose down --volumes` on a laptop.
On the server, remove the volumes `icde_db-data` and `icde-dev_db-data` by hand.

The database password is in the Compose files.
That is acceptable while the database holds no real data: it has no open port, and only the
application server reaches it.

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
