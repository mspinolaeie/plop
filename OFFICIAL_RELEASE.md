# Official Release Policy

This repository currently has two GUI lines:

- the legacy VCL application: `Gui Plop`
- the newer Qt Widgets application: `plop_gui_qt.exe`

## Official product

The official end-user product remains the legacy VCL application.

That means:

- public/end-user releases should continue to ship `Gui Plop`
- the official installer remains the VCL installer flow
- `.gr` file association in official releases should keep pointing to `gui_plop.exe`
- registry-based runtime configuration used by the VCL app remains part of the official product contract

## Qt build status

The Qt application is currently a local build and migration frontend.

It is suitable for:

- local development
- source-build validation
- smoke tests
- incremental GUI migration work

It is not yet the official replacement for the VCL product because feature parity is incomplete, especially in:

- editor tabs and workflows
- `NumEdit` semantics
- automatic cell design
- rich domain editing flows
- overall GUI parity with `TCellEditForm` and `TRunForm`

## Official packaging path

The current official packaging path is the legacy Inno Setup script:

- [plop_src/plop_xe10/gui_plop/inno_setup.iss](plop_src/plop_xe10/gui_plop/inno_setup.iss)

That script packages:

- `gui_plop.exe`
- `z88i1plop.exe`
- `z88i2plop.exe`
- `z88.dyn`
- `z88i4.txt`
- `GuiPlop Users Manual.pdf`
- `autocell/`

## Practical guidance

Until an explicit parity milestone is reached, use this rule:

- distribute VCL to users
- use Qt internally

If the Qt build is ever promoted to official status, that should be treated as a deliberate product transition with:

- a parity review
- a new installer flow
- updated file association behavior
- updated support/documentation policy
