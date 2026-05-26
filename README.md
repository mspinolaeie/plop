# plop
This is the repository for plop.
Download the gui_plop_setup_3_0_7.exe from the release and execute it. Current version is 3.0.7.

https://github.com/davidlewistoronto/plop/releases/download/3.0.7/gui_plop_setup_3_0_7.exe


If you just want to learn more about plop, download the manual in the link

https://github.com/davidlewistoronto/plop/blob/main/GuiPlop%20Users%20Manual.pdf


For a helpful introduction see Martin Lewis' page

https://skyinspector.co.uk/use-of-plop/

## Local build

The repository now supports a local MinGW build through CMake.

Core and Z88 tools:

```powershell
cmake -S . -B build -G Ninja -DPLOP_BUILD_QT_GUI=OFF
cmake --build build
```

Outputs are written to `build/bin`:

- `plop_cli.exe`
- `z88i1plop.exe`
- `z88i2plop.exe`

Runtime assets such as `z88.dyn`, `z88i4.txt`, the user manual, and `autocell/` are staged into the same output directory.

## Qt GUI

If Qt Widgets is installed and discoverable by CMake, enable the Qt frontend:

```powershell
cmake -S . -B build -G Ninja
cmake --build build
```

This produces `build/bin/plop_gui_qt.exe`. The Qt GUI uses app-relative runtime files and `QSettings`; it does not depend on the legacy installer registry keys.
