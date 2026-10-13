# Inleiding

Dit document beschrijft de analyse en het ontwerp van ICDE (Integrated Course Design Environment).
ICDE bewaart de gegevens van een onderwijseenheid, controleert ze op consistentie en genereert er
documenten uit.
Het is de basis voor de realisatie van het prototype in blok 2, en is bedoeld voor reviewers en
docenten.

## Opbouw

Het document bestaat uit een requirements-specificatie (SRS) en een ontwerp (SDD).
ICDE heeft veel interactie tussen objecten, dus het ontwerp toont ook dynamische modellen.

| Deel | Hoofdstuk | Inhoud | Criterium B_Casus1 |
| --- | --- | --- | --- |
| SRS | [Systeemgrenzen](02-systeemgrenzen.md#systeemgrenzen) | Actoren, scope, wensen van de opdrachtgever | 1 |
| SRS | [Use cases](03-use-cases.md#use-cases) | Use case diagram, 11 use cases | 1 |
| SRS | [Use case beschrijvingen](04-use-case-beschrijvingen.md#use-case-beschrijvingen) | Fully dressed, BR1-BR14 | 1 |
| SRS | [Domeinmodel](05-domeinmodel.md#domeinmodel) | 11 concepten, validatie tegen de use cases | 2 |
| SDD | [Architectuur](06-architectuur.md#architectuur) | Component diagram, lagen en servers | 3.2 |
| SDD | [Klassendiagram](07-klassendiagram.md#klassendiagram) | Statisch ontwerp, traceerbaarheid | 3.1, 3.2 |
| SDD | [Sequence diagrams](08-sequencediagrammen.md#sequence-diagrams) | Dynamisch ontwerp | 3.1, 3.2 |
| SDD | [Verantwoording](09-verantwoording.md#verantwoording) | Keuzes, eisen, consistentie | 3.1, 3.2, 4 |
| | [Open punten en overdracht](10-open-punten.md#open-punten-en-overdracht) | Wat nog open is | |

Elke ontwerpkeuze heeft een code: D voor het domeinmodel, A voor de architectuur, K voor het
klassendiagram en S voor de sequence diagrams.
Elke keuze noemt het probleem, de alternatieven met hun nadeel, en de keuze.

## Bronnen

- De ICDE-casus van Christian Köppe en Rody Middelkoop.
- De Modulebeschrijving van de toets Casus, met de aanvullende wensen van de opdrachtgever.
- De lesplanning en de rubric van OOSE-DT, als voorbeeld van echte OWE-gegevens.
- Larman, Applying UML and Patterns: hoofdstuk 4, 7, 8 en 17.

De bron van elk diagram staat in PlantUML in `docs/diagrams/`, met dezelfde naam als de afbeelding.
