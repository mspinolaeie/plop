# plop

`plop` is a legacy desktop application for mirror support analysis.

The repository still contains the original Windows installer/release flow, but it now also supports a reproducible local build on Windows with:

- MinGW + CMake for the legacy numerical core
- Qt Widgets for the new local GUI frontend
- bundled Z88 executables built from source

## Main paths

- end-user manual: [GuiPlop Users Manual.pdf](GuiPlop%20Users%20Manual.pdf)
- repository analysis: [repo-analysis.md](repo-analysis.md)
- legacy GUI module map: [gui-module-map.md](gui-module-map.md)
- local build guide: [LOCAL_BUILD.md](LOCAL_BUILD.md)

## Current local build outputs

A successful local Qt build produces these runtime artifacts in `build-qt/bin`:

- `plop_cli.exe`
- `plop_gui_qt.exe`
- `z88i1plop.exe`
- `z88i2plop.exe`

The runtime directory is also populated with:

- Qt DLLs and plugins via `windeployqt`
- `z88.dyn`
- `z88i4.txt`
- `GuiPlop Users Manual.pdf`
- `autocell/` when present in the source tree

## Quick start

CLI/core only:

```powershell
cmake -S . -B build -G Ninja -DPLOP_BUILD_QT_GUI=OFF
cmake --build build
```

Full Qt build on this machine layout:

```powershell
.\build-local-qt.ps1 -Clean
```

## Qt installation path used locally

The local Qt workflow was validated with:

- `Qt 6.8.3`
- `mingw_64`
- `Tools\mingw1310_64`
- installed under `C:\Users\matteo\Qt`

If Qt is not installed yet, see [LOCAL_BUILD.md](LOCAL_BUILD.md) for the exact `aqtinstall` commands.

## Legacy installer

The original project README/release flow pointed users to the packaged installer:

https://github.com/davidlewistoronto/plop/releases/download/3.0.7/gui_plop_setup_3_0_7.exe

That installer path remains relevant for end users of the historical VCL application, but source development can now proceed through the local CMake flow described above.

## References

- manual PDF in this repository
- GitHub release installer link above
- Martin Lewis introduction: https://skyinspector.co.uk/use-of-plop/
