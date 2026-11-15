# Uitrol

Dit document beschrijft waar het prototype van ICDE draait, en hoe een wijziging daar terechtkomt.
De tools staan in [Techstack](techstack.md#uitrol).
De commando's om lokaal te starten en om de server in te richten staan in `infra/README.md`.

## Overzicht

Het prototype draait op een gehuurde server, op `https://icde.nl`.
Na een push naar de branch `main` staat de nieuwe versie binnen enkele seconden op de server.
Niemand hoeft daarvoor in te loggen op de server.

![Deployment diagram van het prototype](diagrams/uitrol-deployment.svg)

| Onderdeel | Waar | Taak |
| --- | --- | --- |
| Repository `casus` | GitHub | Bevat de code en de Compose-bestanden |
| Workflow `Deploy` | GitHub Actions | Meldt een push aan de server |
| `icde-web` (Caddy) | Server | Webserver: serveert het prototype en regelt de certificaten |
| doco-cd | Server | Haalt de repository op en start de nieuwe versie |
| Let's Encrypt | Internet | Geeft de certificaten voor HTTPS uit |

Op de server draaien twee Compose-projecten.
Het project `icde` is het prototype, en doco-cd beheert het.
Het project `doco-cd` is doco-cd zelf, en een beheerder start het één keer met de hand.

Alleen Caddy is bereikbaar vanaf het internet, op poort 80 en 443.
doco-cd heeft geen eigen poort.
Caddy geeft van `deploy.icde.nl` alleen het pad `/v1/webhook` door aan doco-cd, over het interne
netwerk `edge`.

## Van push tot nieuwe versie

![Sequence diagram van een uitrol](diagrams/uitrol-sequence.svg)

1. Een ontwikkelaar merget een pull request, en GitHub zet de commit op `main`.
2. Wijzigt de commit een bestand van de stack, dan start de workflow `Deploy`.
   De stack bestaat uit `compose.yaml`, `.doco-cd.yml` en de mappen `apps/` en `infra/`.
3. De workflow stuurt een melding naar `https://deploy.icde.nl/v1/webhook`.
   De melding heeft een handtekening, gemaakt met het geheim `WEBHOOK_SECRET`.
4. doco-cd controleert de handtekening.
   Klopt die niet, dan weigert doco-cd de melding.
5. doco-cd haalt de commit op van GitHub.
6. doco-cd start `compose.yaml` samen met `infra/compose.server.yaml`.
   Docker vervangt alleen de containers die gewijzigd zijn.

doco-cd vraagt ook elk uur zelf aan GitHub of er een nieuwe commit is.
Gaat een melding verloren, dan komt de wijziging zo alsnog op de server.

## Laptop en server

Hetzelfde bestand `compose.yaml` start het prototype op een laptop en op de server.
Een tweede bestand voegt toe wat per plek verschilt.

| | Laptop | Server |
| --- | --- | --- |
| Tweede bestand | `compose.override.yaml` | `infra/compose.server.yaml` |
| Adres | `http://localhost:8080` | `https://icde.nl` |
| Certificaat | Geen | Caddy vraagt het aan bij Let's Encrypt |
| Wie start het | De ontwikkelaar, met `docker compose up -d` | doco-cd |

## Veiligheid

doco-cd mag alles op de server starten wat in de Compose-bestanden staat.
Wie die bestanden op de gevolgde branch mag wijzigen, bestuurt dus de server.
Daarom gelden deze keuzes:

- doco-cd volgt alleen de branch `main`.
- De workflow `Deploy` stuurt de melding, niet de webhook-instelling van GitHub zelf.
  Die instelling meldt elke push, ook naar andere branches.
  doco-cd zou dan een branch uitrollen die niemand heeft beoordeeld.
- Het geheim `WEBHOOK_SECRET` staat in de GitHub-omgeving `production`.
  Alleen een workflow op de branch `main` mag die omgeving gebruiken.
- Het geheim staat ook op de server, in een bestand dat alleen de beheerder kan lezen.
  Het staat niet in de repository.

## DNS

Het domein `icde.nl` staat bij de registrar mijn.host.
Deze records wijzen naar de server:

| Naam | Type | Waarde |
| --- | --- | --- |
| `icde.nl` | A | IPv4-adres van de server |
| `icde.nl` | AAAA | IPv6-adres van de server |
| `*.icde.nl` | A | IPv4-adres van de server |
| `*.icde.nl` | AAAA | IPv6-adres van de server |

Het record `*.icde.nl` dekt `deploy.icde.nl` en elke naam die later nodig is.
De server heeft een vast adres, dus de records veranderen niet vanzelf.
