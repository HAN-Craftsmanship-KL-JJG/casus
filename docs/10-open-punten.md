# Open punten en overdracht

Dit ontwerp is de basis voor de gedistribueerde applicatie in blok 2.
Dit hoofdstuk noemt wat nog open is.

## Requirements

- BR3 vraagt minstens één les per criterium.
  De opdrachtgever kan een hogere drempel willen, bijvoorbeeld per studiepunt.
- UC07 neemt standaard een verwijzing op, en als alternatief een kopie.
- BR5 telt alleen de toetsmomenten van één OWE, ook als studenten meerdere OWE's tegelijk volgen.
- Een OWE verandert per studiejaar.
  Moet ICDE oude jaren bewaren, dan wordt een uitvoering per studiejaar een eigen concept in het
  domeinmodel.

## Ontwerp

- ICDE geeft domeinobjecten terug aan de gebruikersinterface, zoals List<OWEOnderdeel> in UC07.
  De gebruikersinterface draait op een eigen server, dus dat worden Data Transfer Objects.
- Een Vergrendeling blijft staan als een ontwikkelaar de browser sluit zonder het veld te
  verlaten.
  Hoe lang een vergrendeling geldt, stemmen we af met de opdrachtgever.

## Overdracht naar blok 2

Deze punten werken we uit in blok 2, elk in een eigen issue:

| Issue | Wat het ontwerp vastlegt | Wat nog open is |
| --- | --- | --- |
| #9 | Consistentieregel als interface, Kopieerbaar | Design patterns uitwerken |
| #10 | Systeemoperaties op de handlers | Remote facade, DTO's, inloggen en rolcontrole (C1) |
| #11 | Grens tussen gebruikersinterface en applicatie | REST-resources |
| #12 | Repository-interfaces, Vergrendeling | Data source pattern, duur van een vergrendeling |
| #13 | Schermen buiten het ontwerp | Presentatiepattern |
| #14 | Lagen en componenten | Talen, frameworks, template-engine voor Documentsjabloon |
| #15 | Drie servers | Deployment |
