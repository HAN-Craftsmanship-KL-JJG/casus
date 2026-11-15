# ICDE: Integrated Course Design Environment

Onderwijs ontwerpen gebeurt nu in losse Word- en Excel-bestanden, die uit de pas lopen.
ICDE bewaart leeruitkomsten, rubrics, toetsen en lessen als data, controleert ze op consistentie
en genereert er documenten uit.

Dit is de casus van ons team voor de HAN-module OOSE Deeltijd 2026/2027.

## Architectuur

ICDE bestaat uit vier containers, die op één server in twee omgevingen draaien.

![De containers van ICDE en de server eromheen](docs/diagrams/overzicht.svg)

| Onderdeel                 | Map               | Techniek                   |
| ------------------------- | ----------------- | -------------------------- |
| Webserver met de frontend | `web/`            | Caddy, React, TypeScript   |
| Applicatieserver          | `api/`            | C++, Drogon                |
| Documentserver            | `documentserver/` | C++, Drogon, Pandoc, Typst |
| Database                  | `db/`             | PostgreSQL                 |

## Hosting

ICDE draait op <https://icde.nl>.
Een merge naar een van deze branches komt vanzelf op de server.

| Omgeving           | Adres                                        | Branch    |
| ------------------ | -------------------------------------------- | --------- |
| Productie (prd)    | <https://icde.nl>, ook <https://prd.icde.nl> | `main`    |
| Ontwikkeling (dev) | <https://dev.icde.nl>                        | `develop` |

## Start development

Installeer Docker Desktop, draai dit commando en open <http://localhost:8080>:

```sh
docker compose up -d --build
```

De eerste keer duurt het bouwen enkele minuten.
Draai hetzelfde commando opnieuw na een wijziging in de code.

## Documentatie

| Document                               | Inhoud                                      |
| -------------------------------------- | ------------------------------------------- |
| [Ontwerpdocument](docs/design/)        | Requirements en ontwerp, ook als [PDF][pdf] |
| [Techstack](docs/techstack.md)         | De gekozen tools, met de reden              |
| [Deployment](docs/deployment.md)       | Wat GitHub zelf doet en hoe het uitrolt     |
| [Werkafspraken](docs/werkafspraken.md) | Commits, branches, issues en pull requests  |
| [Server](docs/server.md)               | De server en wat erop is ingesteld          |

[pdf]: https://github.com/HAN-Craftsmanship-KL-JJG/casus/releases/tag/preview
