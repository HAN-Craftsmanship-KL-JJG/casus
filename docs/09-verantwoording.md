# Verantwoording

Dit hoofdstuk koppelt de eisen uit de casus aan het ontwerp, en controleert of het ontwerp
consistent is met de requirements.

## Eisen uit de casus

De [traceerbaarheid](07-klassendiagram.md#traceerbaarheid) koppelt de use cases en
bedrijfsregels aan het ontwerp.
Deze tabel doet dat voor de eisen uit de casus en de wensen van de opdrachtgever.

| Eis | Ontwerp | Status |
| --- | --- | --- |
| Samenwerken zonder versieconflicten | Vergrendeling (K8) | Ontworpen |
| Scheiding van inhoud en vorm | Documentsjabloon (K5), UC10 | Ontworpen |
| Document als PDF of Word, geheel of deels | Bestandstype, onderdelen (UC06) | Ontworpen |
| EVL-beschrijving en toetsplanning | SoortDocument, zie onder | Ontworpen |
| Gegevensvalidatie van een OWE | Validatie in de domeinklassen (S1), UC05 | Ontworpen |
| Inconsistenties detecteren | Consistentieregel en vijf regels (K4) | Ontworpen |
| Lessen sluiten aan op toetsen | CriteriumHeeftLesRegel, CriteriumBeoordeeldRegel | Ontworpen |
| Meer dan 3 toetsen in een week | ToetsdrukRegel (BR5), ook in UC11 | Ontworpen |
| Onderdelen delen binnen HBO-ICT | OWEOnderdeel.deel, OWE.hergebruik (K6) | Ontworpen |
| Overzicht van de dekking | Opleiding.bepaalDekking, Dekking.voegToe | Ontworpen |
| Uitbreidbaar | Nieuwe regel is een nieuwe klasse, nieuw sjabloon is data | Ontworpen |
| Inloggen door ICDE zelf | Geen, zie C1 | Open, blok 2 |
| Iterative Grading | Geen, ICDE legt geen beoordelingen vast | Buiten het prototype |
| Koppeling Brightspace, Osiris | Geen, het prototype heeft geen koppeling | Buiten het prototype |

De toetsplanning als tabel en als overzicht per week zijn twee documentsjablonen van de soort
TOETSPLANNING.
Een latere koppeling roept dezelfde systeemoperaties aan als de gebruikersinterface.

## Consistentie met de requirements

De controle gaat in twee richtingen, zoals bij de
[validatie van het domeinmodel](05-domeinmodel.md#validatie).
Elke use case, bedrijfsregel en eis heeft een klasse en een operatie.
Elke klasse en operatie dient een use case, regel of eis.

### Wat klopt

- Elke use case heeft een handler, zie de traceerbaarheid in het klassendiagram.
- Elke bedrijfsregel heeft een klasse die haar controleert.
  Acht regels staan ook in een sequence diagram.
- Elke systeemoperatie uit de SSD's is een operatie van een handler, met dezelfde naam en
  parameters.
- Elk sequence diagram gebruikt alleen operaties en associaties uit het klassendiagram, met
  getters en constructors als uitzondering.
- Handlers en repositories dienen de systeemoperaties.
  Overtreding en Dekking dienen UC05 en UC08, Vergrendeling dient het samenwerken.
- Elke exceptional flow van de uitgewerkte use cases geeft een OngeldigeInvoerException.

### Inconsistenties

C2 is in deze versie verwerkt, C1 volgt in blok 2.

#### C1 Het ontwerp kent geen gebruiker of rol

Probleem: elke use case eist een ingelogde gebruiker, en ICDE regelt het inloggen zelf.
Onderwijsontwikkelaar en opleidingscoördinator zijn aparte rollen.
UC08 en UC09 zijn alleen voor de opleidingscoördinator, UC10 alleen voor de functioneel beheerder.
Het ontwerp kent geen gebruiker of rol.
Alleen VergrendelVeldHandler haalt de gebruiker uit de sessie (K8).

Alternatief: elke systeemoperatie krijgt de gebruiker als parameter.
Dan kan een client zich voordoen als een andere gebruiker.

Verbetering: de remote facade regelt het inloggen en controleert de rol.
Use cases van verschillende actoren delen geen handler (K1), dus dat is één controle per handler.

#### C2 Een kopie kan buiten de looptijd vallen

Probleem: UC07 flow 3A neemt een kopie op, maar de use case had geen flow voor een kopie die BR11
of BR14 overtreedt.
Een les in week 8 past niet in een OWE van 7 weken.
Het ontwerp gooit dan een OngeldigeInvoerException (SD opnemenKopie).

Alternatief: de kopie krijgt de laatste week van de eigen OWE.
Dan wijzigt het systeem gegevens zonder dat de ontwikkelaar het weet.

Verbetering: UC07 krijgt flow 3A2A, die de ongeldige week meldt.
