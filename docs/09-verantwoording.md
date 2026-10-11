# Verantwoording

De vorige hoofdstukken tonen het ontwerp.
Dit hoofdstuk zet de ontwerpkeuzes op een rij, koppelt de eisen uit de casus aan het ontwerp, en
controleert of het ontwerp consistent is met de requirements.

## Ontwerpkeuzes

Elke keuze beschrijft het probleem, de alternatieven en de reden.
Deze tabel geeft het overzicht van de keuzes in het ontwerp.
De keuzes in het domeinmodel (D1 tot en met D5) staan in het hoofdstuk
[Domeinmodel](05-domeinmodel.md#keuzes).

| Keuze | Probleem | Principe of pattern |
| --- | --- | --- |
| [A1](06-architectuur.md#keuzes) | Waar draait de domeinlogica? | Low Coupling, lagen |
| [K1](07-klassendiagram.md#keuzes) | Wie ontvangt een systeemoperatie? | GRASP Controller, SRP |
| K2 | Hoe vindt een handler een object? | Repository, DIP |
| K3 | Welke kant van een associatie is navigeerbaar? | Low Coupling |
| K4 | Wie geeft alle gegevens van een OWE? | Information Expert, information hiding |
| K5 | Waar staan de consistentieregels? | Open/Closed, lijkt op Strategy |
| K6 | Wie maakt een document? | Information Expert, High Cohesion |
| K7 | Hergebruik als verwijzing of kopie? | Polymorphism, Liskov Substitution |
| K8 | Wie maakt een onderdeel? | GRASP Creator |
| K9 | Hoe samenwerken zonder versieconflicten? | Vergrendeling per invoerveld |
| [S1](08-sequencediagrammen.md#keuzes) | Waar staat een foutcontrole? | Information Expert |
| S2 | Welke overtredingen horen bij een nieuw onderdeel? | Eén plaats per regel |
| S3 | Hoe komt een kopie in de juiste lijst? | Polymorphism |
| S4 | Is OWE te groot? | High Cohesion |

De verbeteringen uit de [consistentiecontrole](#inconsistenties) hebben ook alternatieven.

## Eisen uit de casus

De [traceerbaarheid](07-klassendiagram.md#traceerbaarheid) in het klassendiagram koppelt elke use
case en elke bedrijfsregel aan het ontwerp.
Deze tabel doet dat voor de eisen uit de casus, de Modulebeschrijving en de wensen van de
opdrachtgever.

| Eis | Ontwerp | Status |
| --- | --- | --- |
| Samenwerken zonder versieconflicten | Vergrendeling (K9) | Ontworpen |
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
| Drie servers | Component diagram, A1 | Ontworpen, uitwerking in blok 2 |
| Inloggen door ICDE zelf | Geen, zie C1 | Open, blok 2 |
| Iterative Grading | Geen, ICDE legt geen beoordelingen vast | Buiten het prototype |
| Koppeling Brightspace, Osiris | Geen, het prototype heeft geen koppeling | Buiten het prototype |

De toetsplanning als tabel en als overzicht per week zijn twee documentsjablonen van de soort
TOETSPLANNING.
Een latere koppeling roept dezelfde systeemoperaties aan als de gebruikersinterface.

## Consistentie met de requirements

We controleren het ontwerp in twee richtingen, zoals bij de
[validatie van het domeinmodel](05-domeinmodel.md#validatie).
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

Elke inconsistentie noemt het probleem, een alternatief en de verbetering.
C2 hebben we in deze versie verwerkt.
C1 volgt in blok 2.

#### C1 Het ontwerp kent geen gebruiker of rol

Probleem: elke use case eist een ingelogde gebruiker, en ICDE regelt het inloggen zelf.
Onderwijsontwikkelaar en opleidingscoördinator zijn aparte rollen.
UC08 en UC09 zijn alleen voor de opleidingscoördinator, UC10 alleen voor de functioneel beheerder.
Het ontwerp kent geen gebruiker of rol.
Alleen VergrendelVeldHandler haalt de gebruiker uit de sessie (K9).

Alternatief: elke systeemoperatie krijgt de gebruiker als parameter.
Dan kan een client zich voordoen als een andere gebruiker.

Verbetering: de remote facade regelt het inloggen en controleert de rol per handler.
Omdat use cases van verschillende actoren geen handler delen (K1), is dat één controle per
handler.

#### C2 Een kopie kan buiten de looptijd vallen

Probleem: UC07 flow 3A neemt een kopie op, maar de use case had geen flow voor een kopie die BR11
of BR14 overtreedt.
Een les in week 8 past niet in een OWE van 7 weken.
Het ontwerp gooit dan een OngeldigeInvoerException (SD opnemenKopie).

Alternatief: de kopie krijgt de laatste week van de eigen OWE.
Dan wijzigt het systeem gegevens zonder dat de ontwikkelaar het weet.

Verbetering: UC07 krijgt flow 3A2A, die de ongeldige week meldt.
