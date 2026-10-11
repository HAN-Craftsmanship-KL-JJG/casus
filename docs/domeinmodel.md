# Domeinmodel ICDE

Dit document toont het domeinmodel van ICDE en onderbouwt het.
Het bouwt voort op [systeemgrenzen.md](systeemgrenzen.md), [use-cases.md](use-cases.md) en
[use-case-beschrijvingen.md](use-case-beschrijvingen.md).
Bronnen: de ICDE-casus in [README.md](../README.md), de Modulebeschrijving van de toets Casus, de
lesplanning en de rubric van OOSE-DT als voorbeeld van echte OWE-gegevens.

## Domeinmodel

![Domeinmodel van ICDE](diagrams/domeinmodel.svg)

De bron is [diagrams/domeinmodel.puml](diagrams/domeinmodel.puml).

## Aanpak

We volgen de regels voor een domeinmodel uit de cursus.
We vonden de concepten met Noun Phrase Identification (NPI) volgens het stappenplan van de
cursus.

## Kandidaat-concepten

We onderstreepten de zelfstandige naamwoorden in de casus, de Modulebeschrijving en de
use case beschrijvingen.
Daarna schiftten we ze: dubbele namen, synoniemen, rollen en dingen buiten het systeem vielen af.

| Zelfstandig naamwoord | Besluit | Reden |
| --- | --- | --- |
| opleiding | concept | UC08 kiest een opleiding. |
| profiel, opleidingsprofiel | geen concept | De HAN kent geen profielen, zie keuze 4. |
| OWE, onderwijseenheid, module | concept OWE | Drie namen voor hetzelfde. |
| eenheid van leeruitkomsten | concept EVL | ICDE genereert de EVL-beschrijving. |
| leeruitkomst, leerdoel | concept Leeruitkomst | De casus gebruikt beide woorden. |
| beoordelingsdimensie | concept | Groep criteria in de rubric. |
| beoordelingscriterium | concept | De kern van de consistentiecontrole. |
| niveau | concept | Een criterium heeft niveaus met elk een beschrijving. |
| les, lesplanning | concept Les | De lesplanning is de verzameling lessen. |
| toets, opdracht, toetsmoment | concept Toetsmoment | Toets en opdracht zijn soorten. |
| onderdeel, onderwijsonderdeel | concept OWE-onderdeel | Wat een OWE deelt, zie keuze 3. |
| documentsjabloon, documentformaat, sjabloon | concept Documentsjabloon | Vorm los van inhoud. |
| rubric | geen concept | Een dimensie met criteria en niveaus. |
| toetsplanning | geen concept | De verzameling toetsmomenten. |
| onderwijsweek | attribuut | Een weeknummer zonder eigen eigenschappen. |
| ontwikkelaar, coördinator, beheerder | geen concept | Rollen van actoren, zie keuze 2. |
| OWE-beschrijving, beoordelingsformulier | geen concept | Uitvoer van UC06, zie keuze 2. |
| PDF, Word | geen concept | Bestandstype dat de gebruiker kiest in UC06. |
| student, beoordeling | geen concept | ICDE legt geen beoordelingen vast, zie keuze 2. |
| inconsistentie, dekkingsoverzicht | geen concept | Uitvoer van UC05 en UC08. |
| versie, versiebeheer | geen concept | Een niet-functionele eis voor samenwerken. |
| Brightspace, Osiris | geen concept | Externe systemen zonder koppeling in het prototype. |
| didactiek | geen concept | Een werkwijze, geen ding met gegevens. |

## Concepten

| Concept | Betekenis |
| --- | --- |
| Opleiding | Een HBO-opleiding, zoals HBO-ICT. |
| OWE | Een onderwijseenheid, zoals OOSE-DT. |
| EVL | Een eenheid van leeruitkomsten van een OWE. |
| OWE-onderdeel | Een deel van een OWE dat te delen is. |
| Leeruitkomst | Wat een student na de OWE kan. |
| Beoordelingsdimensie | Een groep criteria, de rubric. |
| Beoordelingscriterium | Een eis in de rubric. |
| Niveau | Een score op een criterium. |
| Les | Een les in de lesplanning. |
| Toetsmoment | Een toets of opdracht. |
| Documentsjabloon | De vorm van een soort document. |

OWE-onderdeel is abstract: elk onderdeel is een leeruitkomst, dimensie, les of toetsmoment.

Toelichting bij enkele attributen:

- aantalWeken van OWE is de looptijd in onderwijsweken, zie BR8.
- weging en minimumscore komen uit de rubric.
  In de rubric van OOSE-DT heeft criterium B_Casus1-2 weging 10 en minimum 4.
- soort van Toetsmoment is toets of opdracht.
- soortDocument is OWE-beschrijving, EVL-beschrijving, toetsplanning of beoordelingsformulier.
- gedeeld zegt of andere OWE's het onderdeel kunnen hergebruiken (UC09).
- onderdelen, volgorde en opmaak van Documentsjabloon bepalen welke gegevens het document toont,
  in welke volgorde en hoe.
  Het bestandstype (PDF of Word) is geen attribuut, want de gebruiker kiest het per document in
  UC06.

## Associaties

Een multipliciteit staat bij het concept waarvan je het aantal telt.
We stelden per associatie de vraag uit het werkboek: met hoeveel B's heeft een A te maken,
gedurende het hele bestaan van A?

