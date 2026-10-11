# Klassendiagram ICDE

Dit document toont het statische ontwerp van ICDE als design class diagram (DCD).
Het legt ook uit waarom het ontwerp zo is.
Het bouwt voort op het [domeinmodel](domeinmodel.md) en de
[use case beschrijvingen](use-case-beschrijvingen.md).

Bronnen: Larman hoofdstuk 7 (UML Class Diagrams) en 17 (GRASP).

## Klassendiagrammen

Het ontwerp staat in drie diagrammen, zodat elk diagram leesbaar blijft.

| Diagram | Inhoud |
| --- | --- |
| Domeinklassen | De concepten uit het domeinmodel als softwareklassen |
| Consistentieregels en dekking | De klassen voor UC05 en UC08 |
| Handlers en repositories | De klassen die systeemoperaties ontvangen en objecten ophalen |

### Domeinklassen

![Domeinklassen van ICDE](diagrams/klassendiagram-domein.svg)

Bron: [klassendiagram-domein.puml](diagrams/klassendiagram-domein.puml).

### Consistentieregels en dekking

![Consistentieregels en dekking van ICDE](diagrams/klassendiagram-controle.svg)

Bron: [klassendiagram-controle.puml](diagrams/klassendiagram-controle.puml).

### Handlers en repositories

![Handlers en repositories van ICDE](diagrams/klassendiagram-handlers.svg)

Bron: [klassendiagram-handlers.puml](diagrams/klassendiagram-handlers.puml).

## Aanpak

Een associatie heeft geen naam.
Multipliciteit en rolnaam staan alleen aan de doelkant (Larman 7.4).

De systeemoperaties komen uit de system sequence diagrams in
[sequencediagrammen.md](sequencediagrammen.md).
We verdelen de verantwoordelijkheden met de GRASP-patterns Controller, Creator, Information
Expert, Low Coupling en High Cohesion.
De sequence diagrams controleren dit ontwerp.

## Van domeinmodel naar ontwerp

Het domeinmodel toont de werkelijkheid, het klassendiagram de software.
De elf concepten uit het domeinmodel zijn elf klassen gebleven, met dezelfde naam.
Alleen het streepje valt weg: OWE-onderdeel heet OWEOnderdeel.
Net als het domeinmodel gebruikt het klassendiagram geen compositie (domeinmodel, keuze 5).

Dit veranderde:

| Wat | Domeinmodel | Klassendiagram |
| --- | --- | --- |
| Attributen | Alleen een naam | Visibility private en een datatype |
| Operaties | Geen | Uit de stappen van de use cases |
| Associaties | Naam, geen richting | Pijl, rolnaam en multipliciteit aan de doelkant |
| soort, soortDocument | Een attribuut | Enumeraties SoortToetsmoment en SoortDocument |
| onderdelen, volgorde | Twee attributen van Documentsjabloon | Eén geordende lijst onderdelen |
| Bestandstype | Geen attribuut | Enumeratie Bestandstype, een parameter van UC06 |
| OWE-onderdeel | Alleen gedeeld | Ook een id (UUID), uniek over alle OWE's heen |
| Nieuwe klassen | Geen | Handlers, repositories, regels, Overtreding, Dekking, Vergrendeling |
| Kopieerbaar | Geen | Interface voor de onderdelen die UC07 kan kopiëren |

Met het id wijzen UC07 en UC09 een onderdeel aan.

## Keuzes

Elke keuze noemt het probleem, de alternatieven en de onderbouwing.

