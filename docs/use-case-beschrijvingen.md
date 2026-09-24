# Use case beschrijvingen ICDE

Dit document werkt de belangrijkste use cases van ICDE uit.
Het bouwt voort op het use case diagram in [use-cases.md](use-cases.md).

## Aanpak

We volgen het fully dressed template van de cursus (Use Case template, Thema 1 Use Case
Modeling).
De namen van de secties laten we in het Engels, zoals in het template.
Het main success scenario staat in twee kolommen: actor action en system responsibility.
De stappen zijn doorlopend genummerd over beide kolommen.

Een extensie heet naar de stap waar ze begint, bijvoorbeeld 3A.
De conditie (guard) staat tussen rechte haken.
De substappen heten 3A1, 3A2 enzovoort.
Een extensie eindigt met "Ga naar stap N" of "Einde use case".
Zonder zo'n laatste stap gaat het main success scenario verder na de stap van de extensie.

Pre- en postcondities zijn uitspraken die waar of onwaar zijn.
Ze gebruiken de begrippen uit de casus: OWE, leeruitkomst, beoordelingscriterium, les.
De use cases zijn een black box: ze beschrijven wat het systeem doet, niet hoe, en niet hoe het
scherm eruitziet.

## Keuze van de use cases

De cursus vraagt om de nadruk te leggen op use cases met logica en rekenwerk, en niet op CRUD.
Daarom werken we deze use cases fully dressed uit:

- UC05 Controleren consistentie OWE, prioriteit hoog.
  Dit is de kern van de casus: handmatige consistentiecontroles bleken foutgevoelig.
- UC06 Genereren document, prioriteit hoog.
  Dit is de scheiding van inhoud en vorm.
- UC08 Opvragen dekkingsoverzicht, prioriteit hoog.
  De casus noemt het ontbreken van dit overzicht als probleem.
- UC07 Hergebruiken gedeeld onderdeel, prioriteit middel.
  Dit bepaalt hoe een gedeeld onderdeel zich gedraagt als het origineel verandert.

Van de CRUD use cases werken we UC04 Beheren lesplanning en UC11 Beheren toetsplanning uit.
Een les en een toetsmoment koppelen de planning aan de beoordelingscriteria.
Bij een toetsmoment telt het systeem ook de toetsen per week.
Dat is meer dan invoeren.
Voor de andere CRUD use cases geven we het item en de validatieregels.
UC09 Delen OWE-onderdeel staat in brief format.

## Bedrijfsregels

De use cases verwijzen naar deze regels met hun code, bijvoorbeeld [BR1].
"Van de OWE" en "van dezelfde OWE" omvatten ook de onderdelen die de OWE hergebruikt (UC07).

Consistentieregels, voor UC05 en UC08:

- BR1: Elke leeruitkomst van een OWE wordt getoetst door minstens één beoordelingscriterium.
- BR2: Elke les draagt bij aan minstens één beoordelingscriterium.
- BR3: Elk beoordelingscriterium heeft minstens één les die eraan bijdraagt.
- BR4: Elk beoordelingscriterium wordt beoordeeld in minstens één toetsmoment.
- BR5: In geen enkele onderwijsweek lopen meer dan 3 toetsmomenten van de OWE tegelijk.
  Een toetsmoment loopt van zijn startweek tot en met zijn deadlineweek.

BR3 en BR4 samen geven de controle die de opdrachtgever vraagt: lessen voor elke toets, en
andersom.
Een les draagt bij aan een criterium (BR2), en dat criterium wordt getoetst (BR4).
Een toets beoordeelt criteria (BR4), en voor die criteria zijn lessen (BR3).

Regels voor gedeelde onderdelen, voor UC07 en UC09:

- BR6: Een OWE die een gedeeld onderdeel hergebruikt, toont altijd de actuele versie ervan.
- BR7: Alleen de OWE van herkomst kan een gedeeld onderdeel wijzigen.

Validatieregels voor CRUD, voor UC01 tot en met UC04, UC10 en UC11:

- BR8: De code van een OWE is uniek.
  Een OWE heeft een naam, een opleiding, een aantal studiepunten groter dan 0 en een looptijd van
  minstens één onderwijsweek.
  Een OWE heeft minstens één EVL, elk met een naam en studiepunten.
