# Validatie domeinmodel ICDE

Dit document toont aan dat het [domeinmodel](domeinmodel.md) de use cases uit
[use-cases.md](use-cases.md) en [use-case-beschrijvingen.md](use-case-beschrijvingen.md) dekt.
Dit is de stap "Valideer het model" uit het NPI-stappenplan van de cursus.

## Dekking per use case

| Use case | Regels | Gegevens | In het model |
| --- | --- | --- | --- |
| UC01 Beheren OWE | BR8, BR13 | OWE met opleiding en EVL's | OWE, biedt aan, bestaat uit |
| UC02 Beheren leeruitkomsten | BR9, BR13 | Leeruitkomst met EVL | Leeruitkomst, groepeert |
| UC03 Beheren beoordelingscriteria | BR10, BR13 | Rubric, getoetste leeruitkomsten | Beoordelingsdimensie, Beoordelingscriterium, Niveau, toetst |
| UC04 Beheren lesplanning | BR2, BR11, BR13 | Les met criteria | Les, plant, draagt bij aan |
| UC05 Controleren consistentie OWE | BR1 tot en met BR5 | Koppelingen en weken | toetst, draagt bij aan, beoordeelt, startweek, deadlineweek |
| UC06 Genereren document | BR12 | Sjabloon en inhoud van de OWE | Documentsjabloon, OWE met haar onderdelen |
| UC07 Hergebruiken gedeeld onderdeel | BR6, BR7, BR13 | Gedeeld onderdeel | OWE-onderdeel, gedeeld, hergebruikt |
| UC08 Opvragen dekkingsoverzicht | BR1, BR3, BR4 | Per leeruitkomst de criteria, toetsmomenten en lessen | biedt aan, bestaat uit, groepeert, toetst, draagt bij aan, beoordeelt |
| UC09 Delen OWE-onderdeel | | Leeruitkomst of rubric | OWE-onderdeel, gedeeld |
| UC10 Beheren documentsjabloon | BR12 | Sjabloon | Documentsjabloon |
| UC11 Beheren toetsplanning | BR5, BR13, BR14 | Toetsmoment met criteria | Toetsmoment, plant, beoordeelt |

Toelichting bij de tabel:

- UC04 alternate flow 6A bewaart een les zonder criteria, dat kan door draagt bij aan 0..*.
- UC05 en UC08 exceptional flow 2A melden een OWE zonder leeruitkomsten, dat kan door
  groepeert 0..*.
- Een rubric is een Beoordelingsdimensie met haar criteria en niveaus.
- Een kopie in UC07 is een nieuwe les of een nieuw toetsmoment van de eigen OWE.

## Conclusie

Elke use case vindt haar gegevens in het model, en elke flow past bij de multipliciteiten.
Om dat te bereiken, zijn enkele use case teksten aangepast:

- BR8 noemt nu de opleiding en de EVL's van een OWE, BR9 de EVL van een leeruitkomst.
- UC07 en UC09 spreken van OWE's in plaats van profielen, want het model kent geen profielen.
- De samenvattingen van UC05 en UC08 en stap 3 van UC04 en UC11 volgen nu het model.
