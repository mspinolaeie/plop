# Local Build Guide

This document describes the currently validated local Windows build flow for this repository.

This is a development/build document. It does not redefine the product release policy:

- official end-user release: legacy VCL `Gui Plop`
- local migration/development build: `plop_gui_qt.exe`

## Scope

Validated targets:

- `plop_core`
- `plop_cli.exe`
- `z88i1plop.exe`
- `z88i2plop.exe`
- `plop_gui_qt.exe`

Validated generator:

- `Ninja`

Validated compiler/runtime stack:

- Qt `6.8.3`
- Qt MinGW toolchain `mingw1310_64`
- CMake package prefix `C:\Users\matteo\Qt\6.8.3\mingw_64`

## 1. Install Qt and MinGW

Install `aqtinstall`:

```powershell
py -m pip install --user aqtinstall
```

Install Qt:

```powershell
py -m aqt install-qt -O $env:USERPROFILE\Qt windows desktop 6.8.3 win64_mingw
```

Install the matching MinGW toolchain:

```powershell
py -m aqt install-tool -O $env:USERPROFILE\Qt windows desktop tools_mingw1310 qt.tools.win64_mingw1310
```

Expected tool locations after install:

- `C:\Users\matteo\Qt\6.8.3\mingw_64\bin\qmake.exe`
- `C:\Users\matteo\Qt\6.8.3\mingw_64\bin\moc.exe`
- `C:\Users\matteo\Qt\6.8.3\mingw_64\bin\uic.exe`
- `C:\Users\matteo\Qt\6.8.3\mingw_64\bin\windeployqt.exe`
- `C:\Users\matteo\Qt\Tools\mingw1310_64\bin\g++.exe`

## 2. Full Qt build

Use the helper script:

```powershell
.\build-local-qt.ps1 -Clean
```

What the script does:

- prepends Qt and MinGW `bin` directories to `PATH`
- configures `build-qt`
- forces `CMAKE_CXX_COMPILER` to the Qt-provided MinGW
- builds all targets
- runs `plop_gui_qt_deploy` to copy Qt runtime files next to `plop_gui_qt.exe`

## 3. Manual configure/build

If you want the raw commands instead of the script:

```powershell
$env:PATH = "C:\Users\matteo\Qt\6.8.3\mingw_64\bin;C:\Users\matteo\Qt\Tools\mingw1310_64\bin;$env:PATH"

cmake -S . -B build-qt -G Ninja `
  -DCMAKE_PREFIX_PATH=C:\Users\matteo\Qt\6.8.3\mingw_64 `
  -DCMAKE_CXX_COMPILER=C:\Users\matteo\Qt\Tools\mingw1310_64\bin\g++.exe

cmake --build build-qt
cmake --build build-qt --target plop_gui_qt_deploy
```

## 4. CLI-only build

If you only need the numerical core and Z88 tools:

```powershell
cmake -S . -B build -G Ninja -DPLOP_BUILD_QT_GUI=OFF
cmake --build build
```

Outputs go to `build/bin`.

## 5. Smoke tests used

### CLI

A minimal `.gr` smoke input that was used successfully:

```text
diameter 200
thickness 25
f-ratio 6
n-mesh-rings 8
n-mesh-depth 2
rel-support-radii 0.7
num-support 3
basis-ring-size 3
basis-ring-min 4
```

Example run:

```powershell
.\build-qt\bin\plop_cli.exe .\build-qt\smoke-test.gr
```

Observed successful output included:

- `visible rms = 5.791149397e-06`
- `visible p-v = 2.494625038e-05`

### GUI

Runtime smoke validation performed:

- launch `build-qt\bin\plop_gui_qt.exe`
- pass `..\smoke-test.gr`
- verify the process stays alive after startup

## 6. Known warnings

Current build warnings that do not block the build:

- legacy `gets()` usage in `plop_main.cpp`
- legacy string literal to `char *` assignment in `plot.cpp`
- `windeployqt` warning about missing `dxcompiler.dll` and `dxil.dll`

The GUI still launches despite the DirectX compiler warning.

## 7. Notes on layout

The repository ignores local build folders through `.gitignore`:

- `build/`
- `build-qt/`

The recommended runtime location is the generated `build-qt/bin` directory because it contains:

- application executables
- Z88 executables
- runtime support files
- deployed Qt DLLs and plugins
