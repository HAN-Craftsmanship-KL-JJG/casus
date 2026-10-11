# Validatie domeinmodel ICDE

Dit document controleert of het [domeinmodel](domeinmodel.md) de use cases dekt.
Het gebruikt de use cases uit [use-cases.md](use-cases.md) en
[use-case-beschrijvingen.md](use-case-beschrijvingen.md).

## Aanpak

Dit is de stap "Valideer het model" uit het NPI-stappenplan van de cursus (Thema 3).
We controleren in twee richtingen:

- Van use case naar model.
  We lopen elke use case en haar bedrijfsregels langs.
  Elk gegeven dat de use case gebruikt, moet een concept, attribuut of associatie zijn.
  Elke stap moet uitvoerbaar zijn met de multipliciteiten van het model.
- Van model naar use case.
  Elk concept en elke associatie moet in minstens één use case of bedrijfsregel voorkomen.
  Anders is het model groter dan nodig.

Wat niet klopt, staat onder Bevindingen, met de verbetering.
De verbeteringen zijn in deze versie van het model en de use cases verwerkt.

## Van use case naar model

Per use case: de gegevens die ze gebruikt, en waar die in het model staan.

- UC01 Beheren OWE (BR8, BR13).
  Code, naam, opleiding, studiepunten, looptijd en EVL's.
  Model: de attributen van OWE, Opleiding biedt OWE aan, OWE bestaat uit EVL.
  Klopt na bevinding 1.
- UC02 Beheren leeruitkomsten (BR9).
  Nummer, omschrijving en EVL van een leeruitkomst van een OWE.
  Model: Leeruitkomst, EVL groepeert Leeruitkomst.
  Klopt na bevinding 1.
- UC03 Beheren beoordelingscriteria (BR10).
  Dimensies, criteria, niveaus en de leeruitkomsten die een criterium toetst.
  Model: Beoordelingsdimensie, Beoordelingscriterium, Niveau, toetst.
  Klopt.
- UC04 Beheren lesplanning (BR2, BR11).
  Naam, onderwijsweek en beschrijving van een les, en de criteria waaraan ze bijdraagt.
  Model: Les, OWE plant Les, draagt bij aan.
  Alternate flow 6A bewaart een les zonder criteria: dat kan door de 0..*.
  Klopt.
- UC05 Controleren consistentie OWE (BR1 tot en met BR5).
  BR1 gebruikt toetst, BR2 en BR3 gebruiken draagt bij aan, BR4 gebruikt beoordeelt.
  BR5 gebruikt startweek en deadlineweek van de toetsmomenten die de OWE plant.
  Exceptional flow 2A meldt een OWE zonder leeruitkomsten: dat kan door EVL groepeert
  Leeruitkomst 0..*.
  Klopt.
- UC06 Genereren document (BR12).
  Een OWE, een documentsjabloon voor een soort document, en de gekozen onderdelen.
  De OWE-beschrijving en EVL-beschrijving gebruiken OWE, EVL en Leeruitkomst.
  De toetsplanning gebruikt Toetsmoment.
  Het beoordelingsformulier gebruikt Beoordelingsdimensie, Beoordelingscriterium en Niveau.
  Model: Documentsjabloon met soortDocument, onderdelen en volgorde.
  Documentsjabloon heeft geen associatie, want UC06 combineert sjabloon en OWE pas bij het
  genereren.
  Klopt.
- UC07 Hergebruiken gedeeld onderdeel (BR6, BR7, BR13).
  De gedeelde onderdelen die de OWE nog niet bevat, op te nemen als verwijzing of als kopie.
  Model: OWE-onderdeel met vier subtypes, gedeeld, OWE hergebruikt OWE-onderdeel.
  BR7 vraagt de OWE van herkomst.
  Die volgt uit de associatie met de eigen OWE, of voor een leeruitkomst uit de EVL.
  Een kopie is een nieuw onderdeel van de eigen OWE (keuze 3 in het domeinmodel).
  BR11 en BR14 staan koppelingen toe met hergebruikte criteria.
  Dat past bij de beperkingen van het domeinmodel: een onderdeel van de OWE is eigen of
  hergebruikt.
  Klopt.
