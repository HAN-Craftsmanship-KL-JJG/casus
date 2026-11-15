# Server

The server that runs ICDE, and the files that belong to it.
[Deployment](deployment.md) describes how a change reaches it.

## Files

| File | Purpose |
| --- | --- |
| `compose.yaml` | The stack on a laptop |
| `compose.server.yaml` | The stack on the server, once per environment |
| `db/schema.sql` | The tables |
| `.doco-cd.prd.yml` | doco-cd settings for `main`: production and `infra` |
| `.doco-cd.dev.yml` | doco-cd settings for `develop`: development |
| `infra/compose.yaml` | Proxy and doco-cd |
| `infra/Caddyfile` | Which name the proxy passes to which container |
| `.github/workflows/deploy.yml` | Builds the images and tells doco-cd |

Three things to know:

- PostgreSQL runs `db/schema.sql` only in an empty database.
  After a change, delete the database: `docker compose down --volumes` on a laptop, the volumes
  `icde-prd_db-data` and `icde-dev_db-data` on the server.
- The database password is in the Compose files.
  That is accepted while the database holds no real data.
- Store data in a named volume, never in a relative bind mount such as `./data`.
  doco-cd runs each commit from a fresh copy of the repository, so that data is lost.

## The server

| | |
| --- | --- |
| Provider | mijn.host, VPS size S: 1 core, 4 GB memory, 20 GB disk |
| Operating system | Debian 13 |
| Clock | UTC |

| Setting | Value | File on the server |
| --- | --- | --- |
| SSH | Keys only, no passwords | `/etc/ssh/sshd_config.d/00-keys-only.conf` |
| Docker | Engine and Compose from Docker's repository | `/etc/apt/sources.list.d/` |
| Container logs | At most 3 files of 10 MB per container | `/etc/docker/daemon.json` |
| IPv6 | On for containers | `/etc/docker/daemon.json` |
| Updates | Daily, for Debian and Docker | `/etc/apt/apt.conf.d/52unattended-upgrades-icde` |
| Restart | At 04:00 UTC when an update needs it | The same file |
| Secrets | Readable by root only | `/srv/infra/.env` |

A restart or a Docker update takes the sites down for about a minute.

## Secrets

`/srv/infra/.env` holds one value.
Make it with `openssl rand -hex 32`.
doco-cd reads the file when it deploys `infra`.

| Name | Purpose |
| --- | --- |
| `WEBHOOK_SECRET` | Signs the message from GitHub to doco-cd |

## Set up a new server

Only the first start is by hand.
After that, doco-cd keeps the application and `infra` up to date.

1. Install Debian 13 and Docker Engine with the Compose plugin.
2. Apply the settings from the table under [The server](#the-server).
3. Point the DNS records from [Deployment](deployment.md#dns) to the server.
4. Copy the directory `infra/` to `/srv/infra/` on the server.
5. Make `/srv/infra/.env` with the value, readable by root only.
6. Run `docker compose up -d` in `/srv/infra/`.
7. Store the value of `WEBHOOK_SECRET` as a secret in the GitHub environments `production` and
   `development`.

For another domain, replace `icde.nl` in `infra/Caddyfile`, `infra/compose.yaml` and
`.github/workflows/deploy.yml`.
