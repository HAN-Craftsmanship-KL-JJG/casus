# Techstack

De tools voor het prototype van ICDE.
Het prototype moet op macOS en Windows hetzelfde werken.

## Toolchain

| Tool | Functie | Reden |
| --- | --- | --- |
| C++ | Programmeertaal | Het team kent deze taal |
| C++20 | Versie van C++ | Laatste standaard die zowel Clang als Drogon beide ondersteunen |
| Clang | Compiler | De enige compiler die op macOS en Windows hetzelfde werkt. MSVC bouwt niet voor macOS |
| CMake | Buildsysteem | Industriestandaard. Drogon en vcpkg zijn erop gebouwd |
| vcpkg | Package manager voor C++ | Meeste GitHub-sterren. Heeft packages voor alle libraries in dit overzicht en werkt direct met CMake |

## Applicatieserver

| Tool | Functie | Reden |
| --- | --- | --- |
| Drogon | Webframework: routing, sessies, databaseclient, coroutines | Dekt de meeste behoeften in één library, dus het minste eigen code |
| jsoncpp | JSON lezen en schrijven | Zit al in Drogon, dus geen extra afhankelijkheid |
| libsodium | Wachtwoorden hashen met Argon2id | Eenvoudigste veilige API: één aanroep om te hashen, één om te controleren |

## Documenten

| Tool | Functie | Reden |
| --- | --- | --- |
| Pandoc | Word-documenten maken uit een sjabloon | Het enige alternatief dat goede Word-bestanden maakt uit een sjabloon. Sjablonen zijn tijdens het draaien aan te passen (UC10). Het ontwerpdocument gebruikt Pandoc al |
| Typst | PDF-documenten maken uit een sjabloon | Meeste GitHub-sterren, snel en één programma. Het ontwerpdocument gebruikt Typst al |
| `pandoc/typst` | Containerimage van de documentserver, met Pandoc en Typst | Officieel image met beide programma's. Het ontwerpdocument gebruikt het al |

Pandoc en Typst draaien samen op een eigen documentserver, zie
[Architectuur](06-architectuur.md#a2-waar-wordt-het-bestand-gemaakt).
Op de documentserver draait een kleine HTTP-service die de programma's start.
Die service is in C++ met Drogon geschreven, net als de applicatieserver.
Zo heeft de backend één taal, één framework en één set van linter en formatter.

## Database

| Tool | Functie | Reden |
| --- | --- | --- |
| PostgreSQL | Databaseserver | Industriestandaard. Drogon ondersteunt PostgreSQL het best |
| dbmate | Migraties: wijzigingen van het databaseschema in volgorde uitvoeren | Eenvoudigste: gewone SQL-bestanden en één programma, zonder Java |

## API

| Tool | Functie | Reden |
| --- | --- | --- |
| OpenAPI 3.1 | Contract van de REST API | Industriestandaard |
| Swagger UI | Documentatie van de API, met aanroepen vanuit de browser | Industriestandaard. "Try it out" helpt bij het testen tijdens het bouwen |
| openapi-generator | TypeScript-client voor de frontend genereren uit het contract | Meeste GitHub-sterren. Frontend en backend blijven gelijk aan het contract |

## Frontend en webserver

| Tool | Functie | Reden |
| --- | --- | --- |
| React met TypeScript | Gebruikersinterface | Meeste GitHub-sterren, en eenvoudig te leren |
| Vite | Bouwt de frontend | Standaard voor React |
| Caddy | Webserver: serveert de frontend en stuurt `/api` door naar Drogon | Eenvoudigste configuratie. Traefik kan geen bestanden serveren |

## Tests

| Tool | Functie | Reden |
| --- | --- | --- |
| GoogleTest | Unittests | Industriestandaard |
| GoogleMock | Mocks, zoals nep-repositories in tests | Hoort bij GoogleTest |
| llvm-cov | Testdekking meten | Zit in Clang, dus geen extra tool |

## Codekwaliteit

| Tool | Functie | Reden |
| --- | --- | --- |
| clang-tidy | Linter voor C++ | Zit in Clang. Controleert ook de C++ Core Guidelines |
| clang-format | Formatter voor C++ | Zit in Clang |
| ESLint | Linter voor TypeScript | Industriestandaard |
| Prettier | Formatter voor TypeScript | Industriestandaard |
| lizard | Grenzen aan complexiteit, lengte en aantal parameters van functies | Werkt voor C++ en TypeScript, dus één tool voor beide |
| GitHub CodeQL | Statische analyse, of GitHub Code Quality als dat C++ ondersteunt | Ingebouwd in GitHub en gratis voor een publieke repository |
| Dependabot | Meldt en vernieuwt verouderde afhankelijkheden | Ingebouwd in GitHub en gratis |

## Uitrol

| Tool | Functie | Reden |
| --- | --- | --- |
| Docker Compose | Start webserver, applicatieserver, documentserver en database als losse containers | Volgt de servers uit [Architectuur](06-architectuur.md#architectuur), en werkt hetzelfde op macOS en Windows |
| GitHub Actions | Bouwt en test elke wijziging op Linux, macOS en Windows | De repository staat op GitHub, en de runners dekken alle drie de platforms |

## Optioneel

| Tool | Functie | Reden |
| --- | --- | --- |
| Pocket ID | Inloggen met passkeys via OpenID Connect, in plaats van eigen inloggen met libsodium | Geen wachtwoorden, en gebruikers en groepen zijn via een API aan te maken. Werkt offline |
| jwt-cpp | Controleert in Drogon het token van Pocket ID | Alleen nodig met Pocket ID |
| `react-oidc-context` | Inloggen via Pocket ID in de frontend | Alleen nodig met Pocket ID |