- UC08 Opvragen dekkingsoverzicht (BR1, BR3, BR4).
  Opleiding, OWE's, leeruitkomsten, criteria, toetsmomenten en lessen.
  Model: het pad Opleiding, OWE, EVL, Leeruitkomst, en via toetst naar het criterium.
  Vanaf het criterium leiden draagt bij aan en beoordeelt naar lessen en toetsmomenten.
  Klopt.
- UC09 Delen OWE-onderdeel.
  Een onderdeel, zoals een leeruitkomst of een rubric, zichtbaar maken voor andere OWE's.
  Model: gedeeld van OWE-onderdeel, een rubric is een Beoordelingsdimensie.
  Klopt na bevinding 2.
- UC10 Beheren documentsjabloon (BR12).
  Naam, soort document, onderdelen, volgorde en opmaak.
  Model: de attributen van Documentsjabloon.
  Klopt.
- UC11 Beheren toetsplanning (BR4, BR5, BR14).
  Naam, soort, startweek en deadlineweek van een toetsmoment, en de criteria die het beoordeelt.
  Model: Toetsmoment, OWE plant Toetsmoment, beoordeelt.
  Klopt.

## Van model naar use case

Elk concept komt in minstens één use case voor:

- Opleiding: UC01, UC08.
- OWE: UC01, UC05, UC06, UC07, UC08.
- EVL: UC01, UC02, UC06.
- OWE-onderdeel: UC07, UC09.
- Leeruitkomst: UC02, UC03, UC05, UC08.
- Beoordelingsdimensie: UC03, UC06.
- Beoordelingscriterium: UC03, UC04, UC05, UC08, UC11.
- Niveau: UC03, UC06.
- Les: UC04, UC05, UC08.
- Toetsmoment: UC05, UC08, UC11.
- Documentsjabloon: UC06, UC10.

Elke associatie komt in minstens één use case of bedrijfsregel voor:

- Opleiding biedt OWE aan: UC01, UC08.
- OWE bestaat uit EVL: UC01, BR8.
- EVL groepeert Leeruitkomst: UC02, UC08.
- OWE beoordeelt met Beoordelingsdimensie, Beoordelingsdimensie bestaat uit
  Beoordelingscriterium, Beoordelingscriterium onderscheidt Niveau: UC03, BR10.
- OWE plant Les: UC04, BR11.
- OWE plant Toetsmoment: UC11, BR5, BR14.
- Beoordelingscriterium toetst Leeruitkomst: UC03, UC08, BR1.
- Les draagt bij aan Beoordelingscriterium: UC04, BR2, BR3.
- Toetsmoment beoordeelt Beoordelingscriterium: UC11, BR4.
- OWE hergebruikt OWE-onderdeel: UC07, BR6, BR13.

Elk attribuut komt voor in een stap, een bedrijfsregel of een document van UC06.
Het model heeft dus geen overbodige elementen.

## Bevindingen

1. Geen regel legde de EVL's van een OWE vast.
   Het model heeft OWE bestaat uit EVL met 1..*, want de casus zegt dat een OWE uit een of meer
   EVL's bestaat.
   Ook hoort elke leeruitkomst bij één EVL.
   Maar geen use case of bedrijfsregel noemde de EVL.
   UC01 en UC02 konden de EVL dus niet controleren.
   Verbetering: BR8 eist nu minstens één EVL met naam en studiepunten.
   BR9 eist dat een leeruitkomst bij één EVL van de OWE hoort.
   UC01 beheert de OWE met haar EVL's.
2. UC07 en UC09 noemden profielen.
   UC09 maakte een onderdeel zichtbaar voor andere profielen.
   Het domeinmodel kent geen profielen, want de HAN kent ze niet (keuze 4).
   Het attribuut gedeeld maakt een onderdeel zichtbaar voor elke andere OWE.
   Verbetering: UC09 in de use case beschrijvingen en in het use case diagram spreekt nu van
   andere OWE's.
   De stakeholder van UC07 wil dat een verbetering aankomt bij elke OWE die het onderdeel
   hergebruikt.

## Open punten

- De laatste stap van het NPI-stappenplan is "Review het model met gebruikers".
  Dat doen we met de opdrachtgever, samen met de open vragen uit de use cases.
