# Uitrol

Dit document beschrijft waar het prototype van ICDE draait, en hoe een wijziging daar terechtkomt.
De tools staan in [Techstack](techstack.md#uitrol).
De commando's om lokaal te starten en om de server in te richten staan in `infra/README.md`.

## Overzicht

Het prototype draait op een gehuurde server, in twee omgevingen.
Elke omgeving volgt een branch van git flow.

| Omgeving | Adres | Branch | Inhoud |
| --- | --- | --- | --- |
| Productie | `https://icde.nl` | `main` | De laatste opgeleverde versie |
| Ontwikkeling | `https://dev.icde.nl` | `develop` | Het werk voor de volgende oplevering |

Na een push naar een van die branches staat de nieuwe versie binnen enkele seconden op de server.
Niemand hoeft daarvoor in te loggen op de server.

![Deployment diagram van het prototype](diagrams/uitrol-deployment.svg)

Het diagram is vereenvoudigd: de melding van GitHub loopt ook via de proxy.

| Onderdeel | Waar | Taak |
| --- | --- | --- |
| Repository `casus` | GitHub | Bevat de code en de Compose-bestanden |
| Workflow `Deploy` | GitHub Actions | Meldt een push aan de server |
| Proxy (Caddy) | Server | Ontvangt al het verkeer, regelt de certificaten en stuurt door |
| doco-cd | Server | Haalt de repository op en start de nieuwe versie |
| Web (Caddy) | Server, per omgeving | Webserver: serveert het prototype |
| Let's Encrypt | Internet | Geeft de certificaten voor HTTPS uit |

Op de server draaien drie Compose-projecten.

- `edge` is het vaste deel: de proxy en doco-cd.
  Een beheerder start het met de hand.
- `icde` is de omgeving productie.
- `icde-dev` is de omgeving ontwikkeling.

doco-cd beheert `icde` en `icde-dev`.
Beide starten uit dezelfde bestanden, alleen de branch verschilt.
Elke omgeving krijgt later een eigen database, zodat testgegevens niet in productie komen.

Alleen de proxy is bereikbaar vanaf het internet, op poort 80 en 443.
De proxy stuurt elke naam door naar één container:

| Naam | Gaat naar |
| --- | --- |
| `icde.nl` | De webserver van productie |
| `dev.icde.nl` | De webserver van ontwikkeling |
| `deploy.icde.nl` | doco-cd, alleen het pad `/v1/webhook` |

## Van push tot nieuwe versie

![Sequence diagram van een uitrol](diagrams/uitrol-sequence.svg)

Het diagram toont de hoofdlijn, de stappen hieronder geven het detail.

1. Een ontwikkelaar merget een pull request, en GitHub zet de commit op `main` of `develop`.
2. Wijzigt de commit een bestand van de stack, dan start de workflow `Deploy`.
   De stack bestaat uit `compose.yaml`, de bestanden `.doco-cd.yml` en `.doco-cd.dev.yml`, en de
   mappen `apps/` en `infra/`.
3. De workflow stuurt een melding naar `https://deploy.icde.nl/v1/webhook`.
   Voor `develop` eindigt het pad op `/dev`.
   De melding heeft een handtekening, gemaakt met het geheim `WEBHOOK_SECRET`.
4. doco-cd controleert de handtekening.
   Klopt die niet, dan weigert doco-cd de melding.
5. doco-cd haalt de commit op van GitHub.
6. doco-cd start de stack van de omgeving.
   Docker vervangt alleen de containers die gewijzigd zijn.

doco-cd vraagt ook elk uur zelf aan GitHub of een van de twee branches een nieuwe commit heeft.
Gaat een melding verloren, dan komt de wijziging zo alsnog op de server.

Het vaste deel `edge` rolt niet vanzelf uit.
Na een wijziging in `infra/edge/` zet een beheerder de bestanden op de server en start het opnieuw.

## Laptop en server

Hetzelfde bestand `compose.yaml` start het prototype op een laptop en op de server.
Een tweede bestand voegt toe wat per plek verschilt.

| | Laptop | Server |
| --- | --- | --- |
| Tweede bestand | `compose.override.yaml` | `infra/compose.server.yaml` |
| Adres | `http://localhost:8080` | `https://icde.nl` of `https://dev.icde.nl` |
| HTTPS | Nee | Ja, de proxy regelt het certificaat |
| Wie start het | De ontwikkelaar, met `docker compose up -d` | doco-cd |

## Veiligheid

doco-cd mag alles op de server starten wat in de Compose-bestanden staat.
Wie die bestanden op een gevolgde branch mag wijzigen, bestuurt dus de server.
Daarom gelden deze keuzes:

- doco-cd volgt alleen de branches `main` en `develop`.
  Een wijziging komt daar alleen via een pull request.
- De workflow `Deploy` stuurt de melding, niet de webhook-instelling van GitHub zelf.
  Die instelling meldt elke push, ook naar andere branches.
  doco-cd zou dan een branch uitrollen die niemand heeft beoordeeld.
- Het geheim `WEBHOOK_SECRET` staat in de GitHub-omgevingen `production` en `development`.
  Alleen een workflow op `main` mag `production` gebruiken, en alleen een workflow op `develop`
  mag `development` gebruiken.
- Het geheim staat ook op de server, in een bestand dat alleen de beheerder kan lezen.
  Het staat niet in de repository.

Beide omgevingen delen één doco-cd en dus één geheim.
Wie `develop` mag wijzigen, kan daarmee ook productie raken.
Dat is voor een prototype aanvaard.

## DNS

Het domein `icde.nl` staat bij de registrar mijn.host.
Deze records wijzen naar de server:

| Naam | Type | Waarde |
| --- | --- | --- |
| `icde.nl` | A | IPv4-adres van de server |
| `icde.nl` | AAAA | IPv6-adres van de server |
| `*.icde.nl` | A | IPv4-adres van de server |
| `*.icde.nl` | AAAA | IPv6-adres van de server |

Het record `*.icde.nl` dekt `dev.icde.nl`, `deploy.icde.nl` en elke naam die later nodig is.
De server heeft een vast adres, dus de records veranderen niet vanzelf.