- BR9: Een leeruitkomst heeft een omschrijving.
  Het nummer van een leeruitkomst is uniek binnen de OWE.
- BR10: Een beoordelingscriterium hoort bij precies één beoordelingsdimensie van dezelfde OWE.
  Het heeft minstens twee niveaus.
- BR11: Een les heeft een naam en een onderwijsweek binnen de looptijd van de OWE.
  Een les draagt alleen bij aan beoordelingscriteria van dezelfde OWE.
- BR12: De naam van een documentformaat is uniek.
  Een documentformaat is voor één soort document en gebruikt alleen gegevens die een OWE heeft.
- BR13: Een onderdeel dat een andere OWE hergebruikt, kan niet worden verwijderd.
- BR14: Een toetsmoment heeft een naam, een startweek en een deadlineweek binnen de looptijd van
  de OWE.
  De startweek ligt niet na de deadlineweek.
  Een toetsmoment beoordeelt alleen beoordelingscriteria van dezelfde OWE.

## UC05 Controleren consistentie OWE

- Primary actor: Onderwijsontwikkelaar.
- Stakeholders and interests:
  - Onderwijsontwikkelaar: wil fouten in het ontwerp vroeg zien, zonder handmatig te tellen.
  - Opleidingscoördinator: wil dat elke OWE aansluit op de eigen leeruitkomsten.
  - Examencommissie: wil aantoonbaar zien dat de toetsing aansluit op de leeruitkomsten.
  - Student: wil op elk beoordelingscriterium worden voorbereid in de lessen.
- Cross references: BR1 tot en met BR5, UC02, UC03, UC04, UC11.
- Brief description: De onderwijsontwikkelaar laat het systeem een OWE controleren.
  Het systeem past de consistentieregels toe en toont elke overtreding.
- Preconditions: De OWE bestaat.
- Postconditions on success: Het systeem heeft BR1 tot en met BR5 toegepast op de OWE.
  De ontwikkelaar heeft elke overtreding gezien.
  De gegevens van de OWE zijn niet gewijzigd.
- Postconditions on failure: De gegevens van de OWE zijn niet gewijzigd.

Main success scenario:

| Actor action | System responsibility |
| --- | --- |
| 1. De ontwikkelaar kiest een OWE en vraagt een consistentiecontrole aan. | |
| | 2. Het systeem past BR1 tot en met BR5 toe op de gegevens van de OWE. |
| | 3. Het systeem toont per regel de onderdelen die de regel overtreden. |
| 4. De ontwikkelaar kiest een overtreding. | |
| | 5. Het systeem toont het onderdeel met de gegevens die de overtreding veroorzaken. |

Stappen 4 en 5 worden herhaald tot de ontwikkelaar klaar is.

Alternate flows:

- 3A. [De OWE overtreedt geen enkele regel]
  - 3A1. Het systeem meldt dat de OWE consistent is.
  - 3A2. Einde use case.

Exceptional flows:

- 2A. [De OWE heeft geen leeruitkomsten]
  - 2A1. Het systeem meldt dat er zonder leeruitkomsten niets te controleren is.
  - 2A2. Einde use case.

## UC06 Genereren document

- Primary actor: Onderwijsontwikkelaar.
- Stakeholders and interests:
  - Onderwijsontwikkelaar: wil een document zonder de gegevens opnieuw te typen.
  - Functioneel beheerder: wil het formaat kunnen wijzigen zonder de inhoud aan te raken.
  - Opleidingscoördinator: wil dat alle OWE-beschrijvingen van de opleiding hetzelfde formaat
    hebben.
  - Student: wil een OWE-beschrijving die klopt met het gegeven onderwijs.
- Cross references: BR12, UC10 levert de formaten.
- Brief description: De onderwijsontwikkelaar kiest een OWE en een documentformaat.
  Het systeem maakt uit de gegevens van de OWE een document in dat formaat.
  Soorten documenten zijn de OWE-beschrijving, de EVL-beschrijving, de toetsplanning en het
  beoordelingsformulier.
- Preconditions: De OWE bestaat.
  Er is minstens één documentformaat.
- Postconditions on success: Er is een document dat de gegevens van de OWE toont in het gekozen
  formaat.
  De gegevens van de OWE zijn niet gewijzigd.
- Postconditions on failure: Er is geen document gemaakt.
  De gegevens van de OWE zijn niet gewijzigd.

