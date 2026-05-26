# Gui Plop Module Map

## Scope

This document maps the GUI modules under `plop_src/plop_xe10/gui_plop` from a maintenance perspective:

- which form owns which user workflow
- how GUI modules talk to the numerical core
- where data synchronization happens
- which modules are structural and which are only accessory

## Overall GUI Architecture

The GUI is a classic VCL multi-form application. All major forms are created eagerly at startup in `gui_plop.cpp`, not lazily on demand.

Startup sequence:

- `_tWinMain` stores raw startup arguments
- `Application->CreateForm(...)` constructs all major forms
- `TCellEditForm` acts as the primary editor/main window
- `TRunForm` acts as the execution and results control window
- picture windows and accessory dialogs are secondary forms

This architecture assumes global singleton-like form instances and extensive cross-form calls.

## High-Level Functional Areas

### 1. Main editor and repository of GUI state

Primary module:

- `MeshEdit.cpp`
- `MeshEdit.h`

Primary class:

- `TCellEditForm`

This is the real center of the GUI.

Responsibilities:

- open/save `.gr` files
- load parser state into GUI controls
- copy GUI values back into Plop globals
- manage tabs for mirror/material/support/basis/variables/text/parts/Z88 parameters
- maintain recent files
- read installation metadata from registry
- initialize the core runtime and memory
- act as the source of truth for current editable model state

Important detail:

`TCellEditForm` is not just a form. It is effectively:

- main editor
- install/runtime bootstrapper
- registry/config manager
- UI-to-core mapping layer

That makes it the most important GUI module to understand before any change.

### 2. Run control and live execution status

Primary module:

- `Run.cpp`
- `Run.h`

Primary class:

- `TRunForm`

Responsibilities:

- start a Plop run
- collect run options from GUI controls
- create the worker thread
- show progress, optimization steps, Monte Carlo status
- update visible plots and error fields
- gate the optional Z88 flow

This form is the operational controller for the computation phase.

### 3. Worker thread and UI synchronization

Primary module:

- `PlopExec.cpp`
- `PlopExec.h`

Primary class:

- `PlopExec`

Responsibilities:

- run `init_default_basis()`
- run `plate_init()`
- run `run_plate()`
- synchronize updates back to the VCL thread

Key synchronization methods:

- `UpdatePicsSync`
- `UpdateOptStatusSync`
- `UpdateStatusSync`
- `UpdateMonteSync`
- `UpdateCellEditOptVarsSync`

This is the bridge between long-running computation and the GUI message thread.

### 4. Plot and image presentation layer

Primary modules:

- `Picture.cpp`
- `Picture.h`
- derived picture form files

Primary class:

- `TPictureForm`

Derived forms:

- `TMeshPictureForm`
- `TSupportPictureForm`
- `TColorPictureForm`
- `TContourPictureForm`
- `TCellPartPictureForm`
- `TQuadPictureForm`
- `TZ88ColorPictureForm`

Responsibilities:

- host a `TImage`
- maintain an 8-bit bitmap and palette
- render the appropriate visualization based on `PictureStyle`
- save/copy rendered results
- redraw when new computation output is available

This is a shared base-form pattern, with behavior selected by style instead of deep subclass specialization.

### 5. Part geometry dimension view

Primary module:

- `PartDimension.cpp`
- `PartDimension.h`

Primary class:

- `TPartDimensionForm`

Responsibilities:

- draw a single part in a dimension-oriented view
- expose CG and coordinate labels
- support unit switching
- support rotation cycling

This module is conceptually adjacent to picture forms, but it is implemented separately rather than inheriting from `TPictureForm`.

### 6. UI-to-core binding utilities

Primary modules:

- `PlopInterface.h`
- `NumEdit.h`
- `NumEdit.cpp`
- `TCEdit.h`
- `TCEdit.cpp`

Responsibilities:

- define the mapping structure between GUI controls and Plop parameters
- provide compound editable controls for:
  - fixed values
  - optimization variables
  - scan ranges
  - scan sets
  - Monte Carlo deltas
- track active control identity for scrolling/edit behavior

This is the local abstraction layer that makes the editor usable without creating hundreds of hardcoded individual handlers.

## Main Form Map

### `TCellEditForm` in `MeshEdit.*`

This is the dominant form in the application.

#### User-facing workflows

- File open/save/save-as
- edit mirror/material/support/basis/variable data
- edit raw `.gr` text
- open run window
- open graphics windows
- open part/dimension windows
- open help/about/what’s new

#### Internal responsibilities

- reads install/runtime settings from registry:
  - `AutoCellLoc`
  - `HelpFileLoc`
  - `PlopLoc`
  - `LastVersionRun`
- creates dynamic control sets for:
  - variables
  - support rings
  - basis rings
  - parts
