# Sequence diagrams ICDE

Dit document toont hoe de objecten van ICDE samenwerken in de kern-use-cases.
Het bouwt voort op de [use case beschrijvingen](use-case-beschrijvingen.md) en het
[klassendiagram](klassendiagram.md).
Bronnen: Larman hoofdstuk 4 (System Sequence Diagrams) en 8 (UML Interaction Diagrams).

## Aanpak

We tekenen de use cases met logica: UC05, UC06, UC07 en UC08, en het toevoegen bij UC04 en
UC11.
De andere CRUD use cases hebben geen eigen logica.

- Een system sequence diagram (SSD) per use case levert de systeemoperaties.
- Een sequence diagram (SD) per systeemoperatie toont hoe de handler het werk verdeelt.
- Een systeemoperatie die alleen gegevens ophaalt, krijgt geen SD.

De SD's tonen de gebruikersinterface niet: de actor roept de handler direct aan.
Een exception staat als stippellijn `OngeldigeInvoerException` met de flow uit de use case, zoals
(2A).
De SD's gebruiken getters en constructors (`create`) die het klassendiagram weglaat (Larman 7.6).

## System sequence diagrams

UC04 en UC11 hebben geen SSD, omdat ze één systeemoperatie hebben.

![SSD UC05 Controleren consistentie OWE](diagrams/ssd-uc05-controleren-consistentie.svg)

![SSD UC06 Genereren document](diagrams/ssd-uc06-genereren-document.svg)

![SSD UC07 Hergebruiken gedeeld onderdeel](diagrams/ssd-uc07-hergebruiken-onderdeel.svg)

![SSD UC08 Opvragen dekkingsoverzicht](diagrams/ssd-uc08-opvragen-dekking.svg)

## Systeemoperaties

| Use case | Systeemoperatie | Handler | SD |
| --- | --- | --- | --- |
| UC04 | toevoegenLes | BeheerPlanningHandler | toevoegenLes |
| UC05 | controleer | ControleerConsistentieHandler | controleer, BR1, BR5 |
| UC06 | geefSjablonen | GenereerDocumentHandler | Geen |
| UC06 | genereer | GenereerDocumentHandler | genereer |
| UC07 | geefGedeeldeOnderdelen | HergebruikOnderdeelHandler | Geen |
| UC07 | opnemenOnderdeel | HergebruikOnderdeelHandler | opnemenOnderdeel |
| UC07 | opnemenKopie | HergebruikOnderdeelHandler | opnemenKopie |
| UC08 | geefDekking | OpvragenDekkingHandler | geefDekking, OWE.bepaalDekking |
| UC11 | toevoegenToetsmoment | BeheerPlanningHandler | toevoegenToetsmoment |

`geefSjablonen` en `geefGedeeldeOnderdelen` halen alleen gegevens op uit een repository.

## Sequence diagrams

### UC04 Toevoegen les

OWE maakt de les en controleert de week en de criteria (BR11, 4A).
Daarna controleert LesDraagtBijRegel BR2.
De handler geeft alleen de overtredingen van de nieuwe les terug (6A, keuze 2).

![SD toevoegenLes](diagrams/sd-uc04-toevoegenles.svg)

### UC05 Controleren consistentie OWE

De handler kent alleen de interface Consistentieregel.
`controleer(owe)` is een polymorfe message: elke regel werkt haar eigen controle uit.

![SD controleer](diagrams/sd-uc05-controleer.svg)

Larman tekent een SD per uitwerking van een polymorfe message (figuur 8.21).
BR1 en BR5 hebben elk een eigen vorm.

![SD BR1](diagrams/sd-br1-leeruitkomst-getoetst.svg)

![SD BR5](diagrams/sd-br5-toetsdruk.svg)

BR2, BR3 en BR4 hebben de vorm van BR1, met een andere lus en vraag:

| Regel | Lus over | Vraag per element |
| --- | --- | --- |
| BR2 LesDraagtBijRegel | `owe.geefLessen()` | `les.heeftCriteria()` |
| BR3 CriteriumHeeftLesRegel | `owe.geefCriteria()` | `les.dekt(c)`, voor elke les |
| BR4 CriteriumBeoordeeldRegel | `owe.geefCriteria()` | `t.beoordeelt(c)`, voor elk toetsmoment |

### UC06 Genereren document

Documentsjabloon controleert eerst of de OWE de gegevens heeft (4A) en maakt dan het document.

![SD genereer](diagrams/sd-uc06-genereer.svg)

### UC07 Hergebruiken gedeeld onderdeel

OWERepository vindt alleen gedeelde onderdelen.
Is het origineel verwijderd, dan volgt 4A.
OWE bewaart een verwijzing, geen kopie (BR6).

![SD opnemenOnderdeel](diagrams/sd-uc07-opnemenonderdeel.svg)

Een kopie (3A) loopt via de toevoegoperatie van de OWE (keuze 3).

![SD opnemenKopie](diagrams/sd-uc07-opnemenkopie.svg)

### UC08 Opvragen dekkingsoverzicht

Opleiding vraagt elke OWE om haar dekking.
De gebruikersinterface markeert elke dekking waarvoor `isVolledig()` false geeft.

![SD geefDekking](diagrams/sd-uc08-geefdekking.svg)

OWE kent alle leeruitkomsten, criteria, toetsmomenten en lessen, dus OWE bepaalt de dekking en
maakt de Dekking-objecten (Information Expert, Creator).

![SD OWE.bepaalDekking](diagrams/sd-owe-bepaaldekking.svg)

### UC11 Toevoegen toetsmoment

Dit volgt het patroon van UC04, met BR14 en ToetsdrukRegel (BR5).

![SD toevoegenToetsmoment](diagrams/sd-uc11-toevoegentoetsmoment.svg)

## Keuzes

### Keuze 1: controle bij de gegevens

Probleem: waar staan de controles voor exceptional flows, zoals 4A in UC04?

Alternatief: de handler controleert alle invoer.
Dan kent de handler de regels van het domein en wordt hij een bloated controller.

Keuze: het object met de gegevens controleert ze (Information Expert).
OWE controleert de week en de criteria, Toetsmoment de volgorde van start- en deadlineweek.
De handler controleert alleen of er iets te doen is, zoals 2A in UC05 en UC08.

### Keuze 2: Overtreding kent haar onderdelen

Probleem: UC04 en UC11 melden alleen overtredingen van het nieuwe onderdeel (6A).
Een regel controleert de hele OWE.

Alternatieven:

- Een tweede operatie `controleer(owe, onderdeel)` op elke regel.
  Dan heeft elke regel twee bijna gelijke operaties.
- De handler controleert BR2 zelf.
  Dan staat BR2 op twee plaatsen, en voor BR5 werkt het niet.

Keuze: Overtreding kent haar onderdelen en beantwoordt `betreft(onderdeel)`.
De handler filtert daarmee, en elke regel blijft op één plaats.
Een criterium is geen OWEOnderdeel, dus Overtreding kent voor BR3 en BR4 ook `0..1 criterium`.

### Keuze 3: kopie via toevoegen

Probleem: een kopie (UC07, 3A) moet in de lijst van haar soort, en OWE controleert de week
(BR11, BR14).

Alternatief: OWE of de handler vraagt de kopie en test de soort.
Een test op de soort vervangt Polymorphism door een switch.

Keuze: `Kopieerbaar.kopieerNaar(owe)`.
Een Les roept `owe.toevoegenLes` aan, een Toetsmoment `owe.toevoegenToetsmoment`, zonder
criteria.
Zo controleert OWE de week zoals bij toevoegen.

### Keuze 4: OWE blijft één klasse

Probleem: OWE heeft 19 operaties (keuze 4 in het klassendiagram).

Alternatief: de zoek- en geef-operaties naar een eigen klasse.
Die klasse moet dan alle lijsten van OWE kennen.

Keuze: OWE blijft één klasse.
De SD's tonen dat elke operatie kort is en alleen de eigen lijsten gebruikt, dus de cohesie is
hoog.
