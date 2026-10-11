# Ontwerp

Dit hoofdstuk is de ingang van het ontwerp van ICDE.
Het legt de architectuur vast, geeft een overzicht van de modellen en ontwerpkeuzes, en controleert
of het ontwerp consistent is met de requirements.
De modellen zelf staan in de hoofdstukken die volgen.
Bron: de leeruitkomst Software Design Modeling in de Modulebeschrijving.

## Architectuur

De casus eist dat presentatielaag, domeinlaag en datalaag elk op een eigen server draaien.
Het component diagram toont de lagen en de interfaces ertussen.

![Component diagram van ICDE](diagrams/componentdiagram.svg)

| Component | Inhoud | Server |
| --- | --- | --- |
| Gebruikersinterface | Schermen, buiten dit ontwerp | Webserver |
| Applicatie | De handlers, package `applicatie` | Applicatieserver |
| Domein | Domeinklassen, regels, repository-interfaces, package `domein` | Applicatieserver |
| Datalaag | De implementatie van de repositories | Applicatieserver |
| Database | De gegevens | Databaseserver |

- Systeemoperaties zijn de operaties van de handlers.
  Het zijn de systeemoperaties uit de system sequence diagrams.
- Repositories zijn de interfaces OWERepository, OpleidingRepository,
  DocumentsjabloonRepository en VergrendelingRepository.
  Ze horen bij het domein, en de datalaag implementeert ze (keuze 2 in het klassendiagram).
  De datalaag hangt dus af van het domein, niet andersom.

Keuze A1: waar draait de domeinlogica?

- Probleem: de consistentieregels, de validatieregels en het genereren van documenten moeten
  ergens draaien.
  Meerdere gebruikers werken tegelijk aan dezelfde OWE.
- Alternatief A: in de gebruikersinterface, met een server die alleen gegevens opslaat.
  Dan draait elke regel op elke client.
  Een latere koppeling met Brightspace of Osiris moet de regels opnieuw bouwen.
- Alternatief B: in de database, als stored procedures en constraints.
  Een regel als BR5 (toetsen per week) is dan moeilijk te schrijven en te testen.
  De regels hangen dan af van één databaseproduct, en OO-patterns zoals Strategy zijn niet
  bruikbaar.
- Keuze: een eigen applicatie- en domeinlaag op de applicatieserver.
  Elke regel staat op één plaats, voor alle gebruikers en latere koppelingen.
  Gebruikersinterface en database zijn vervangbaar zonder het domein te wijzigen (Low Coupling).

## Ontwerpmodellen