| Nr | Keuze | Principe |
| --- | --- | --- |
| 1 | [Een handler per use case](#een-handler-per-use-case) | GRASP Controller |
| 2 | [Repositories vinden de objecten](#repositories-vinden-de-objecten) | DIP |
| 3 | [Associaties in één richting](#associaties-in-één-richting) | Low Coupling |
| 4 | [OWE geeft alle gegevens van een OWE](#owe-geeft-alle-gegevens-van-een-owe) | Expert |
| 5 | [Een klasse per consistentieregel](#een-klasse-per-consistentieregel) | Open/Closed |
| 6 | [Documentsjabloon maakt het document](#documentsjabloon-maakt-het-document) | Expert |
| 7 | [Hergebruik: verwijzing of kopie](#hergebruik-verwijzing-of-kopie) | Polymorphism |
| 8 | [De eigenaar maakt een onderdeel](#de-eigenaar-maakt-een-onderdeel) | GRASP Creator |
| 9 | [Een vergrendeling per invoerveld](#een-vergrendeling-per-invoerveld) | |

DIP is het Dependency Inversion Principle, Expert is GRASP Information Expert.

### Een handler per use case

Probleem: ICDE heeft 11 use cases met samen meer dan 30 systeemoperaties.
Welke klasse ontvangt ze (GRASP Controller)?

| Alternatief | Nadeel |
| --- | --- |
| Eén facade controller ICDE | Alle operaties in één klasse: lage cohesie (bloated controller) |
| Altijd één handler per use case | 11 handlers, en vier doen hetzelfde |

De vier gelijke handlers halen een OWE op, voegen een onderdeel toe en bewaren de OWE.

Keuze: een use case controller per use case.
De naam is de naam van de use case met het achtervoegsel Handler, zoals bij Larman.
CRUD use cases van dezelfde actor over dezelfde gegevens delen een handler, tot ongeveer 10
systeemoperaties.

- UC01 en UC02 delen BeheerOWEHandler.
- UC04 en UC11 delen BeheerPlanningHandler.
- UC03 heeft met dimensies, criteria en niveaus genoeg operaties voor een eigen handler.

Use cases van verschillende actoren delen geen handler, omdat ze om verschillende redenen
veranderen (Single Responsibility Principle).
Daarom hebben UC07 en UC09 elk een eigen handler, net als UC05 en UC08.

### Repositories vinden de objecten

Probleem: een handler krijgt een code of naam en moet het object vinden.
De database draait op een eigen server, zoals de casus eist.

| Alternatief | Nadeel |
| --- | --- |
| Een rootobject Catalogus, zoals Store bij Larman | Laadt alle opleidingen voor elke vraag |
| Statische zoekoperaties, zoals OWE.zoek(code) | Elke domeinklasse kent de database |

Een domeinklasse die de database kent, is ook moeilijk te testen.

Keuze: een repository-interface per ingang.
Dat zijn OWERepository, OpleidingRepository, DocumentsjabloonRepository en
VergrendelingRepository.
De interface hoort bij het domein, de implementatie bij de datalaag.
Zo hangt het domein niet af van de database (Dependency Inversion Principle).
Welk data source pattern de implementatie gebruikt, bepalen we in #12.

### Associaties in één richting

Probleem: welke kant van een associatie is navigeerbaar?

| Alternatief | Nadeel |
| --- | --- |
| Beide richtingen | Dubbele koppeling, en beide kanten moeten gelijk blijven |

Keuze: elke associatie gaat één kant op (Low Coupling).

- Van eigenaar naar onderdeel.
- Van les of toetsmoment naar criterium.

Er is geen cyclus.
Een vraag in de andere richting gaat naar een klasse met overzicht:

- "Welke lessen dragen bij aan dit criterium?" beantwoordt OWE, want die kent alle lessen.
- "Hergebruikt een andere OWE dit onderdeel?" (BR13) beantwoordt
  OWERepository.wordtHergebruikt.
- "Welke onderdelen zijn gedeeld?" (UC07) beantwoordt OWERepository.zoekGedeeldeOnderdelen.

### OWE geeft alle gegevens van een OWE

Probleem: de consistentieregels, de dekking en de documenten hebben alle leeruitkomsten,
criteria, lessen en toetsmomenten van een OWE nodig.
Daar horen ook de hergebruikte onderdelen bij.

| Alternatief | Nadeel |
| --- | --- |
| Elke regel zoekt zelf in EVL's, dimensies en hergebruik | Elke regel kent de structuur van OWE |

Keuze: OWE heeft geefLeeruitkomsten, geefCriteria, geefLessen en geefToetsmomenten (Information
Expert).
Ze geven eigen en hergebruikte onderdelen samen.
De rest van het systeem ziet het verschil niet (information hiding).
Nadeel: OWE heeft 19 operaties.
Keuze 4 in [sequencediagrammen.md](sequencediagrammen.md#keuze-4-owe-blijft-één-klasse) weegt dat af.

### Een klasse per consistentieregel

Probleem: UC05 past BR1 tot en met BR5 toe.
De opdrachtgever kan regels toevoegen of wijzigen, zie de open punten van de use cases.

| Alternatief | Nadeel |
| --- | --- |
| Een operatie per regel in OWE | OWE krijgt meer taken, en elke nieuwe regel wijzigt OWE |
| Alle regels in ControleerConsistentieHandler | Domeinlogica in de handler, geen hergebruik |

Zonder hergebruik kunnen UC04 en UC11 de regels niet gebruiken.

Keuze: een interface Consistentieregel, met een klasse per regel.

- ControleerConsistentieHandler loopt de lijst regels af en weet niet welke regels er zijn.
- Een nieuwe regel is een nieuwe klasse, zonder wijziging van bestaande code (Open/Closed
  Principle).
- BeheerPlanningHandler hergebruikt LesDraagtBijRegel voor BR2 (UC04, stap 6).
- BeheerPlanningHandler hergebruikt ToetsdrukRegel voor BR5 (UC11, stap 6).
- ToetsdrukRegel heeft het maximum als attribuut.
  Een andere grens vraagt dus geen nieuwe klasse.

Deze opzet lijkt op het Strategy pattern.
De design patterns werken we uit in #9.

### Documentsjabloon maakt het document

Probleem: ICDE scheidt inhoud en vorm (UC06).

| Alternatief | Nadeel |
| --- | --- |
| OWE.genereer(sjabloon) | OWE kent dan de opmaak, en dat is niet zijn taak (High Cohesion) |
| Een generatorklasse per soort document | Een nieuwe soort document vraagt een programmeur |

De functioneel beheerder wil sjablonen aanpassen zonder programmeur (UC10).

Keuze: Documentsjabloon maakt het document, want het kent zijn onderdelen en opmaak
(Information Expert).

- zoekOntbrekendeGegevens voert stap 4 uit, genereer stap 5.
- Beide krijgen de onderdelen die de ontwikkelaar in stap 3 koos.
  Een lege lijst betekent alle onderdelen van het sjabloon (flow 3A).
- genereer geeft de inhoud van een PDF- of Word-bestand terug, daarom byte[].
- Documentsjabloon kent OWE alleen als parameter: een dependency, geen associatie.

Welke template-engine het bestand maakt, is een technologiekeuze voor blok 2.

### Hergebruik: verwijzing of kopie

Probleem: UC07 neemt een gedeeld onderdeel op in een OWE.
Een verwijzing toont altijd de actuele versie (BR6).
Een kopie hangt niet meer af van het origineel (flow 3A).
Een kopie kan alleen van een les of toetsmoment.

Lijst (stap 2): HergebruikOnderdeelHandler.geefGedeeldeOnderdelen haalt alle gedeelde onderdelen
op.
Het laat de onderdelen weg die de OWE al bevat (OWE.bevat).

Verwijzing (stap 4): OWE.hergebruik voegt het originele object toe aan de lijst hergebruikt.
Er is geen kopie, dus de OWE ziet elke wijziging meteen.

Kopie (flow 3A):

| Alternatief | Nadeel |
| --- | --- |
| De gebruikersinterface vult het toevoegscherm met het origineel | Flow 3A heeft die stap niet |

In flow 3A neemt het systeem de kopie zelf op, zonder invoer van de ontwikkelaar.

Keuze: een interface Kopieerbaar met de operatie kopieerNaar(owe), die Les en Toetsmoment elk op
hun eigen manier uitwerken (Polymorphism).

- Leeruitkomst en Beoordelingsdimensie zijn niet Kopieerbaar.
  Een gekopieerde leeruitkomst heeft een EVL en een nieuw nummer nodig (BR9).
  Een gekopieerd criterium verliest zijn leeruitkomsten, terwijl het er minstens één toetst.
- Een abstracte kopieer op OWEOnderdeel zou bij twee van de vier subklassen een fout geven.
  Dat schendt het Liskov Substitution Principle.
- HergebruikOnderdeelHandler.opnemenKopie controleert dat het onderdeel Kopieerbaar is.
- Les.kopieerNaar roept owe.toevoegenLes aan, Toetsmoment.kopieerNaar owe.toevoegenToetsmoment.
  Zo controleert OWE BR11 en BR14 net als bij toevoegen, zonder de soort te testen
  (keuze 3 in [sequencediagrammen.md](sequencediagrammen.md#keuze-3-kopie-via-toevoegen)).
- De kopie heeft geen koppelingen met criteria, want die horen bij de andere OWE.
  Les en Toetsmoment mogen 0 criteria hebben, en UC05 meldt dat (BR2, BR4).
  De ontwikkelaar koppelt de kopie daarna aan eigen criteria.

Origineel verwijderd (flow 4A): OWERepository.zoekGedeeldOnderdeel vindt het niet, en de handler
meldt dat.

### De eigenaar maakt een onderdeel

Probleem: welke klasse maakt een nieuw onderdeel (GRASP Creator)?

Keuze: de klasse die het onderdeel bevat.

| Klasse | Maakt |
| --- | --- |
| Opleiding | OWE, met de eerste EVL |
| OWE | EVL, Beoordelingsdimensie met het eerste criterium, Les en Toetsmoment |
| EVL | Leeruitkomst |
| Beoordelingsdimensie | Beoordelingscriterium |

Gevolgen:

- Opleiding.maakOWE krijgt de gegevens van de eerste EVL mee, want BR8 eist minstens één EVL.
  Zo bestaat er geen OWE zonder EVL.
- OWE.toevoegenDimensie krijgt de gegevens van het eerste criterium mee, want een dimensie
  bestaat uit minstens één criterium (BR10).
- Verwijderen weigert het laatste exemplaar.
  OWE.verwijderEVL weigert de laatste EVL (BR8) en een EVL met leeruitkomsten (BR9).
  Beoordelingsdimensie.verwijderCriterium weigert het laatste criterium (BR10).
- OWE krijgt bij een les of toetsmoment de criteriumcodes, niet de criteria zelf.
  OWE zoekt ze op in de eigen en hergebruikte dimensies (zoekCriteria).
  Een code van een andere OWE vindt OWE niet, en dat geeft een fout.
  Zo dwingt het ontwerp BR11 en BR14 af.
- De private operatie controleerWeek controleert onderwijsweek, startweek en deadlineweek
  (BR11, BR14).

### Een vergrendeling per invoerveld

Probleem: twee ontwikkelaars wijzigen tegelijk dezelfde OWE.
De opdrachtgever wil dat een invoerveld geblokkeerd is zolang iemand het wijzigt.
De rest van de OWE blijft bewerkbaar.

| Alternatief | Nadeel |
| --- | --- |
| Een versienummer op OWE, bewaar weigert een oude versie | Het conflict blijkt pas bij opslaan |
| De hele OWE vergrendelen | De tweede ontwikkelaar wacht, ook bij een ander veld |

Bij een versienummer is het werk van de tweede ontwikkelaar verloren.

Keuze: een Vergrendeling per veld.

- Gaat een ontwikkelaar een veld in, dan vraagt de gebruikersinterface
  VergrendelVeldHandler.vergrendel aan.
- Heeft een ander het veld al, dan geeft vergrendel false, en blokkeert de gebruikersinterface
  het veld.
- Invoer gaat real-time naar de backend, dus er is geen aparte stap opslaan.
  Verlaat de ontwikkelaar het veld, dan volgt ontgrendel.
- onderdeelId is leeg voor een veld van de OWE zelf.
- De handler haalt de ingelogde gebruiker uit de sessie, niet uit een parameter.
  Zo kan een client geen veld van een ander ontgrendelen.

VergrendelVeldHandler is een eigen handler, omdat elke wijzig-use case hem gebruikt.

## Traceerbaarheid

### Per use case

| Use case | Handler | Klassen en operaties |
| --- | --- | --- |
| UC01 | BeheerOWEHandler | Opleiding.maakOWE, OWE.toevoegenEVL, OWE.verwijderEVL |
| UC02 | BeheerOWEHandler | OWE.toevoegenLeeruitkomst, EVL.toevoegenLeeruitkomst |
| UC03 | BeheerRubricHandler | OWE.toevoegenDimensie, Beoordelingsdimensie.toevoegenCriterium |
| UC04 | BeheerPlanningHandler | OWE.toevoegenLes, LesDraagtBijRegel |
| UC05 | ControleerConsistentieHandler | Consistentieregel met vijf regels, Overtreding |
| UC06 | GenereerDocumentHandler | Documentsjabloon.zoekOntbrekendeGegevens, genereer |
| UC07 | HergebruikOnderdeelHandler | OWE.bevat, OWE.hergebruik, Kopieerbaar.kopieerNaar |
| UC08 | OpvragenDekkingHandler | Opleiding.bepaalDekking, OWE.bepaalDekking, Dekking |
| UC09 | DeelOnderdeelHandler | OWEOnderdeel.deel |
| UC10 | BeheerDocumentsjabloonHandler | Documentsjabloon |
| UC11 | BeheerPlanningHandler | OWE.toevoegenToetsmoment, ToetsdrukRegel |

De namen van de use cases staan in [use-cases.md](use-cases.md#use-cases).

Verwijderen gaat zo:

- Een leeruitkomst, dimensie, les of toetsmoment: BeheerOWEHandler.verwijderOnderdeel en
  OWE.verwijder.
  Eén operatie is genoeg, omdat het allemaal een OWEOnderdeel is.
- Een criterium is geen OWEOnderdeel: BeheerRubricHandler.verwijderCriterium en
  Beoordelingsdimensie.verwijderCriterium.
- Een EVL is geen OWEOnderdeel: BeheerOWEHandler.verwijderEVL en OWE.verwijderEVL.
- Een OWE: BeheerOWEHandler.verwijderOWE en OWERepository.verwijder.

### Per bedrijfsregel

Per regel de klasse die de regel controleert, en het sequence diagram (SD) dat de regel toont.
De regels zonder SD horen bij CRUD use cases, zie
[sequencediagrammen.md](sequencediagrammen.md#aanpak).

| Regel | Klasse en operatie | SD |
| --- | --- | --- |
| BR1 | LeeruitkomstGetoetstRegel, met Beoordelingscriterium.toetst | BR1 |
| BR2 | LesDraagtBijRegel, met Les.heeftCriteria | controleer, toevoegenLes |
| BR3 | CriteriumHeeftLesRegel, met Les.dekt | controleer |
| BR4 | CriteriumBeoordeeldRegel, met Toetsmoment.beoordeelt | controleer |
| BR5 | ToetsdrukRegel, met Toetsmoment.omvat | BR5, toevoegenToetsmoment |
| BR6 | OWE.hergebruik bewaart een verwijzing, geen kopie | opnemenOnderdeel |
| BR7 | Alleen de OWE die het onderdeel in de eigen lijsten heeft, wijzigt het | - |
| BR8 | Opleiding.maakOWE met de eerste EVL, OWE.verwijderEVL, OWERepository.zoek | - |
| BR9 | EVL.toevoegenLeeruitkomst, met OWE voor een uniek nummer | - |
| BR10 | OWE.toevoegenDimensie, Beoordelingsdimensie.toevoegenCriterium, verwijderCriterium | - |
| BR11 | OWE.toevoegenLes, met controleerWeek en zoekCriteria | toevoegenLes, opnemenKopie |
| BR12 | BeheerDocumentsjabloonHandler, met DocumentsjabloonRepository.zoek | - |
| BR13 | verwijderOnderdeel, verwijderCriterium, verwijderOWE, OWERepository.wordtHergebruikt | - |
| BR14 | OWE.toevoegenToetsmoment, met controleerWeek en zoekCriteria | toevoegenToetsmoment |

## Wat niet in de diagrammen staat

- Getters en setters.
  Ze voegen veel regels toe en weinig informatie (Larman 7.6).
- Constructors.
  De operaties die een object maken, tonen al wie wat maakt
  (zie [De eigenaar maakt een onderdeel](#de-eigenaar-maakt-een-onderdeel)).
- Wijzigen en bekijken bij de CRUD use cases.
  Die volgen het CRUD-sjabloon, met dezelfde parameters als toevoegen.
  De diagrammen tonen toevoegen, net als de use case beschrijvingen.
- Foutmeldingen.
  Een operatie die een validatieregel of een exceptional flow tegenkomt, gooit een
  OngeldigeInvoerException met de melding.
  Voorbeelden: flow 2A van UC05, en flow 4A van UC04, UC06, UC07 en UC11.
- De gebruikersinterface en de implementatie van de repositories.
  Die horen bij de technologiekeuze in blok 2.

## Open punten

- ICDE geeft domeinobjecten terug aan de gebruikersinterface, zoals List<OWEOnderdeel> in UC07.
  De gebruikersinterface draait op een eigen server, dus dat worden Data Transfer Objects (#10).
- Een Vergrendeling blijft staan als een ontwikkelaar de browser sluit zonder op te slaan.
  Hoe lang een vergrendeling geldt, stemmen we af met de opdrachtgever.
- UC07 flow 3A heeft geen extensie voor een kopie die BR11 of BR14 overtreedt, bijvoorbeeld een
  les buiten de looptijd van de eigen OWE.
  toevoegenLes of toevoegenToetsmoment gooit dan een OngeldigeInvoerException.