Main success scenario:

| Actor action | System responsibility |
| --- | --- |
| 1. De ontwikkelaar kiest een OWE en geeft aan een document te willen maken. | |
| | 2. Het systeem toont de documentformaten, per soort document. |
| 3. De ontwikkelaar kiest een documentformaat. | |
| | 4. Het systeem controleert of de OWE alle gegevens heeft die het formaat gebruikt. |
| | 5. Het systeem maakt het document uit de gegevens van de OWE en het formaat. |
| | 6. Het systeem levert het document aan de ontwikkelaar. |

Alternate flows:

- 2A. [Er is precies één documentformaat]
  - 2A1. Het systeem kiest dat formaat.
  - 2A2. Ga naar stap 4.

Exceptional flows:

- 4A. [De OWE mist gegevens die het formaat gebruikt]
  - 4A1. Het systeem toont welke gegevens ontbreken.
  - 4A2. Einde use case.

## UC08 Opvragen dekkingsoverzicht

- Primary actor: Opleidingscoördinator.
- Stakeholders and interests:
  - Opleidingscoördinator: wil zien of de opleiding elke leeruitkomst voldoende afdekt.
  - Onderwijsontwikkelaar: wil weten welke leeruitkomsten meer onderwijs nodig hebben.
  - Examencommissie: wil aantoonbaar zien dat elke leeruitkomst wordt getoetst.
- Cross references: BR1, BR3, BR4, UC05.
- Brief description: De opleidingscoördinator kiest een opleiding.
  Het systeem toont per OWE en per leeruitkomst welke beoordelingscriteria de leeruitkomst toetsen,
  in welke toetsmomenten die criteria worden beoordeeld, en welke lessen eraan bijdragen.
- Preconditions: De opleiding bestaat.
- Postconditions on success: De coördinator heeft per leeruitkomst van de opleiding het aantal
  beoordelingscriteria, toetsmomenten en lessen gezien.
  Elke leeruitkomst zonder criteria, zonder toetsmoment of zonder lessen is gemarkeerd.
  De gegevens zijn niet gewijzigd.
- Postconditions on failure: De gegevens zijn niet gewijzigd.

Main success scenario:

| Actor action | System responsibility |
| --- | --- |
| 1. De coördinator kiest een opleiding en vraagt het dekkingsoverzicht op. | |
| | 2. Het systeem verzamelt de OWE's van de opleiding met hun leeruitkomsten. |
| | 3. Het systeem bepaalt per leeruitkomst de criteria die haar toetsen. |
| | 4. Het systeem bepaalt per leeruitkomst de toetsmomenten en lessen van die criteria. |
| | 5. Het systeem toont per leeruitkomst het aantal criteria, toetsmomenten en lessen. |
| | 6. Het systeem markeert elke leeruitkomst waarvan een van die aantallen 0 is. |
| 7. De coördinator kiest een leeruitkomst. | |
| | 8. Het systeem toont de criteria, toetsmomenten en lessen van die leeruitkomst. |

Stappen 7 en 8 worden herhaald tot de coördinator klaar is.

Alternate flows:

- 1A. [De coördinator wil het overzicht van één OWE]
  - 1A1. De coördinator kiest een OWE en vraagt het dekkingsoverzicht op.
  - 1A2. Het systeem neemt alleen deze OWE mee.
  - 1A3. Ga naar stap 3.

Exceptional flows:

- 2A. [Geen OWE van de opleiding heeft leeruitkomsten]
  - 2A1. Het systeem meldt dat er geen leeruitkomsten zijn om te tonen.
  - 2A2. Einde use case.

## UC07 Hergebruiken gedeeld onderdeel

- Primary actor: Onderwijsontwikkelaar.
- Stakeholders and interests:
  - Onderwijsontwikkelaar: wil een bestaand onderdeel gebruiken in plaats van het opnieuw te
    schrijven.
  - Opleidingscoördinator die het onderdeel deelde: wil dat verbeteringen bij alle opleidingen
    aankomen.
  - Opleidingscoördinator van de ontvangende opleiding: wil een onderdeel kunnen aanpassen aan de
    eigen opleiding.
