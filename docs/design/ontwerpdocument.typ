// Typst layout for the design document PDF.
// The workflow passes this file to pandoc with --include-in-header.
// Pandoc inserts it after its own conf function, so the conf below replaces pandoc's title block
// and page layout.
// Only fonts that Typst embeds are used, because the pandoc/typst container has no other fonts.

#let accent = rgb("#1f4e79")
#let accent-light = rgb("#eaf0f6")
#let muted = luma(105)

#set text(font: "Libertinus Serif", size: 10.5pt)
#set par(justify: false, leading: 0.6em, spacing: 0.9em)
#set list(indent: 0.4em, body-indent: 0.5em)
#show link: set text(fill: accent)
#show raw: set text(font: "DejaVu Sans Mono", size: 0.85em)
#show raw.where(block: false): it => box(
  fill: luma(240),
  inset: (x: 2pt),
  outset: (y: 2.5pt),
  radius: 2pt,
  it,
)

#show heading: set text(fill: accent)
#show heading: set block(above: 1.4em, below: 0.7em)
#show heading.where(level: 1): it => {
  pagebreak(weak: true)
  block(width: 100%, below: 1.2em, stroke: (bottom: 1.5pt + accent), inset: (bottom: 0.4em))[
    #text(size: 22pt, weight: "bold", it.body)
  ]
}
#show heading.where(level: 2): set text(size: 14pt)
#show heading.where(level: 3): set text(size: 12pt)
#show heading.where(level: 4): set text(size: 10.5pt, fill: black)

#set table(
  inset: (x: 6pt, y: 5pt),
  stroke: none,
  fill: (_, y) => if y == 0 { accent } else if calc.even(y) { accent-light },
)
#show table: set text(size: 9.5pt)
#show table.cell: set align(left)
#show table.cell.where(y: 0): set text(fill: white, weight: "bold")
#show figure.where(kind: table): set block(breakable: true)
#show figure: set block(above: 1em, below: 1em)

// Shrink a diagram that is taller than the page, so it does not leave an empty page before it.
#show image: it => layout(region => {
  let natural = measure(it)
  let scale = calc.min(1, region.width / natural.width)
  let max-height = 22cm
  if natural.height * scale > max-height { box(height: max-height, it) } else { it }
})

#show outline.entry.where(level: 1): set block(above: 1em)
#show outline.entry.where(level: 1): set text(weight: "bold", fill: accent)

#let title-page(title, subtitle, date) = page(margin: 0pt, header: none, footer: none)[
  #block(width: 100%, height: 45%, fill: accent, inset: (x: 2.5cm, bottom: 2cm))[
    #align(bottom)[
      #text(size: 34pt, weight: "bold", fill: white, hyphenate: false, title)
      #v(0.3em)
      #text(size: 16pt, fill: white, subtitle)
    ]
  ]
  #block(inset: (x: 2.5cm, top: 1.2cm))[
    #text(size: 11pt, fill: muted)[Requirements-specificatie en softwareontwerp]
    #v(0.4em)
    #text(size: 11pt, fill: muted)[Versie #date]
  ]
]

// The chapter heading on or before this page, or none on the first page of a chapter.
#let running-chapter() = {
  let page-number = here().page()
  let chapters = query(heading.where(level: 1))
  if chapters.any(h => h.location().page() == page-number) { return none }
  let before = chapters.filter(h => h.location().page() < page-number)
  if before.len() > 0 { before.last().body }
}

#let conf(..args) = {
  let named = args.named()
  let doc = args.pos().last()
  let title = named.at("title", default: none)
  set document(title: title)
  set text(lang: named.at("lang", default: "nl"), region: named.at("region", default: "NL"))
  title-page(title, named.at("subtitle", default: none), named.at("date", default: none))
  set page(
    paper: named.at("paper", default: "a4"),
    margin: named.at("margin", default: 2cm),
    header: context {
      let chapter = running-chapter()
      if chapter != none {
        set text(size: 9pt, fill: muted)
        grid(columns: (1fr, auto), chapter, title)
        v(-0.5em)
        line(length: 100%, stroke: 0.5pt + luma(200))
      }
    },
    footer: context align(center, text(size: 9pt, fill: muted, counter(page).display())),
  )
  counter(page).update(1)
  doc
}