| Associatie | Multipliciteit | Onderbouwing |
| --- | --- | --- |
| Opleiding biedt OWE aan | 1 : 0..* | Een OWE hoort bij één opleiding, de eigenaar. |
| OWE bestaat uit EVL | 1 : 1..* | De casus: een OWE bestaat uit een of meer EVL's. |
| EVL groepeert Leeruitkomst | 1 : 0..* | UC05 meldt een OWE zonder leeruitkomsten (2A). |
| OWE beoordeelt met Beoordelingsdimensie | 1 : 0..* | Een nieuwe OWE heeft nog geen rubric. |
| Beoordelingsdimensie bestaat uit Beoordelingscriterium | 1 : 1..* | BR10, groep criteria. |
| Beoordelingscriterium onderscheidt Niveau | 1 : 1..* | Zonder niveau valt er niets te scoren. |
| OWE plant Les | 1 : 0..* | Een nieuwe OWE heeft nog geen lessen. |
| OWE plant Toetsmoment | 1 : 0..* | Een nieuwe OWE heeft nog geen toetsen. |
| Beoordelingscriterium toetst Leeruitkomst | 0..* : 1..* | BR1 controleert de kant 0..*. |
| Les draagt bij aan Beoordelingscriterium | 0..* : 0..* | BR2 en BR3. |
| Toetsmoment beoordeelt Beoordelingscriterium | 0..* : 0..* | BR4. |
| OWE hergebruikt OWE-onderdeel | 0..* : 0..* | UC07, BR6, BR7, BR13. |

Voorbeeld van lezen: Beoordelingscriterium toetst Leeruitkomst, 0..* : 1..*.
Een criterium toetst minstens één leeruitkomst.
Een leeruitkomst wordt door nul of meer criteria getoetst.

Documentsjabloon heeft geen associatie.
Een sjabloon geldt voor alle OWE's.
UC06 combineert een sjabloon en een OWE pas bij het genereren.

## Beperkingen die het diagram niet toont

Een UML-multipliciteit kan niet alles zeggen.
Deze regels gelden ook.
De codes verwijzen naar de
[bedrijfsregels](use-case-beschrijvingen.md#bedrijfsregels).
Met "een onderdeel van de OWE" bedoelen we een eigen onderdeel, of een onderdeel dat de OWE
hergebruikt.

- Een criterium toetst alleen leeruitkomsten van de OWE van zijn dimensie.
- Een les en een toetsmoment koppelen alleen criteria van hun OWE (BR11, BR14).
- onderwijsweek, startweek en deadlineweek liggen binnen aantalWeken van de OWE (BR11, BR14).
- Een OWE hergebruikt alleen onderdelen van een andere OWE met gedeeld = ja.

## Keuzes

1. Minimum 0 bij de consistentieregels.
   BR1 tot en met BR4 zeggen "minstens één", maar het model zegt 0..*.
   ICDE moet een OWE met een inconsistentie kunnen bewaren, anders kan UC05 die niet melden.
   Een ontwikkelaar legt eerst een les vast en koppelt later de criteria.
   UC04 waarschuwt dan, maar slaat de les wel op (alternate flow 6A).
2. Een klein model.
   De casus eist minimaal 10 concepten, dit model heeft er 11.
   Deze kandidaten vielen af:
   - Student en beoordeling horen bij Iterative Grading.
     ICDE legt geen beoordelingen vast, en de student is geen gebruiker van ICDE.
   - Onderwijsontwikkelaar, coördinator en beheerder zijn actoren in het use case diagram.
     Wie iets doet is toegangsbeheer, geen domeinkennis.
   - Een document is de uitvoer van UC06 uit een OWE en een sjabloon.
     Of ICDE documenten bewaart, is een ontwerpkeuze voor later.
3. Generalisatie OWE-onderdeel.
   UC09 deelt "een onderdeel, zoals een leeruitkomst of een rubric".
   Leeruitkomst, Beoordelingsdimensie, Les en Toetsmoment zijn allemaal te delen.
   De generalisatie laat zien dat delen (UC09) en hergebruiken (UC07) voor alle vier hetzelfde
   werken.
   Alternatief was een aparte associatie hergebruikt per soort onderdeel: vier lijnen die
   hetzelfde zeggen.
   Een gedeelde dimensie neemt haar criteria en niveaus mee.
   Een kopie (UC07, alternate flow 3A) is een nieuw onderdeel van de eigen OWE, geen hergebruik.
4. Geen concept Profiel.
   De casus noemt delen "tussen opleidingen en profielen".
   De HAN kent geen profielen als specialisatie binnen een opleiding, Opleiding dekt dit.
   ICDE deelt alleen binnen HBO-ICT, dus een onderdeel is gedeeld of niet.
   Het attribuut gedeeld legt dat vast, en een gedeeld onderdeel is zichtbaar voor elke andere OWE.
5. Geen compositie.
   Bijna elk concept bestaat niet zonder zijn OWE, dus compositie zou overal staan.
   Dat voegt geen informatie toe, en de cursus vraagt geen compositie in een domeinmodel.
6. Les en Toetsmoment hangen aan de OWE, niet aan een EVL.
   [systeemgrenzen.md](systeemgrenzen.md#begrippen) zegt dat een EVL leeruitkomsten groepeert en
   de toetsen die ze beoordelen.
   In de lesplanning van OOSE-DT staat ook per les een EVL.
   Die EVL volgt uit de criteria: criterium, leeruitkomst, EVL.
   Een directe associatie zou dubbel zijn en kan tegenspreken.
   Dit is de stap "controleer op redundantie" uit het stappenplan.

## Validatie

De controle van dit model tegen de use cases staat in
[domeinmodel-validatie.md](domeinmodel-validatie.md).

## Open punten

- Een OWE verandert per studiejaar.
  Moet ICDE oude jaren bewaren, dan wordt een uitvoering per studiejaar een eigen concept.