- initializes core runtime:
  - `init_plop()`
  - `set_max_points(...)`
  - `init_graphics()`
  - `alloc_globals()`
  - `alloc_plate_globals()`
- captures process-wide messages with `Application->OnMessage = ProcessMessage`

#### Data role

`TCellEditForm` stores a large amount of GUI-side structured state:

- variable names and values
- support ring edit state
- basis ring edit state
- general parameter edit state
- part editing state
- clipboard-like temporary copies for duplication/paste actions

#### Core coupling points

Most important methods:

- `LoadFromPlop()`
  - copies parser/global state into GUI controls
- `CopyToPlop(bool allow_err)`
  - pushes GUI state back into Plop globals
- `AddToPlopMap(...)`
  - binds GUI widgets to parameter names
- `StoreNumEditState(...)`
  - parses GUI values into parameter or variable state

This is the main serialization/deserialization boundary between GUI and computation state.

#### Why it matters

If a change affects parameter semantics, `.gr` loading, run setup, or on-screen editing, `TCellEditForm` is almost certainly involved.

### `TRunForm` in `Run.*`

`TRunForm` is the execution dashboard.

#### User-facing workflows

- launch computation
- pause/resume/abort
- view RMS/PV output
- watch optimization progress
- watch Monte Carlo progress
- enable output tracing
- enable Zernike output
- enable basis mode
- generate Z88 input
- run the Z88 backend path
- open output picture windows

#### Internal responsibilities

- reads run-option controls and writes into global run flags
- validates the editor state before starting execution
- creates and resumes `PlopExec`
- updates displayed result fields
- enables/disables editor operations while Plop is running

#### Core coupling points

Directly manipulates global runtime flags such as:

- `use_p_v_error`
- `refocus_flag`
- `refocus_xyr_flag`
- `generate_z88_input_flag`
- `calculate_zernike_flag`
- `trace_opt`
- `grid_gen_using_basis`

It also reads result globals such as:

- `plate_err_vis_rms`
- `plate_err_vis_p_v`
- `plate_refocus_focal_length`
- `z88_plot_err_vis_rms`
- `z88_plot_err_vis_p_v`

#### Z88-specific role

`RunZ88ButtonClick()`:

- builds paths to `z88i1plop.exe` and `z88i2plop.exe`
- sets `PLOPDIR`
- launches both executables via `spawnl`
- calls `load_z88_deflection_data(n_mesh_depth)`
- refreshes Z88 error display and Z88 picture availability

So `TRunForm` owns the whole optional external Z88 execution path.

### `PlopExec` in `PlopExec.*`

This thread wrapper is small but critical.

#### Responsibilities

- execute long-running numerical work outside the UI thread
- use `Synchronize(...)` for safe VCL updates
- notify `RunForm` when execution finishes
- support progress/status updates from the core

#### Architectural role

It is not an independent service layer. It is a thin threading shell around direct core calls. That keeps behavior simple, but preserves the tight coupling between GUI and computational globals.

## Visualization Module Map

### `TPictureForm` in `Picture.*`

This is a shared rendering surface with style-driven behavior.

#### Picture styles

- `PicStyleMesh`
- `PicStyleSupports`
- `PicStyleColor`
- `PicStyleContour`
- `PicStyleParts`
- `PicStyleQuads`
- `PicStyleZ88Color`

#### Rendering behavior

`DrawPic()` switches on `PictureStyle` and chooses one of:

- `DrawMesh(...)`
- `DrawQuads(...)`
- `calculate_plop_plot(...) + LoadPlopPic(...)`
- `calculate_z88_plot(...) + LoadPlopPic(...)`

#### State model

Important flags:

- `NewPicAvail`
- `SomePicAvail`

These are used to avoid drawing before data exists and to trigger refresh on show/resize.

#### Concurrency model

Rendering locks shared Plop data with:

- `LockPlopData(1)`
- `UnlockPlopData()`

So the picture layer is directly aware of shared mutable computational state.

### Specialized picture forms

The derived forms are intentionally thin:

- `MeshPicture.*`
- `SupportPicture.*`
- `ColorPicture.*`
- `ContourPicture.*`
- `CellPartPicture.*`
- `QuadPicture.*`
- `Z88ColorPicture.*`

They mainly exist as separate windows with separate DFM resources and form classes. The real rendering logic remains centralized in `TPictureForm`.

This is a good thing for maintenance: behavior lives mostly in one place.

### `TPartDimensionForm` in `PartDimension.*`

This module deserves separate attention.

It draws part-local geometry rather than the global mirror field and exposes:

- current part number
- CG radius and angle
- CG X/Y
- per-corner coordinates
- units toggle
- rotation cycling

It also calls `evaluate_parts()` when rotation changes, so it is not purely passive display.

## Accessory Dialog Map