- Cross references: BR6, BR7, BR13, UC09 maakt een onderdeel gedeeld.
- Brief description: De onderwijsontwikkelaar kiest een gedeeld onderdeel en neemt het op in de
  eigen OWE.
  Het onderdeel blijft gelijk aan het origineel, tenzij de ontwikkelaar een kopie kiest.
- Preconditions: De OWE bestaat.
  Er is minstens één gedeeld onderdeel van een andere OWE.
- Postconditions on success: De OWE bevat het gekozen onderdeel, als verwijzing of als kopie.
- Postconditions on failure: De OWE is niet gewijzigd.

Main success scenario:

| Actor action | System responsibility |
| --- | --- |
| 1. De ontwikkelaar kiest een OWE en geeft aan een gedeeld onderdeel te willen opnemen. | |
| | 2. Het systeem toont de gedeelde onderdelen met soort en OWE van herkomst. |
| 3. De ontwikkelaar kiest een onderdeel. | |
| | 4. Het systeem toont de inhoud van het onderdeel. |
| 5. De ontwikkelaar bevestigt het opnemen van het onderdeel. | |
| | 6. Het systeem neemt een verwijzing naar het onderdeel op in de OWE [BR6]. |

Alternate flows:

- 5A. [De ontwikkelaar wil het onderdeel aanpassen aan de eigen OWE]
  - 5A1. De ontwikkelaar kiest voor een kopie.
  - 5A2. Het systeem neemt een kopie van het onderdeel op in de OWE.
    De kopie hangt niet meer af van het origineel.
  - 5A3. Einde use case.

Exceptional flows:

- 6A. [De OWE bevat het onderdeel al]
  - 6A1. Het systeem meldt dat de OWE het onderdeel al bevat.
  - 6A2. Ga naar stap 2.

## UC04 Beheren lesplanning

UC04 is een «CRUD» use case.
Ze staat voor Toevoegen les, Bekijken les, Wijzigen les en Verwijderen les.
Die volgen het CRUD-sjabloon van de cursus.
Toevoegen les werken we hier uit, omdat de koppeling met beoordelingscriteria afwijkt van het
sjabloon.

### Toevoegen les

- Primary actor: Onderwijsontwikkelaar.
- Stakeholders and interests:
  - Onderwijsontwikkelaar: wil per les vastleggen aan welke criteria die bijdraagt.
  - Docent: wil weten welke criteria in een les aan bod komen.
- Cross references: BR2, BR11, UC03 levert de beoordelingscriteria.
- Brief description: De onderwijsontwikkelaar voegt een les toe aan de lesplanning van een OWE, en
  geeft aan aan welke beoordelingscriteria die bijdraagt.
- Preconditions: De OWE bestaat.
- Postconditions on success: De OWE heeft een nieuwe les die voldoet aan BR11.
- Postconditions on failure: De lesplanning van de OWE is niet gewijzigd.

Main success scenario:

| Actor action | System responsibility |
| --- | --- |
| 1. De ontwikkelaar geeft aan een nieuwe les te willen toevoegen aan een OWE. | |
| | 2. Het systeem geeft gelegenheid tot invoeren en toont de criteria van de OWE. |
| 3. De ontwikkelaar vult naam, onderwijsweek en beschrijving van de les in. | |
| 4. De ontwikkelaar kiest de criteria waaraan de les bijdraagt. | |
| 5. De ontwikkelaar bevestigt de ingevoerde gegevens. | |
| | 6. Het systeem controleert of de gegevens valide zijn [BR11]. |
| | 7. [gegevens zijn valide] Het systeem slaat de les op. |

Alternate flows:

- 7B. [De les draagt aan geen enkel criterium bij]
  - 7B1. Het systeem slaat de les op.
  - 7B2. Het systeem meldt dat de les BR2 overtreedt.
  - 7B3. Einde use case.

Exceptional flows:

- 7A. [gegevens zijn niet valide]
  - 7A1. Het systeem meldt welke gegevens onjuist zijn.
  - 7A2. Ga naar stap 2.

## UC11 Beheren toetsplanning

UC11 is een «CRUD» use case.
Ze staat voor Toevoegen toetsmoment, Bekijken toetsmoment, Wijzigen toetsmoment en Verwijderen
toetsmoment.
Toevoegen toetsmoment werken we hier uit, omdat het systeem daarbij de toetsen per week telt.
Wijzigen toetsmoment doet dezelfde telling na stap 7 van het CRUD-sjabloon.

