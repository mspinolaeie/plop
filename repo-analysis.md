# Plop Repository Analysis

## Executive Summary

This repository is a legacy Windows desktop application for mirror support analysis. It is not organized like a modern actively maintained software project; it is closer to a source archive plus packaging assets.

The primary user-facing deliverable is the Windows installer for `Gui Plop`, not a reproducible source build. The repository contains:

- a core Plop computation codebase in `plop_src/plop_xe10`
- a bundled/adapted Z88 source tree in `plop_src/z88src/z88mix12`
- Windows GUI project files for Embarcadero C++Builder/VCL
- an installer script and end-user documentation

## Top-Level Structure

- `README.md`
  - points users to the release installer `gui_plop_setup_3_0_7.exe`
  - links the user manual PDF
- `GuiPlop Users Manual.pdf`
  - bundled manual for the desktop application
- `plop_src.tar`
  - archive artifact kept in the repo
- `plop_src/plop_xe10`
  - main Plop codebase
- `plop_src/z88src/z88mix12`
  - Z88-related source tree with a separate build path

## Main Code Areas

### 1. Core CLI / computation layer

The main CLI entrypoint is `plop_src/plop_xe10/plop_main.cpp`.

Responsibilities:

- parses command-line options
- supports interactive CLI mode when no arguments are provided
- reads `.gr` control files
- initializes globals, graphics state, and solver state
- runs the Plop evaluation flow

### 2. Parser and domain model

The parser is centered in `plop_src/plop_xe10/plop_parser.cpp`.

Characteristics:

- table-driven parameter parsing via `parm_list`
- custom tokenization with `getwords`
- variable support and variable binding
- writes into large global state tables

The input model is based on Plop control files and mutable global arrays rather than typed objects.

### 3. Run/evaluation flow

The orchestration logic is in `plop_src/plop_xe10/plop_run.cpp`.

The main routine is `run_plate()`, which:

- evaluates variables
- generates mesh or basis mesh
- invokes the FE solve path
- interpolates results
- computes RMS and peak-to-valley metrics
- optionally applies refocus logic
- optionally exports Z88 input files

This is the main “application logic” layer for numerical execution.

### 4. FE solve path

The standard solve path does not go through Z88.

`exec_plate()` in `plop_src/plop_xe10/grid_gen.cpp`:

- converts mesh and supports into solver arrays
- sets constraints
- maps basis/support loads
- calls:
  - `plate_setup()`
  - `pload()`
  - `formk()`
  - `solve()`
  - `out()`

Those functions live in the internal solver implementation, mainly `plop_src/plop_xe10/plate.cpp`.

So the default Plop run uses the internal plate solver.

### 5. Plotting and graphics

The plotting layer is mostly in `plop_src/plop_xe10/plot.cpp` and related GUI picture forms.

It supports:

- mesh views
- support views
- color displacement plots
- contour plots
- part drawings
- Z88 result visualization

### 6. GUI application

The GUI lives in `plop_src/plop_xe10/gui_plop`.

This is a VCL/Embarcadero C++Builder Windows app targeting Win32. The project file `gui_plop.cbproj` shows:

- `FrameworkType` = `VCL`
- platform default = `Win32`
- compile defines including `gui_plop`, `use_gd_graphics`, `use_sparse`

The GUI is tightly coupled to the core via shared global state and direct calls into core functions.

### 7. Z88 integration

Z88 is present, but it is not the default solve backend for ordinary Plop execution.

Instead, Z88 is used as an auxiliary path:

- Plop can generate Z88 input files
- the GUI can launch `z88i1plop.exe` and `z88i2plop.exe`
- deflection results are then loaded back for visualization

That path is driven from the GUI, not from the default `exec_plate()` solve.

## Build and Packaging

### GUI build

The GUI is built with Embarcadero C++Builder using `gui_plop.cbproj`.

Implications:

- Windows-only target in practice
- toolchain-specific project format
- some local include/library path assumptions remain in the project

### Core/makefile build

There is also a GNU-style `makefile` in `plop_src/plop_xe10` for building CLI/core binaries such as:

- `plate`
- `grid_gen`
- `plot`
- `plop`

There is a second `makefile` under `plop_src/z88src/z88mix12` for the Z88 executables.

### Installer

`plop_src/plop_xe10/gui_plop/inno_setup.iss` packages:

- `gui_plop.exe`
- the user manual
- `z88i1plop.exe`
- `z88i2plop.exe`
- support files such as `z88.dyn` and `z88i4.txt`

It also registers `.gr` file association and stores install-related values in the Windows registry.

## Architecture Characteristics

### Strong coupling

The GUI and core are tightly coupled through:

- global variables
- shared arrays
- direct function calls
- shared plotting buffers
- shared synchronization hooks

There is no clear separation between:

- domain layer
- application layer
- presentation layer

### Global state everywhere

The system relies heavily on global arrays and global flags declared across `global.h`, `plate_global.cpp`, and related modules.

This simplifies the original codebase but makes change isolation and testing difficult.

### Fixed-size limits

The code uses many hardcoded limits, for example:

- `default_max_points`
- `max_basis_size`
- `max_mesh_radii`
- `max_support_radii`
- `max_opt_vars`

These are operational constraints, not just implementation details.

### Legacy C/C++ style

The codebase uses patterns typical of older C/C++ Windows applications:

- fixed buffers
- `sprintf`
- custom parsing
- ad hoc memory management
- compile-time flags for multiple modes
- platform/compiler conditionals

## Risks and Maintenance Notes

### 1. Build reproducibility risk

The repository does not look ready for a clean, modern, reproducible build on a fresh machine without toolchain-specific setup.

Main reasons:

- Embarcadero C++Builder dependency
- local path remnants in project configuration
- mixed build systems
- repository contains archive artifacts and legacy backup files

### 2. Change risk in numerical code

Because of the global-state architecture, even small changes can have non-local effects on:

- parser behavior
- GUI state loading
- plotting
- optimization
- solver inputs

### 3. Weak validation story

No obvious automated tests or CI guardrails are present in the repository.

That means the practical validation strategy would need to rely on:

- manual GUI flows
- sample `.gr` files
- numerical result comparison

### 4. Windows/runtime dependency risk

The GUI depends on:

- Windows registry keys
- installed file layout
- bundled executables for Z88 flow

That increases fragility outside the packaged installer environment.

## Notable Observations

- The README claims current version `3.0.7`.
- The installer script also packages `Gui Plop 3.0.7`.
- The GUI code still contains `CurrentVersion = "3.0.6"` in `MeshEdit.cpp`.

That version mismatch is a concrete sign that source, packaging, and release metadata are not fully synchronized.

## Practical Reading Order

If further work is needed on this repository, the most useful reading order is:

1. `plop_src/plop_xe10/gui_plop/MeshEdit.cpp`
2. `plop_src/plop_xe10/gui_plop/Run.cpp`
3. `plop_src/plop_xe10/plop_run.cpp`
4. `plop_src/plop_xe10/plop_parser.cpp`
5. `plop_src/plop_xe10/grid_gen.cpp`
6. `plop_src/plop_xe10/plate.cpp`
7. `plop_src/plop_xe10/plot.cpp`

That order follows the actual user flow from editor to execution to solver to plots.

## Conclusion

`plop` is a legacy Win32/VCL engineering application with a custom numerical core, an optional Z88 export/run path, and a GUI tightly bound to global computational state.

It is understandable and modifiable, but not lightweight to modernize. Any non-trivial change should be treated as legacy maintenance work, with conservative scope and explicit validation against representative `.gr` cases.