| Soort | Model | Waar |
| --- | --- | --- |
| Statisch | Component diagram | [Architectuur](#architectuur) |
| Statisch | Design class diagram, in drie diagrammen | [Klassendiagram](08-klassendiagram.md#klassendiagram) |
| Dynamisch | Vier system sequence diagrams | [Sequence diagrams](09-sequencediagrammen.md#system-sequence-diagrams) |
| Dynamisch | Tien sequence diagrams | [Sequence diagrams](09-sequencediagrammen.md#diagrammen-per-use-case) |

ICDE heeft veel interactie tussen objecten, zoals de consistentiecontrole en het
dekkingsoverzicht.
Daarom toont het ontwerp naast statische ook dynamische modellen.

## Ontwerpkeuzes

Elke keuze beschrijft het probleem, de alternatieven en de reden.
Deze tabel geeft het overzicht.
K staat voor een keuze in het [klassendiagram](08-klassendiagram.md#keuzes), S voor een keuze bij
de [sequence diagrams](09-sequencediagrammen.md#keuzes).

| Keuze | Probleem | Principe of pattern |
| --- | --- | --- |
| A1 | Waar draait de domeinlogica? | Low Coupling, lagen |
| K1 | Wie ontvangt een systeemoperatie? | GRASP Controller, SRP |
| K2 | Hoe vindt een handler een object? | Repository, DIP |
| K3 | Welke kant van een associatie is navigeerbaar? | Low Coupling |
| K4 | Wie geeft alle gegevens van een OWE? | Information Expert, information hiding |
| K5 | Waar staan de consistentieregels? | Open/Closed, lijkt op Strategy |
| K6 | Wie maakt een document? | Information Expert, High Cohesion |
| K7 | Hergebruik als verwijzing of kopie? | Polymorphism, Liskov Substitution |
| K8 | Wie maakt een onderdeel? | GRASP Creator |
| K9 | Hoe samenwerken zonder versieconflicten? | Vergrendeling per invoerveld |
| S1 | Waar staat een foutcontrole? | Information Expert |
| S2 | Welke overtredingen horen bij een nieuw onderdeel? | Eén plaats per regel |
| S3 | Hoe komt een kopie in de juiste lijst? | Polymorphism |
| S4 | Is OWE te groot? | High Cohesion |

De verbeteringen uit de [consistentiecontrole](#inconsistenties) hebben ook alternatieven.
De design patterns werken we uit in #9.

## Eisen uit de casus

De [traceerbaarheid](08-klassendiagram.md#traceerbaarheid) in het klassendiagram koppelt elke use
case en elke bedrijfsregel aan het ontwerp.
Deze tabel doet dat voor de eisen uit de casus, de Modulebeschrijving en de wensen van de
opdrachtgever.

| Eis | Ontwerp | Status |
| --- | --- | --- |
| Samenwerken zonder versieconflicten | Vergrendeling (K9) | Ontworpen, #12 |
| Scheiding van inhoud en vorm | Documentsjabloon (K6), UC10 | Ontworpen |
| Document als PDF of Word, geheel of deels | Bestandstype, onderdelen (UC06) | Ontworpen |
| EVL-beschrijving en toetsplanning | SoortDocument, zie onder | Ontworpen |
| Gegevensvalidatie van een OWE | Validatie in de domeinklassen (S1), UC05 | Ontworpen |
| Inconsistenties detecteren | Consistentieregel en vijf regels (K5) | Ontworpen |
| Lessen sluiten aan op toetsen | CriteriumHeeftLesRegel, CriteriumBeoordeeldRegel | Ontworpen |
| Meer dan 3 toetsen in een week | ToetsdrukRegel (BR5), ook in UC11 | Ontworpen |
| Onderdelen delen binnen HBO-ICT | OWEOnderdeel.deel, OWE.hergebruik (K7) | Ontworpen |
| Overzicht van de dekking | Opleiding.bepaalDekking, Dekking.voegToe | Ontworpen |
| Uitbreidbaar | Nieuwe regel is een nieuwe klasse, nieuw sjabloon is data | Ontworpen |
| Drie servers | Component diagram, A1 | Ontworpen, uitwerking in #10 en #14 |
| Inloggen door ICDE zelf | Geen, zie C1 | Open, #10 |
| Iterative Grading | Geen, ICDE legt geen beoordelingen vast | Buiten het prototype |
| Koppeling Brightspace, Osiris | Geen, het prototype heeft geen koppeling | Buiten het prototype |

De toetsplanning als tabel en als overzicht per week zijn twee documentsjablonen van de soort
TOETSPLANNING.
Een latere koppeling roept dezelfde systeemoperaties aan als de gebruikersinterface.

## Consistentie met de requirements

We controleren het ontwerp in twee richtingen, zoals bij de
[validatie van het domeinmodel](06-domeinmodel-validatie.md#validatie-domeinmodel).
Van requirement naar ontwerp: elke use case, bedrijfsregel en eis heeft een klasse en een operatie.
Van ontwerp naar requirement: elke klasse en operatie dient een use case, regel of eis.

### Wat klopt

- Elke use case heeft een handler, zie de traceerbaarheid in het klassendiagram.
- Elke bedrijfsregel heeft een klasse die haar controleert.
  Acht regels staan ook in een sequence diagram.
- Elke systeemoperatie uit de SSD's is een operatie van een handler, met dezelfde naam en
  parameters.
- Elk sequence diagram gebruikt alleen operaties en associaties uit het klassendiagram.
  Getters en constructors zijn de uitzondering, zie de aanpak in de sequence diagrams.
- Elke klasse komt voor in een use case, bedrijfsregel of eis.
  Handlers en repositories dienen de systeemoperaties.
  Overtreding en Dekking dienen UC05 en UC08, Vergrendeling dient het samenwerken.
- Elke exceptional flow van de uitgewerkte use cases geeft een OngeldigeInvoerException.

### Inconsistenties

C2 hebben we in deze versie verwerkt.
C1 werken we uit in #10.

1. C1: elke use case eist een ingelogde gebruiker, en ICDE regelt het inloggen zelf.
   Onderwijsontwikkelaar en opleidingscoördinator zijn aparte rollen.
   UC08 en UC09 zijn alleen voor de opleidingscoördinator, UC10 alleen voor de functioneel
   beheerder.
   Het ontwerp kent geen gebruiker of rol.
   Alleen VergrendelVeldHandler haalt de gebruiker uit de sessie (K9).
   - Alternatief: elke systeemoperatie krijgt de gebruiker als parameter.
     Dan kan een client zich voordoen als een andere gebruiker.
   - Verbetering: de remote facade in #10 regelt het inloggen en controleert de rol per handler.
     Omdat use cases van verschillende actoren geen handler delen (K1), is dat één controle per
     handler.
2. C2: UC07 3A neemt een kopie op, maar de use case had geen extensie voor een kopie die BR11 of
   BR14 overtreedt.
   Een les in week 8 past niet in een OWE van 7 weken.
   Het ontwerp gooit dan een OngeldigeInvoerException (SD opnemenKopie).
   - Alternatief: de kopie krijgt de laatste week van de eigen OWE.
     Dan wijzigt het systeem gegevens zonder dat de ontwikkelaar het weet.
   - Verbetering: UC07 krijgt de extensie 3A2A, die de ongeldige week meldt.

## Overdracht naar blok 2

Dit ontwerp is de basis voor de gedistribueerde applicatie.
Deze punten liggen nog open, met het issue dat ze uitwerkt:

| Issue | Wat het ontwerp vastlegt | Wat nog open is |
| --- | --- | --- |
| #9 | Consistentieregel als interface, Kopieerbaar | Design patterns uitwerken |
| #10 | Systeemoperaties op de handlers | Remote facade, DTO's, inloggen en rolcontrole (C1) |
| #11 | Grens tussen gebruikersinterface en applicatie | REST-resources |
| #12 | Repository-interfaces, Vergrendeling | Data source pattern, duur van een vergrendeling |
| #13 | Schermen buiten het ontwerp | Presentatiepattern |
| #14 | Lagen en componenten | Talen, frameworks, template-engine voor Documentsjabloon |
| #15 | Drie servers | Deployment |

De open punten van de requirements staan in
[Use case beschrijvingen](04-use-case-beschrijvingen.md#open-punten) en
[Domeinmodel](05-domeinmodel.md#open-punten).
