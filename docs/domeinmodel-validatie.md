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
  Klopt na bevinding 4.
- UC02 Beheren leeruitkomsten (BR9).
  Nummer en omschrijving van een leeruitkomst van een OWE.
  Model: Leeruitkomst, via EVL groepeert Leeruitkomst.
  Klopt, de keuze van de EVL is een open punt in het domeinmodel.
- UC03 Beheren beoordelingscriteria (BR10).
  Dimensies, criteria, niveaus en de leeruitkomsten die een criterium toetst.
  Model: Beoordelingsdimensie, Beoordelingscriterium, Niveau, toetst.
  Klopt.
- UC04 Beheren lesplanning (BR2, BR11).
  Naam, onderwijsweek en beschrijving van een les, en de criteria waaraan ze bijdraagt.
  Model: Les, OWE plant Les, draagt bij aan.
  Alternate flow 7B bewaart een les zonder criteria: dat kan door de 0..*.
  Klopt.
- UC05 Controleren consistentie OWE (BR1 tot en met BR5).
  BR1 gebruikt toetst, BR2 en BR3 gebruiken draagt bij aan, BR4 gebruikt beoordeelt.
  BR5 gebruikt startweek en deadlineweek van de toetsmomenten die de OWE plant.
  Exceptional flow 2A (een OWE zonder leeruitkomsten) kon niet voorkomen, zie bevinding 1.
- UC06 Genereren document (BR12).
  Een OWE en een documentformaat per soort document.
  De OWE-beschrijving en EVL-beschrijving gebruiken OWE, EVL en Leeruitkomst.
  De toetsplanning gebruikt Toetsmoment.
  Het beoordelingsformulier gebruikt Beoordelingsdimensie, Beoordelingscriterium en Niveau.
  Model: Documentformaat met soortDocument.
  Klopt.
- UC07 Hergebruiken gedeeld onderdeel (BR6, BR7, BR13).
  Een gedeeld onderdeel met soort en OWE van herkomst, als verwijzing of als kopie.
  Model: OWE-onderdeel met vier subtypes, gedeeld, OWE hergebruikt OWE-onderdeel.
  De soort is het subtype.
  De OWE van herkomst volgt uit de associatie met de eigen OWE, of voor een leeruitkomst uit de
  EVL.
  Een kopie is een nieuw onderdeel van de eigen OWE.
  Klopt na bevinding 2 en 3.
- UC08 Opvragen dekkingsoverzicht (BR1, BR3, BR4).
  Opleiding, OWE's, leeruitkomsten, criteria, toetsmomenten en lessen.
  Model: het pad Opleiding, OWE, EVL, Leeruitkomst, en via toetst naar het criterium.
  Vanaf het criterium leiden draagt bij aan en beoordeelt naar lessen en toetsmomenten.
  Klopt.
- UC09 Delen OWE-onderdeel.
  Een onderdeel, zoals een leeruitkomst of een rubric, voor andere opleidingen en profielen.
  Model: gedeeld van OWE-onderdeel, een rubric is een Beoordelingsdimensie.
  Profielen zijn geen concept (keuze 2 in het domeinmodel).
  Klopt.
- UC10 Beheren documentformaat (BR12).
  Naam, soort document en opmaak.
  Model: de attributen van Documentformaat.
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
- Documentformaat: UC06, UC10.

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

1. Een OWE zonder leeruitkomsten kon niet bestaan.
   Het model had EVL groepeert Leeruitkomst met 1..*.
   Maar UC01 maakt een OWE aan voordat UC02 de leeruitkomsten vastlegt.
   En UC05 en UC08 hebben een exceptional flow 2A voor een OWE zonder leeruitkomsten.
   Verbetering: de multipliciteit is nu 0..*.
   Dat volgt keuze 1 van het domeinmodel: ICDE bewaart ook een onvolledige OWE.
2. Hergebruikte onderdelen vielen buiten "dezelfde OWE".
   BR10, BR11 en BR14 staan alleen koppelingen toe met onderdelen van dezelfde OWE.
   Een ontwikkelaar kon dus geen les koppelen aan een criterium uit een hergebruikte dimensie.
   Dan heeft UC07 geen nut.
   Verbetering: "van de OWE" omvat nu ook wat de OWE hergebruikt.
   Dat staat bij de bedrijfsregels en bij de beperkingen van het domeinmodel.
3. UC07 toonde de naam van een gedeeld onderdeel.
   Een leeruitkomst heeft geen naam, maar een nummer en een omschrijving.
   Verbetering: stap 2 toont soort en OWE van herkomst, stap 4 toont de inhoud.
   Alternatief was een attribuut naam op OWE-onderdeel.
   Dat voegt een gegeven toe dat de opdrachtgever voor een leeruitkomst niet gebruikt.
4. Geen regel legde de EVL's van een OWE vast.
   De compositie OWE bestaat uit EVL eist minstens één EVL.
   Geen use case of bedrijfsregel noemde de EVL.
   Verbetering: BR8 eist nu minstens één EVL met naam en studiepunten.
   UC01 beheert de OWE met haar EVL's.

## Open punten

- De laatste stap van het NPI-stappenplan is "Review het model met gebruikers".
  Dat doen we met de opdrachtgever, samen met de open vragen uit de use cases.
