# Inleiding

Dit document beschrijft de analyse en het ontwerp van ICDE (Integrated Course Design Environment).
ICDE ondersteunt het administratieve deel van het ontwikkelen van onderwijs.
Het document is bedoeld voor wie ICDE in blok 2 bouwt, en voor reviewers en docenten.

## Leeswijzer

Het document bestaat uit een requirements-specificatie (SRS) en een ontwerp (SDD).
Elk hoofdstuk bouwt voort op de hoofdstukken ervoor.

| Deel | Hoofdstuk | Inhoud | Criterium B_Casus1 |
| --- | --- | --- | --- |
| SRS | [Systeemgrenzen](02-systeemgrenzen.md#systeemgrenzen) | Actoren, scope, wensen van de opdrachtgever | 1 |
| SRS | [Use cases](03-use-cases.md#use-cases) | Use case diagram, 11 use cases | 1 |
| SRS | [Use case beschrijvingen](04-use-case-beschrijvingen.md#use-case-beschrijvingen) | Fully dressed, BR1-BR14 | 1 |
| SRS | [Domeinmodel](05-domeinmodel.md#domeinmodel) | Domeinmodel, 11 concepten | 2 |
| SRS | [Validatie domeinmodel](06-domeinmodel-validatie.md#validatie-domeinmodel) | Domeinmodel tegen use cases | 2 |
| SDD | [Ontwerp](07-ontwerp.md#ontwerp) | Architectuur, keuzes, consistentie | 3.1, 3.2, 4 |
| SDD | [Klassendiagram](08-klassendiagram.md#klassendiagram) | Statisch ontwerp, traceerbaarheid | 3.1, 3.2 |
| SDD | [Sequence diagrams](09-sequencediagrammen.md#sequence-diagrams) | Dynamisch ontwerp | 3.1, 3.2 |

## Diagrammen

De diagrammen zijn getekend in PlantUML.
De bron van elk diagram staat in `docs/diagrams/`, met dezelfde naam als de afbeelding.
