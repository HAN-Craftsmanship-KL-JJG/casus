# ICDE: Integrated Course Design Environment

Onderwijs ontwerpen gebeurt nu in losse Word- en Excel-bestanden, die uit de pas lopen.
ICDE bewaart leeruitkomsten, rubrics, toetsen en lessen als data, controleert ze op consistentie
en genereert er documenten uit.

Dit is de casus van ons team voor de HAN-module OOSE Deeltijd 2026/2027.

## Architectuur

ICDE bestaat uit vier containers.

| Onderdeel                 | Map               | Techniek                   |
| ------------------------- | ----------------- | -------------------------- |
| Webserver met de frontend | `web/`            | Caddy, React, TypeScript   |
| Applicatieserver          | `api/`            | C++, Drogon                |
| Documentserver            | `documentserver/` | C++, Drogon, Pandoc, Typst |
| Database                  | `db/`             | PostgreSQL                 |

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
| [Werkafspraken](docs/werkafspraken.md) | Commits, branches, issues en pull requests  |

[pdf]: https://github.com/HAN-Craftsmanship-KL-JJG/casus/releases/tag/preview
