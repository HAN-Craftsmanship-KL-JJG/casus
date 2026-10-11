# OOSE-DT — Casusopdracht

Dit is de opdrachtrepository voor de module **OOSE Deeltijd** (Object-Oriented Software Engineering), studiejaar 2026/2027. Je werkt in teamverband aan een casus die over beide blokken loopt: **SAD** (Software Analysis & Design, blok 1) en **DAD** (Distributed Application Development, blok 2). Deze repository fork of clone je (binnen de GitHub-organisatie [aim-oose-dt](https://github.com/aim-oose-dt)) om met de casus te starten.

> De casus bestaat uit beroepsproductdelen B_Casus1 (SAD) en B_Casus2 (DAD).

## De opdracht

Je kiest als team tussen twee opties:

1. De standaard **ICDE-casus** (Integrated Course Design Environment).
2. Een **eigen casus** die voldoet aan de generieke eisen.

> Oorspronkelijke opdracht in Brightspace: https://leren.han.nl/d2l/home/110865
> - ICDE-casus: https://leren.han.nl/d2l/le/lessons/110865/topics/895841
> - Eigen casus (eisen): https://leren.han.nl/d2l/le/lessons/110865/topics/895844

## Optie 1: Standaardcasus ICDE

**Auteurs/opdrachtgevers:** Christian Köppe en Rody Middelkoop.

### Inleiding

De auteurs hebben het OOSE-deeltijdsemester ontwikkeld met behulp van Educational Patterns en Assessment-Driven Course Design. Ze zijn begonnen bij de leeruitkomsten en hebben van daaruit de beoordelingsdimensies en -criteria (rubrics) bepaald, gevolgd door een planning van toetsmomenten. Daaruit is een lesplanning met bijbehorende didactiek afgeleid, waarbij Hybrid Pedagogy en Constructive Alignment zijn toegepast en beoordelingscriteria expliciet aan lesinhoud zijn gekoppeld.

Tijdens dit strikte proces liepen ze tegen een aantal problemen aan:

- Er waren meerdere, onderling inconsistente formaten voor OWE-beschrijvingen in gebruik.
- Er was geen duidelijk format voor beoordelingscriteria of voor de lesplanning.
- Er was geen eenvoudig overzicht om te controleren of alle leeruitkomsten voldoende werden afgedekt.

De handmatige consistentiecontroles bleken foutgevoelig. Hybride aspecten zoals Iterative Grading dreigen bovendien een foutgevoelige administratie met veel overhead op te leveren.

### Opdrachtbeschrijving

In plaats van talloze losse Word- en Excel-bestanden bouw je een systeem dat de administratieve delen van het cursusontwikkelproces ondersteunt: het bewaart de data en genereert daaruit de benodigde documenten. Het systeem ondersteunt of bevat de volgende features:

- collaboratief werken zonder versiebeheerproblemen;
- scheiding van inhoud en vorm, waarbij formaten worden gegenereerd en eenvoudig aanpasbaar zijn;
- geautomatiseerde detectie van inconsistenties, bijvoorbeeld onvoldoende onderwijs per beoordelingsdimensie, of lessen die niet bijdragen aan de leerdoelen;
- data die direct bruikbaar is voor nieuwe aanpakken zoals Iterative Grading, waarbij transparantie en de groei van de student centraal staan;
- vereenvoudigd delen van onderwijsonderdelen tussen opleidingen en profielen;
- flexibiliteit in formaten, algemene ontwerpaanpak en uitbreidbaarheid, zodat het HAN-breed inzetbaar is;
- koppeling op termijn met andere systemen, zoals Brightspace (genereren en plaatsen van OWE-beschrijvingen) of Osiris (eindbeoordelingen volgens rubrics overnemen, inclusief onderbouwing).

### De opdracht (deliverables)

Maak een analyse en leg deze vast in een requirements-specificatie. Ontwerp het systeem volgens die specificatie en realiseer een prototype dat aantoont dat de belangrijkste requirements gerealiseerd (kunnen) worden. Toon van alle onderdelen aan dat ze van voldoende kwaliteit zijn. De beoordelingscriteria staan op onderwijsonline.

> Je mag op elk moment tijdens de uitvoering onderdelen laten beoordelen, mits je (1) duidelijk aangeeft op welke criteria je welk niveau denkt te halen (zie rubrics), en (2) onderbouwt waarom, met een link naar die onderbouwing. Zonder onderbouwing geen beoordeling.

## Optie 2: Eigen casus

Je mag ook een eigen casus ontwerpen. Deze moet voldoen aan de volgende eisen:

- Domeinmodel met minimaal 10 concepten.
- Use case diagram met minimaal 10 use cases, waarvan maximaal 65% CRUD.
- Een op zichzelf staand (onderdeel van een) systeem — dus geen features toevoegen aan of bugs oplossen van een bestaand systeem.
- Het systeem is distribueerbaar over meerdere machines/nodes (geen monoliet): presentatielaag, domeinlaag en datalaag draaien op verschillende servers. Een mobiele app of JavaScript front-end via RESTful services op een backend met een aparte database voldoet al.
- De technologiekeuze is nog niet volledig bepaald, met voldoende keuzevrijheid om deze gemotiveerd te onderbouwen.
- De casus kan tussentijds aangevuld worden met functionele en niet-functionele eisen vanuit de opdrachtgever (docent).

### Tips voor een eigen casus

- Beschrijf de meerwaarde voor jezelf of je werkgever: waarom moet dit gebouwd worden en welk probleem lost het op?
- Beschrijf features, user stories of use cases. Focus op features met logica, rekenwerk of complexiteit (veel samenwerking tussen objecten), niet op pure CRUD of UI. Een app die alleen leest en schrijft naar een database legt de focus te veel op UI en opslag — beide vallen buiten de OOSE-leerstof.
- Een eenvoudige database (~10 tabellen) en een sobere UI (witte schermen, grijze knoppen) houden de focus op functionaliteit.
- Neem een voorschot op prioriteiten: een goede casus is te groot voor de beschikbare tijd, zodat je keuzes maakt en in delen oplevert.
- Noem ook niet-functionele eisen: externe systemen en APIs, schaalbaarheid, flexibiliteit (vervangbare libraries), en het gewenste platform of de gewenste taal.
- Neem een voorlopig lijstje concepten op als quickstart voor het domeinmodel, inclusief hun samenhang: meer samenhang betekent meer kans dat het samenwerkende klassen worden.
- Overleg met de docenten over de technologie. Java is de OOSE-huisstijl, maar C#, TypeScript of Python mag ook, mits je de OOSE-ontwerpprincipes en patterns kunt toepassen.

## Werkwijze

Maak een issue-board in GitHub (Issues + Milestones). De milestones en issues zijn te importeren uit `Milestones-Issues-OOSE-DT.csv` (in deze map). Koppel je teamleden aan de issues. Onderbouw de kwaliteit per criterium.

## Bijlagen

- `sad/casus-opdracht.md` — EVL-beschrijving en leeruitkomsten
- `sad/toetsing/beoordelingscriteria casus.xlsx` — beoordelingscriteria
- `sad/assets/OOSE DT Casus ICDE.docx` — volledige ICDE-casusbeschrijving
- `meta/Milestones-Issues-OOSE-DT.csv` — importeerbare milestones/issues

---

> De ICDE casus versie 0.1 (05-07-2017) is van Christian Köppe en Rody Middelkoop.