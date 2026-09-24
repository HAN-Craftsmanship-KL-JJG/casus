# AGENTS.md

Assignment repository for the HAN module OOSE Deeltijd (2026/2027).
Student teams fork it and build the case (ICDE or their own) across the SAD and DAD blocks.

## Working on an issue

Before you start an issue, read the matching course material in
https://github.com/HAN-Craftsmanship-KL-JJG/oose.
The rubric and the teachers grade against that material, not against general practice.

Aim for 10% above each minimum the assessment sets, and no more: a minimum of 10 means 11.
Extra items make models harder to read and do not raise the grade.
Cut items that no core use case needs, turn them into attributes, and explain the cuts in the
deliverable.

## Agent compatibility

These instructions must work in both Claude Code and OpenAI Codex.
Both read `AGENTS.md`, so keep all guidance there and add no `CLAUDE.md`.
A second file would duplicate or drift from this one.
Use only features both agents understand: plain Markdown, nested `AGENTS.md` files, and skills
in a format both can load.
When a feature exists in only one agent, keep the instruction readable without it.

## Writing

Write in plain English.
Readers are students who are not native English speakers.
Use short sentences, common words, and the active voice.
Start every sentence on a new line in all documentation, including `AGENTS.md`, README files,
and list items.
Diffs and review comments then point at one sentence.

Maximise information density while keeping text easy to read.
Drop filler (just, really, basically, actually, simply), pleasantries, and hedging.
Keep code symbols, function names, API names, and error strings verbatim.
Never abbreviate them, even when compressing other text.

Style rules for all prose, code, comments, output, and commit messages:

- No em dash or semicolon.
  Both chain clauses into long sentences.
  Split the sentence, or use a comma, colon, or parentheses.
  Semicolons that code syntax requires are exempt.
- No emojis.
- No ASCII decoration: banners, boxes, separator bars, ASCII art.
  Box-drawing in a directory tree is structure and is allowed.
- No bold, unless the information is critical.
- No numbered headings.

## Code quality

Every language needs a linter and an auto-formatter, Markdown included.
When a change adds a language, add its linter and formatter in the same change.
Use the strictest available ruleset and treat warnings as errors.
A build with any lint violation fails.
Fix the cause instead of disabling or downgrading a rule.
An inline suppression is a last resort: name the specific rule code and explain why.

Wire the formatter into a hook or task so it runs on every file.
A formatter that nobody runs gives no coverage.
Let it own layout decisions.

Limit hand-written lines to 100 characters.
Generated and vendored files are exempt.
In source, only unbreakable tokens (URLs, hashes) may exceed the limit.

## Git commits

Use Conventional Commits: `type(scope?): subject`.
Allowed types: `feat`, `fix`, `docs`, `refactor`, `test`, `perf`, `build`, `ci`, `chore`,
`style`, `revert`.
Mark a breaking change with `type(scope)!: subject` or a `BREAKING CHANGE:` footer that gives
the migration steps.
Link issues in the footer with `Fixes #123` or `Refs #123`.
Without an issue, the body states why the change exists.

Do not add AI attribution trailers.
Forbidden: `Co-authored-by:`, `Generated-by:`, `AI-Generated-by:`, `Assisted-by:`, `Model:`.
Allowed trailers: `Fixes #...`, `Refs #...`, `BREAKING CHANGE: ...`,
`Signed-off-by:` (human only).

## Dates and times

Write dates and times in ISO 8601: largest field first, full zero padding, literal `T` between
date and time.
Locale formats are ambiguous and sort wrong as text.
Store and log timestamps in UTC with an explicit `Z`, or an explicit numeric offset when local
time is unavoidable.
Convert to local time only for display, so timestamps from different machines and across
daylight saving changes stay comparable.

In filenames, replace each colon with a hyphen and change nothing else:
`2026-09-24T14-05-00Z`.
Windows forbids the colon in paths, and the name must still sort and parse back.

## Identifiers

- Language: BCP 47 tag, such as `nl-NL` or `en`.
  Lowercase language, uppercase region, hyphen between.
  Add the region only when the variant matters.
  Browsers and platforms negotiate on BCP 47, so names or `nl_NL` need translation first.
- Country: ISO 3166-1 alpha-2, two uppercase letters.
  No alpha-3, numeric codes, or domain suffixes.
- Place: UN/LOCODE, such as `NLNIJ`.
  Look the code up and use it verbatim.
  Local site abbreviations collide and nobody outside the team can resolve them.
- GUID: RFC 4122 canonical form, lowercase hex, no braces.
  Normalise input before storing, logging, or comparing, because braced or uppercase forms fail
  a plain string comparison.

## Versioning

Version every packaged application and module with Semantic Versioning 2.0.0.
Raise major for an incompatible change, minor for compatible features, patch for compatible
fixes, and reset the lower parts to zero.
Never reuse or edit a shipped version, because consumers pin against it.

## Editing agent instructions

Agent instruction files load on every task, so every line costs attention.
For each line, ask: would an agent do the wrong thing without it?
If not, delete it.

- State the project purpose in one or two lines.
  Spend the rest on gotchas that the code does not reveal.
- Do not repeat what `ls`, a manifest, or the code already shows, or general language
  knowledge.
- Write rules as intent with a reason, so an agent can apply them to cases the rule does not
  name.
- Match strictness to risk.
  Open task: state the goal.
  Preferred pattern: give a default and an escape hatch.
  Fragile or irreversible step (migration, release, deletion): give the exact command.
- Prefer code as the reference (test, schema, script, example file), because prose about code
  drifts.
  Say whether the agent must run it or read it.
- Move procedures needed only on some tasks (release, verification) into a skill or doc, and
  leave one line that names the file and says when to read it.

Each piece of guidance lives in exactly one file, because duplicates drift and contradict.
Before editing an `AGENTS.md`, read its parent and sibling `AGENTS.md` files and check for
overlap.
Put subtree-wide guidance in the nearest common ancestor and directory-specific guidance in that
directory.
When a new rule conflicts with an old one, remove one.
Do not add a third rule to settle the conflict.
Keep each `AGENTS.md` under 250 lines.
Past that, move directory-specific detail into a nested `AGENTS.md` and leave a short pointer.
