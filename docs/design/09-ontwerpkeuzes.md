# Ontwerpkeuzes

Dit hoofdstuk bundelt de ontwerpkeuzes uit de hoofdstukken
[Domeinmodel](05-domeinmodel.md#domeinmodel), [Architectuur](06-architectuur.md#architectuur),
[Klassendiagram](07-klassendiagram.md#klassendiagram) en
[Sequence diagrams](08-sequencediagrammen.md#sequence-diagrams).
Elke keuze noemt het probleem, de alternatieven met hun nadeel, en de keuze.
De code van een keuze toont het hoofdstuk waar ze bij hoort: D voor het domeinmodel, A voor de
architectuur, K voor het klassendiagram en S voor de sequence diagrams.

## Domeinmodel

### D1 Minimum 0 bij de consistentieregels

Probleem: BR1 tot en met BR4 zeggen "minstens één".
Welke multipliciteit krijgen die associaties?

Alternatief: 1..*, zoals de regels zeggen.
Dan kan ICDE een OWE met een inconsistentie niet bewaren, en kan UC05 die niet melden.

Keuze: 0..*.
Een ontwikkelaar legt eerst een les vast en koppelt later de criteria.
UC04 waarschuwt dan, maar slaat de les wel op (flow 6A).

### D2 Generalisatie OWE-onderdeel

Probleem: UC09 deelt "een onderdeel, zoals een leeruitkomst of een rubric".
Leeruitkomst, Beoordelingsdimensie, Les en Toetsmoment zijn allemaal te delen.
Hoe toont het model dat?

Alternatief: een aparte associatie hergebruikt per soort onderdeel.
Dat zijn vier lijnen die hetzelfde zeggen.

Keuze: een abstract concept OWE-onderdeel met vier specialisaties.
De generalisatie laat zien dat delen (UC09) en hergebruiken (UC07) voor alle vier hetzelfde
werken.
Een gedeelde dimensie neemt haar criteria en niveaus mee.
Een kopie (UC07, flow 3A) is een nieuw onderdeel van de eigen OWE, geen hergebruik.

### D3 Geen concept Profiel

Probleem: de casus noemt delen "tussen opleidingen en profielen".

Alternatief: een concept Profiel, als specialisatie binnen een opleiding.
De HAN kent zulke profielen niet, en Opleiding dekt dit al.

Keuze: geen concept Profiel.
ICDE deelt alleen binnen HBO-ICT, dus een onderdeel is gedeeld of niet.
Het attribuut gedeeld legt dat vast, en een gedeeld onderdeel is zichtbaar voor elke andere OWE.

### D4 Les en Toetsmoment hangen aan de OWE, niet aan een EVL

Probleem: [Begrippen](02-systeemgrenzen.md#begrippen) zegt dat een EVL leeruitkomsten groepeert
en de toetsen die ze beoordelen.
In de lesplanning van OOSE-DT staat ook per les een EVL.

Alternatief: een directe associatie van Les en Toetsmoment naar EVL.
Die EVL volgt al uit de criteria: criterium, leeruitkomst, EVL.
Een directe associatie is dus dubbel en kan tegenspreken.

Keuze: Les en Toetsmoment hangen aan de OWE, zonder redundante associatie.

## Architectuur

### A1 Waar draait de domeinlogica?

Probleem: de consistentieregels, de validatieregels en het genereren van documenten moeten ergens
draaien.
Meerdere gebruikers werken tegelijk aan dezelfde OWE.

Alternatieven:

- In de gebruikersinterface, met een server die alleen gegevens opslaat.
  Dan draait elke regel op elke client.
  Een latere koppeling met Brightspace of Osiris moet de regels opnieuw bouwen.
- In de database, als stored procedures en constraints.
  Een regel als BR5 (toetsen per week) is dan moeilijk te schrijven en te testen.
  De regels hangen dan af van één databaseproduct, en OO-patterns zoals Strategy zijn niet
  bruikbaar.

Keuze: een eigen applicatie- en domeinlaag op de applicatieserver.
Elke regel staat op één plaats, voor alle gebruikers en latere koppelingen.
Gebruikersinterface en database zijn vervangbaar zonder het domein te wijzigen (Low Coupling).

### A2 Waar wordt het bestand gemaakt?

Probleem: UC06 maakt van de inhoud van een OWE een PDF- of Word-bestand.
Dat is zwaar werk, en het voert de opmaak uit die de functioneel beheerder aanpast (UC10).

Alternatieven:

- In het domein: Documentsjabloon maakt zelf het bestand.
  Dan hangt het domein af van de programma's die het bestand maken, en is het moeilijk te testen.
- Op de applicatieserver, buiten het domein.
  Een trage of vastgelopen omzetting hindert dan alle andere use cases.
  Een fout in een sjabloon draait dan op de server die bij alle gegevens kan.

Keuze: een eigen documentserver, achter de interface Documentomzetter.

- De applicatieserver bestuurt: hij kent de regels en de gegevens.
  De documentserver rekent: hij krijgt inhoud en opmaak, en geeft een bestand terug.
- De documentserver bewaart niets en kan niet bij de database.
  Een fout in een sjabloon raakt dus geen gegevens.
- De interface hoort bij het domein, de implementatie niet, net als bij de repositories
  (Dependency Inversion Principle).
- De documentserver is vervangbaar zonder het domein te wijzigen (Low Coupling).

Gevolg: het maken van een bestand is een aanroep over het netwerk.
Is de documentserver niet bereikbaar, dan is er geen document gemaakt, zoals de postconditie bij
falen van UC06 zegt.
Dat is een technische fout, geen flow van de use case.

## Klassendiagram

### K1 Een handler per use case

Probleem: ICDE heeft 11 use cases met samen meer dan 30 systeemoperaties.
Welke klasse ontvangt ze (GRASP Controller)?

Alternatieven:

- Eén facade controller ICDE.
  Alle operaties staan dan in één klasse, met lage cohesie (bloated controller).
- Een eigen handler voor elk van de 11 use cases.
  Vier handlers doen dan hetzelfde: een OWE ophalen, een onderdeel toevoegen en de OWE bewaren.

Keuze: een use case controller per use case, met het achtervoegsel Handler.
CRUD use cases van dezelfde actor over dezelfde gegevens delen een handler, tot ongeveer 10
systeemoperaties.

- UC01 en UC02 delen BeheerOWEHandler.
- UC04 en UC11 delen BeheerPlanningHandler.
- UC03 heeft met dimensies, criteria en niveaus genoeg operaties voor een eigen handler.

Use cases van verschillende actoren veranderen om verschillende redenen, en delen dus geen handler
(Single Responsibility Principle).

### K2 Repositories vinden de objecten

Probleem: een handler krijgt een code of naam en moet het object vinden.
De database draait op een eigen server.

Alternatieven:

- Een rootobject Catalogus, zoals Store bij Larman.
  Dat laadt alle opleidingen voor elke vraag.
- Statische zoekoperaties, zoals OWE.zoek(code).
  Dan kent elke domeinklasse de database, en is ze moeilijk te testen.

Keuze: een repository-interface per ingang: OWERepository, OpleidingRepository en
DocumentsjabloonRepository.
De interface hoort bij het domein, de implementatie bij de datalaag.
Zo hangt het domein niet af van de database (Dependency Inversion Principle).
Het data source pattern volgt in blok 2.

### K3 De delen van OWE geven alle gegevens

Probleem: de consistentieregels, de dekking en de documenten hebben alle leeruitkomsten,
criteria, lessen en toetsmomenten van een OWE nodig.
Daar horen ook de hergebruikte onderdelen bij.

Alternatief: elke regel zoekt zelf in EVL's, dimensies en hergebruik.
Dan kent elke regel de structuur van OWE.

Keuze: de klasse met de lijst geeft de gegevens (Information Expert).
OWE heeft geefLeeruitkomsten, Rubric geefCriteria, en Planning geefLessen en geefToetsmomenten.
Ze geven eigen en hergebruikte onderdelen samen, zodat de rest van het systeem het verschil niet
ziet (information hiding).

### K4 Een klasse per consistentieregel

Probleem: UC05 past BR1 tot en met BR5 toe.
De opdrachtgever kan regels toevoegen of wijzigen.

Alternatieven:

- Een operatie per regel in OWE.
  OWE krijgt dan meer taken, en elke nieuwe regel wijzigt OWE.
- Alle regels in ControleerConsistentieHandler.
  Dan staat domeinlogica in de handler, en kunnen UC04 en UC11 de regels niet hergebruiken.

Keuze: een interface Consistentieregel, met een klasse per regel.

- ControleerConsistentieHandler loopt de lijst regels af en weet niet welke regels er zijn.
- Een nieuwe regel is een nieuwe klasse, zonder wijziging van bestaande code (Open/Closed
  Principle).
- BeheerPlanningHandler hergebruikt LesDraagtBijRegel (BR2) en ToetsdrukRegel (BR5) in stap 6
  van UC04 en UC11.
- ToetsdrukRegel heeft het maximum als attribuut, dus een andere grens vraagt geen nieuwe klasse.

Deze opzet lijkt op het Strategy pattern.

### K5 Documentsjabloon maakt de inhoud van het document

Probleem: ICDE scheidt inhoud en vorm (UC06).
De functioneel beheerder wil sjablonen aanpassen zonder programmeur (UC10).
Het bestand zelf maakt de documentserver
([A2](09-ontwerpkeuzes.md#a2-waar-wordt-het-bestand-gemaakt)).

Alternatieven:

- OWE.genereer(sjabloon).
  OWE kent dan de opmaak, en dat is niet zijn taak (High Cohesion).
- Een generatorklasse per soort document.
  Een nieuwe soort document vraagt dan een programmeur.
- Documentsjabloon maakt ook het bestand.
  Dan roept een domeinklasse de documentserver aan, en is ze niet te testen zonder die server.

Keuze: Documentsjabloon maakt de inhoud, want het kent zijn onderdelen (Information Expert).
De interface Documentomzetter maakt van de inhoud een bestand.

- zoekOntbrekendeGegevens voert stap 4 uit.
  maakInhoud en Documentomzetter.zetOm voeren samen stap 5 uit.
- zoekOntbrekendeGegevens en maakInhoud krijgen de onderdelen die de ontwikkelaar in stap 3 koos.
  Een lege lijst betekent alle onderdelen van het sjabloon (flow 3A).
- maakInhoud geeft de inhoud als tekst terug, zonder opmaak.
- GenereerDocumentHandler geeft de inhoud, de opmaak van het sjabloon en het bestandstype aan
  zetOm.
- zetOm geeft de inhoud van een PDF- of Word-bestand terug, daarom byte[].
- Documentomzetter hoort bij het domein, de implementatie niet.
  Zo hangt het domein niet af van de documentserver (Dependency Inversion Principle), net als bij
  de repositories (K2).
- Documentsjabloon kent OWE alleen als parameter: een dependency, geen associatie.

Welke programma's de documentserver gebruikt, is een technologiekeuze voor blok 2.

### K6 Hergebruik: verwijzing of kopie

Probleem: UC07 neemt een gedeeld onderdeel op in een OWE, als verwijzing of als kopie.
Een verwijzing toont altijd de actuele versie (BR6).
Een kopie hangt niet meer af van het origineel (flow 3A), en kan alleen van een les of
toetsmoment.
Hoe komt een kopie in de OWE?

Alternatieven:

- De gebruikersinterface vult het toevoegscherm met het origineel.
  Flow 3A heeft die stap niet: het systeem neemt de kopie zelf op, zonder invoer van de
  ontwikkelaar.
- Een abstracte operatie kopieerNaar op OWEOnderdeel.
  Die geeft bij Leeruitkomst en Beoordelingsdimensie een fout, en dat schendt het Liskov
  Substitution Principle.
  Een gekopieerde leeruitkomst heeft een EVL en een nieuw nummer nodig (BR9).
  Een gekopieerd criterium verliest zijn leeruitkomsten, terwijl het er minstens één toetst.

Keuze: een interface Kopieerbaar met de operatie kopieerNaar(owe), die Les en Toetsmoment elk op
hun eigen manier uitwerken (Polymorphism).

- Stap 2: HergebruikOnderdeelHandler.geefGedeeldeOnderdelen haalt de gedeelde onderdelen op die
  de OWE nog niet bevat (OWE.bevat).
- Stap 4: de polymorfe operatie OWEOnderdeel.hergebruikIn(owe) voegt het originele object toe aan
  de lijst hergebruikt van zijn soort, dus de OWE ziet elke wijziging meteen.
  Een leeruitkomst gaat naar OWE, een dimensie naar Rubric, een les of toetsmoment naar Planning.
  Zo test de handler de soort niet (Polymorphism).
- Flow 3A: HergebruikOnderdeelHandler.opnemenKopie controleert dat het onderdeel Kopieerbaar is.
  Les.kopieerNaar roept planning.toevoegenLes aan, Toetsmoment.kopieerNaar
  planning.toevoegenToetsmoment.
  Zo controleert Planning BR11 en BR14 net als bij toevoegen, zonder de soort te testen
  ([S3](09-ontwerpkeuzes.md#s3-kopie-via-toevoegen)).
- De kopie heeft geen criteria, want die horen bij de andere OWE.
  UC05 meldt dat (BR2, BR4), en de ontwikkelaar koppelt daarna eigen criteria.
- Flow 4A: OWERepository.zoekGedeeldOnderdeel vindt een verwijderd origineel niet, en de handler
  meldt dat.

### K7 De eigenaar maakt een onderdeel

Probleem: welke klasse maakt een nieuw onderdeel (GRASP Creator)?

Alternatief: de handler maakt het onderdeel en geeft het aan de eigenaar.
Dan kent de handler de constructors van het domein, en controleert de eigenaar zijn regels pas
achteraf.

Keuze: de klasse die het onderdeel bevat.

| Klasse | Maakt |
| --- | --- |
| Opleiding | OWE, met de eerste EVL |
| OWE | EVL, Rubric en Planning |
| Rubric | Beoordelingsdimensie met het eerste criterium |
| Planning | Les en Toetsmoment |
| EVL | Leeruitkomst |
| Beoordelingsdimensie | Beoordelingscriterium |

Gevolgen:

- Opleiding.maakOWE krijgt de gegevens van de eerste EVL mee, want BR8 eist minstens één EVL.
  Zo bestaat er geen OWE zonder EVL.
- Rubric.toevoegenDimensie krijgt de gegevens van het eerste criterium mee, want een dimensie
  bestaat uit minstens één criterium (BR10).
- Verwijderen weigert het laatste exemplaar.
  OWE.verwijderEVL weigert de laatste EVL (BR8) en een EVL met leeruitkomsten (BR9).
  Beoordelingsdimensie.verwijderCriterium weigert het laatste criterium (BR10).
- De handler krijgt bij een les of toetsmoment de criteriumcodes, niet de criteria zelf.
  Rubric.zoekCriteria zoekt ze op in de eigen en hergebruikte dimensies van de OWE.
  Een code van een andere OWE vindt Rubric niet, en dat geeft een fout.
  Zo dwingt het ontwerp BR11 en BR14 af.
- De private operatie Planning.controleerWeek controleert onderwijsweek, startweek en
  deadlineweek (BR11, BR14).

### K8 Conflicterende veldwijzigingen weigeren

Probleem: twee ontwikkelaars wijzigen hetzelfde veld van dezelfde OWE.
Zonder controle kan de tweede wijziging de eerste overschrijven.
Wijzigingen aan verschillende velden moeten wel mogelijk blijven.

Alternatieven:

- Een vergrendeling per veld.
  Deze vraagt om vrijgave of een vervaltijd wanneer iemand de applicatie verlaat.
- Een versienummer op de hele OWE.
  Dit weigert ook wijzigingen aan verschillende velden.

PostgreSQL gebruikt Multi-Version Concurrency Control (MVCC).
Bij het standaardisolatieniveau READ COMMITTED ziet elke leesopdracht een momentopname van de
vastgelegde gegevens bij het begin van die opdracht.
MVCC herkent niet automatisch dat invoer uit de gebruikersinterface op oudere gegevens berust.
Daarom controleert de UPDATE-opdracht ook de oorspronkelijke veldwaarde.

Keuze: controleer bij elke veldwijziging de oorspronkelijke waarde in PostgreSQL.
De applicatie stuurt alleen het gewijzigde veld met de oorspronkelijke en nieuwe waarde mee.
De datalaag voert de controle en de wijziging uit in één UPDATE-opdracht.
De WHERE-voorwaarde vergelijkt de opgeslagen waarde met de oorspronkelijke waarde via
IS NOT DISTINCT FROM, zodat de vergelijking ook werkt bij NULL.

- Als één rij wordt bijgewerkt, is de wijziging opgeslagen.
- Als geen rij wordt bijgewerkt, kan het veld inmiddels gewijzigd of het record verwijderd zijn.
  De applicatie meldt dit en bewaart de eigen invoer voor vergelijking met de nieuwste gegevens.
- Wijzigingen aan andere velden blijven mogelijk, omdat alleen het gewijzigde veld wordt bewaard.
- De controle vergelijkt waarden en detecteert geen wijziging die daarna is teruggedraaid naar
  de oorspronkelijke waarde.

De repository-implementatie voert deze controle uit, zonder aparte vergrendelingsklassen.

### K9 OWE splitsen in Rubric en Planning

Probleem: OWE had 19 operaties.
EVL's, rubric, lesplanning, toetsplanning, hergebruik en dekking stonden in één klasse.
Elke wijziging in een van die taken raakt OWE (lage cohesie).

Alternatieven:

- Alles in OWE laten.
  Dat volgt Information Expert, maar OWE wordt een god class.
- Gegevens en gedrag scheiden: OWE houdt de lijsten, een serviceklasse maakt en controleert de
  onderdelen.
  Dan bewaakt OWE zijn eigen gegevens niet meer (anemic domain model), en kent de service de
  lijsten van OWE.

Keuze: OWE splitsen naar taak, met het gedrag bij de gegevens.

- Rubric beheert de beoordelingsdimensies en zoekt criteria op (BR10).
- Planning beheert de lessen en toetsmomenten en controleert de weken (BR11, BR14).
- OWE houdt de EVL's en leeruitkomsten (BR8, BR9) en de dekking.
- Rubric en Planning hebben elk een eigen verwijder, bevat en zoekOnderdeel, voor de eigen en
  hergebruikte onderdelen in hun lijsten (Information Expert).
- OWE.verwijder, bevat en zoekOnderdeel doorzoeken de leeruitkomsten van OWE, en vragen daarna
  Rubric en Planning.
  OWE kent de lijsten van Rubric en Planning dus niet.
  verwijder en bevat geven bij Rubric en Planning een boolean terug.
  Zo weet OWE of het onderdeel gevonden is, zonder de soort te testen.
- OWE maakt Rubric en Planning en heeft er precies één van (Creator).

Rubric en Planning zijn Pure Fabrication: het domeinmodel kent ze niet.
De namen komen wel uit de casus: de rubric van een OWE en de toetsplanning.
OWE heeft nu 10 operaties, Rubric 8 en Planning 10.

Gevolg: het domeinmodel heeft één associatie hergebruikt naar OWEOnderdeel.
Het ontwerp splitst die in een lijst per soort, bij het deel dat die soort beheert.
OWEOnderdeel.hergebruikIn kiest de lijst, zodat geen klasse de soort test (K6).

## Sequence diagrams

### S1 Controle bij de gegevens

Probleem: waar staan de controles voor exceptional flows, zoals 4A in UC04?

Alternatief: de handler controleert alle invoer.
Dan kent de handler de regels van het domein en wordt hij een bloated controller.

Keuze: het object met de gegevens controleert ze (Information Expert).
Planning controleert de week, Rubric de criteria, Toetsmoment de volgorde van start- en
deadlineweek.
De handler controleert alleen of er iets te doen is, zoals 2A in UC05 en UC08.

### S2 Overtreding kent haar onderdelen

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

### S3 Kopie via toevoegen

Probleem: een kopie (UC07, 3A) moet in de lijst van haar soort, en Planning controleert de week
(BR11, BR14).

Alternatief: Planning of de handler vraagt de kopie en test de soort.
Dan vervangt een switch op de soort het Polymorphism.

Keuze: `Kopieerbaar.kopieerNaar(planning)`.
Een Les roept `planning.toevoegenLes` aan, een Toetsmoment `planning.toevoegenToetsmoment`, zonder
criteria.
Zo controleert Planning de week zoals bij toevoegen.
