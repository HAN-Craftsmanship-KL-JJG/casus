# Validatie domeinmodel ICDE

Dit document toont aan dat het [domeinmodel](domeinmodel.md) de use cases uit
[use-cases.md](use-cases.md) en [use-case-beschrijvingen.md](use-case-beschrijvingen.md) dekt.
Dit is de stap "Valideer het model" uit het NPI-stappenplan van de cursus (Thema 3).

## Dekking per use case

Per use case: de gegevens die ze gebruikt, en waar die in het model staan.

- UC01 Beheren OWE (BR8, BR13).
  Code, naam, opleiding, studiepunten, looptijd en EVL's van een OWE.
  Model: OWE, Opleiding biedt OWE aan, OWE bestaat uit EVL.
- UC02 Beheren leeruitkomsten (BR9).
  Nummer, omschrijving en EVL van een leeruitkomst.
  Model: Leeruitkomst, EVL groepeert Leeruitkomst.
- UC03 Beheren beoordelingscriteria (BR10).
  Dimensies, criteria, niveaus en de leeruitkomsten die een criterium toetst.
  Model: Beoordelingsdimensie, Beoordelingscriterium, Niveau, toetst.
- UC04 Beheren lesplanning (BR2, BR11).
  Naam, onderwijsweek en beschrijving van een les, en de criteria waaraan ze bijdraagt.
  Model: Les, OWE plant Les, draagt bij aan.
  Alternate flow 6A bewaart een les zonder criteria, dat kan door de 0..*.
- UC05 Controleren consistentie OWE (BR1 tot en met BR5).
  BR1 gebruikt toetst, BR2 en BR3 gebruiken draagt bij aan, BR4 gebruikt beoordeelt.
  BR5 gebruikt startweek en deadlineweek van Toetsmoment.
  Exceptional flow 2A meldt een OWE zonder leeruitkomsten, dat kan door EVL groepeert
  Leeruitkomst 0..*.
- UC06 Genereren document (BR12).
  Een OWE, een documentsjabloon en de gekozen onderdelen.
  Model: Documentsjabloon, en voor de inhoud OWE, EVL, Leeruitkomst, Toetsmoment,
  Beoordelingsdimensie, Beoordelingscriterium en Niveau.
- UC07 Hergebruiken gedeeld onderdeel (BR6, BR7, BR13).
  Een gedeeld onderdeel, opgenomen als verwijzing of als kopie.
  Model: OWE-onderdeel met gedeeld, OWE hergebruikt OWE-onderdeel.
  Een kopie is een nieuw onderdeel van de eigen OWE.
- UC08 Opvragen dekkingsoverzicht (BR1, BR3, BR4).
  Per leeruitkomst van een opleiding de criteria, toetsmomenten en lessen.
  Model: Opleiding biedt OWE aan, OWE bestaat uit EVL, EVL groepeert Leeruitkomst, toetst,
  draagt bij aan, beoordeelt.
- UC09 Delen OWE-onderdeel.
  Een onderdeel, zoals een leeruitkomst of een rubric, zichtbaar voor andere OWE's.
  Model: gedeeld van OWE-onderdeel, een rubric is een Beoordelingsdimensie.
- UC10 Beheren documentsjabloon (BR12).
  Naam, soort document, onderdelen, volgorde en opmaak.
  Model: Documentsjabloon.
- UC11 Beheren toetsplanning (BR4, BR5, BR14).
  Naam, soort, startweek en deadlineweek van een toetsmoment, en de criteria die het beoordeelt.
  Model: Toetsmoment, OWE plant Toetsmoment, beoordeelt.

## Conclusie

Elke use case vindt haar gegevens in het model, en elke flow past bij de multipliciteiten.
Om dat te bereiken, zijn enkele use case teksten aangepast:

- BR8 en BR9 noemen nu de EVL.
- UC07 en UC09 spreken van OWE's in plaats van profielen, want het model kent geen profielen.
- De samenvattingen van UC05 en UC08 en stap 3 van UC04 en UC11 volgen nu het model.