### `TAutoCellForm` in `AutoCell.*`

Purpose:

- wizard-like shortcut for generating standard cell layouts

Behavior:

- collects diameter/thickness/focal/secondary/hole values
- selects a cell template
- builds a `.gr` filename from registry-based `AutoCellLoc`
- loads that file via `read_info(...)`
- updates the main editor state
- opens the run form

This is effectively a template-driven bootstrap workflow for common configurations.

### `TGraphOptionsForm` in `GraphOptions.*`

Purpose:

- configure plot rendering parameters

Controls:

- number of colors
- number of contours
- Z-axis range
- contour spacing

Behavior:

- writes directly into global plotting parameters
- redraws visible affected plot windows immediately

### `TDebugForm` in `Debug.*`

Purpose:

- toggle and inspect debug facilities

Capabilities:

- debug trace memo
- debug flags checkboxes
- debug file selection
- memory usage display
- registry viewer launch

This is a diagnostic support window rather than a core workflow window.

### `TRegViewer` in `RegView.*`

Purpose:

- inspect registry contents interactively

This is a support/debugging tool and not essential to normal end-user workflow.

### `TAboutBox` in `About.*`

Purpose:

- application identity/version/about information

Notable detail:

- it displays `CurrentVersion`
- current source still reports `3.0.6` in `MeshEdit.cpp`

### `TWhatsNewForm` in `WhatsNew.*`

Purpose:

- show release/update information

Likely part of first-run or version-change behavior.

### `TRunFinishedForm` in `PlopExecDone.*`

Purpose:

- modal completion notification after a run

### `TRunOptionsForm` in `RunOptions.*`

This appears to be structurally present but functionally lightweight in the current code. It does not carry meaningful logic on its own.

## Data and Control Flow

## 1. Startup flow

1. `gui_plop.cpp` creates all forms.
2. `TCellEditForm::FormCreate()` initializes registry, dynamic controls, runtime globals, memory, and optional startup file loading.
3. `TRunForm::FormCreate()` configures picture styles and palettes.

## 2. File load flow

1. User opens a `.gr` file from `TCellEditForm`.
2. `read_info(...)` parses the file into Plop globals.
3. `LoadFromPlop()` copies global state into GUI controls.
4. Plot and part-related forms are refreshed to match current state.

## 3. Run flow

1. User starts execution from `TRunForm`.
2. `TCellEditForm::CopyToPlop(false)` validates and writes GUI state into globals.
3. `TRunForm` sets global runtime flags.
4. `PlopExec` thread runs `run_plate()`.
5. Core code calls GUI callback functions for progress/optimization/Monte updates.
6. `RunForm` and picture windows refresh through synchronized methods.

## 4. Z88 flow

1. User enables Z88 input generation.
2. `run_plate()` produces Z88 input files.
3. `TRunForm::RunZ88ButtonClick()` launches external Z88 executables.
4. GUI loads deflection output and exposes a Z88-specific color plot.

## Coupling and Risk Areas

### Tightest coupling points

- `TCellEditForm` <-> parser/global parameter tables
- `TRunForm` <-> global run flags and result globals
- `TPictureForm` <-> global plotting buffers and mesh/result arrays
- `PlopExec` <-> direct core entrypoints

### Highest-maintenance modules

If changes are planned, the most fragile/high-impact GUI files are:

1. `MeshEdit.cpp`
2. `Run.cpp`
3. `Picture.cpp`
4. `PartDimension.cpp`
5. `PlopExec.cpp`

### Why these are fragile

- they sit on shared mutable globals
- they coordinate multiple forms
- they mix UI code with domain assumptions
- they include manual synchronization or validation logic

## Practical Guidance for Future Work

### If changing parameter editing

Start in:

- `MeshEdit.cpp`
- `MeshEdit.h`
- `PlopInterface.h`
- `NumEdit.*`

### If changing run behavior

Start in:

- `Run.cpp`
- `PlopExec.cpp`
- `plop_run.cpp`

### If changing plot behavior

Start in:

- `Picture.cpp`
- `GraphOptions.cpp`
- `plot.cpp`

### If changing Z88 workflow

Start in:

- `Run.cpp`
- `grid_gen.cpp`
- `plot.cpp`
- installer/registry assumptions in `inno_setup.iss` and `MeshEdit.cpp`

## Conclusion

The GUI is organized around one dominant editor form, one dominant run-control form, a thin worker thread wrapper, and a centralized picture-rendering base class with multiple window shells.

This is not a modular MVC-style GUI. It is a tightly integrated engineering desktop application where:

- forms are global peers
- state is largely global
- synchronization is manual
- domain logic leaks into presentation code

That makes the code workable, but it also means GUI changes should be scoped conservatively and validated through the actual form interaction paths they affect.
