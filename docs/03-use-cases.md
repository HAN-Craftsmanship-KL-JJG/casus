# Use cases

Dit hoofdstuk leidt de use cases af uit de actoren en de scope, en licht de keuzes toe.

## Use case diagram

![Use case diagram van ICDE](diagrams/use-case-diagram.svg)

## Overzicht use cases

We vonden de use cases vanuit de doelen van elke primary actor.
Elke use case is een elementair bedrijfsproces: één persoon voert het uit op één plaats en één
moment, en de gegevens zijn daarna consistent.

| ID | Use case | Primary actor | CRUD | Prioriteit |
| --- | --- | --- | --- | --- |
| UC01 | Beheren OWE | Onderwijsontwikkelaar | ja | hoog |
| UC02 | Beheren leeruitkomsten | Onderwijsontwikkelaar | ja | hoog |
| UC03 | Beheren beoordelingscriteria | Onderwijsontwikkelaar | ja | hoog |
| UC04 | Beheren lesplanning | Onderwijsontwikkelaar | ja | hoog |
| UC05 | Controleren consistentie OWE | Onderwijsontwikkelaar | nee | hoog |
| UC06 | Genereren document | Onderwijsontwikkelaar | nee | hoog |
| UC07 | Hergebruiken gedeeld onderdeel | Onderwijsontwikkelaar | nee | middel |
| UC08 | Opvragen dekkingsoverzicht | Opleidingscoördinator | nee | hoog |
| UC09 | Delen OWE-onderdeel | Opleidingscoördinator | nee | middel |
| UC10 | Beheren documentsjabloon | Functioneel beheerder | ja | middel |
| UC11 | Beheren toetsplanning | Onderwijsontwikkelaar | ja | hoog |

Het doel van elke use case:

- UC01: een OWE aanmaken, bekijken, wijzigen en verwijderen.
- UC02: de leeruitkomsten van een OWE vastleggen, per EVL.
- UC03: de rubric van een OWE vastleggen: dimensies, criteria en niveaus.
- UC04: lessen vastleggen, met de beoordelingscriteria waaraan elke les bijdraagt.
- UC05: het systeem meldt inconsistenties, zoals een criterium zonder les.
- UC06: het systeem maakt met een sjabloon een document uit de gegevens van een OWE.
  De gebruiker kiest alle gegevens of een selectie, en PDF of Word.
- UC07: een ontwikkelaar neemt een gedeeld onderdeel op in de eigen OWE.
- UC08: het systeem toont per leeruitkomst van een opleiding hoeveel criteria, toetsmomenten en
  lessen eraan bijdragen.
- UC09: een onderdeel van een OWE beschikbaar maken voor andere OWE's binnen HBO-ICT.
- UC10: sjablonen vastleggen, los van de inhoud.
  Een sjabloon bepaalt welke onderdelen een document toont, in welke volgorde en met welke opmaak.
- UC11: toetsmomenten vastleggen, met startweek, deadlineweek en de criteria die ze beoordelen.
  Het systeem waarschuwt bij meer dan 3 toetsen in een week.

## Eis: maximaal 65% CRUD

De casus eist minimaal 10 use cases, waarvan maximaal 65% CRUD.
Van de 11 use cases zijn er 6 CRUD: UC01, UC02, UC03, UC04, UC10 en UC11.
Dat is 55%.

## Keuzes

### Stereotype «CRUD»

Het beheren van een item is één use case met «CRUD»: toevoegen, bekijken, wijzigen en
verwijderen.
Het telt als één use case bij de 65% CRUD.
Zie [CRUD use cases](04-use-case-beschrijvingen.md#crud-use-cases).

### Geen «include» of «extend»

Die geven in dit diagram geen meerwaarde.

### Geen use case Inloggen

Inloggen levert de gebruiker zelf geen waarde, en is dus geen elementair bedrijfsproces.
Een ingelogde gebruiker is een preconditie van elke use case.
ICDE regelt het inloggen voorlopig zelf.
Een koppeling met SURFconext kan later.

### Geen use case voor samenwerken

Samenwerken zonder versieconflicten is een eigenschap van elke wijzig-use case, geen doel van een
actor.
Het is een niet-functionele requirement: een invoerveld is geblokkeerd zolang iemand het wijzigt,
en de rest van de OWE blijft bewerkbaar.

### Prioriteit

Hoog is de kern van de casus: gegevens vastleggen, controleren en documenten genereren.
Middel zijn delen, hergebruiken en sjabloonbeheer.
UC05 heeft de hoogste prioriteit, omdat de opdrachtgever gegevensvalidatie voorop zet.