### Toevoegen toetsmoment

- Primary actor: Onderwijsontwikkelaar.
- Stakeholders and interests:
  - Onderwijsontwikkelaar: wil een toets plannen en zien of die botst met andere toetsen.
  - Student: wil niet meer dan 3 toetsen tegelijk in een week.
  - Docent: wil weten welke criteria in welke toets worden beoordeeld.
- Cross references: BR4, BR5, BR14, UC03 levert de beoordelingscriteria.
- Brief description: De onderwijsontwikkelaar voegt een toets of opdracht toe aan de
  toetsplanning van een OWE.
  De ontwikkelaar legt vast wanneer het toetsmoment loopt en welke criteria het beoordeelt.
- Preconditions: De OWE bestaat.
- Postconditions on success: De OWE heeft een nieuw toetsmoment dat voldoet aan BR14.
  Is BR5 overtreden, dan heeft de ontwikkelaar een waarschuwing gezien.
- Postconditions on failure: De toetsplanning van de OWE is niet gewijzigd.

Main success scenario:

| Actor action | System responsibility |
| --- | --- |
| 1. De ontwikkelaar geeft aan een nieuw toetsmoment te willen toevoegen aan een OWE. | |
| | 2. Het systeem geeft gelegenheid tot invoeren en toont de criteria van de OWE. |
| 3. De ontwikkelaar vult naam, soort, startweek en deadlineweek in. | |
| 4. De ontwikkelaar kiest de criteria die het toetsmoment beoordeelt. | |
| 5. De ontwikkelaar bevestigt de ingevoerde gegevens. | |
| | 6. Het systeem controleert of de gegevens valide zijn [BR14]. |
| | 7. [gegevens zijn valide] Het systeem slaat het toetsmoment op. |
| | 8. Het systeem telt per week van het toetsmoment de lopende toetsmomenten [BR5]. |

Alternate flows:

- 8A. [In een week lopen meer dan 3 toetsmomenten]
  - 8A1. Het systeem waarschuwt en toont de weken en de toetsmomenten die daarin lopen.

Exceptional flows:

- 7A. [gegevens zijn niet valide]
  - 7A1. Het systeem meldt welke gegevens onjuist zijn.
  - 7A2. Ga naar stap 2.

## Overige CRUD use cases

Deze use cases volgen het CRUD-sjabloon van de cursus zonder afwijkingen.
Stap "Systeem controleert of gegevens valide zijn" gebruikt de genoemde regels.

| Use case | Item | Validatieregels |
| --- | --- | --- |
| UC01 Beheren OWE | OWE met EVL's | BR8, BR13 bij verwijderen |
| UC02 Beheren leeruitkomsten | Leeruitkomst | BR9, BR13 bij verwijderen |
| UC03 Beheren beoordelingscriteria | Beoordelingscriterium | BR10, BR13 bij verwijderen |
| UC10 Beheren documentformaat | Documentformaat | BR12 |

Voor alle wijzig-use cases geldt deze niet-functionele eis.
Als twee ontwikkelaars tegelijk dezelfde OWE wijzigen, gaat geen van beide wijzigingen verloren
zonder dat de ontwikkelaar dat merkt.

## Use case in brief format

- UC09 Delen OWE-onderdeel: De opleidingscoördinator kiest een onderdeel van een OWE, zoals een
  leeruitkomst of een rubric.
  Het systeem maakt het onderdeel zichtbaar voor andere opleidingen en profielen.
  Daarna kan een ontwikkelaar het hergebruiken met UC07.

## Open punten

- Iterative Grading en de koppelingen met OnderwijsOnline en Alluris staan niet in het use case
  diagram, zie [use-cases.md](use-cases.md#buiten-het-diagram).
  Komen die use cases terug, dan komen er ook bedrijfsregels bij.
- BR3 zegt "minstens één les" per criterium.
  De opdrachtgever kan een hogere drempel willen, bijvoorbeeld een aantal lessen per studiepunt.
- UC07 kiest standaard een verwijzing en als alternatief een kopie.
  De opdrachtgever moet bevestigen dat dit de gewenste manier van delen is.
- BR5 telt de toetsmomenten van één OWE.
  Studenten volgen soms meerdere OWE's tegelijk.
  De opdrachtgever moet zeggen of de telling ook over OWE's heen moet gaan.
