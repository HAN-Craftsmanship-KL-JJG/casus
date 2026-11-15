# Infrastructure

Files that only the server needs.
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

The prototype runs at <https://icde.nl>.
doco-cd on the server watches this repository.
When a commit on the watched branch changes the stack, doco-cd runs the new version.

| File | Purpose |
| --- | --- |
| `../.doco-cd.yml` | Tells doco-cd which Compose files to run. doco-cd only reads it in the root |
| `../compose.yaml` | The stack, the same on a laptop and on the server |
| `../compose.override.yaml` | Laptop only: opens port 8080 |
| `compose.server.yaml` | Server only: connects the web server to Traefik |
| `doco-cd/compose.yaml` | doco-cd itself. Started once by hand on the server |

Paths in `compose.server.yaml` are relative to the repository root, because Compose resolves
them against the first file it loads.

Do not keep data in a relative bind mount such as `./data`.
doco-cd runs every commit from a fresh copy of the repository, so that data is lost.
Use a named volume or an absolute path on the server.
