[CmdletBinding()]
param(
    [string]$QtRoot = (Join-Path $env:USERPROFILE "Qt"),
    [string]$QtVersion = "6.8.3",
    [string]$QtArch = "mingw_64",
    [string]$MingwToolDir = "mingw1310_64",
    [string]$BuildDir = "build-qt",
    [switch]$Clean
)

$ErrorActionPreference = "Stop"

$qtPrefix = Join-Path $QtRoot "$QtVersion\$QtArch"
$qtBin = Join-Path $qtPrefix "bin"
$mingwBin = Join-Path $QtRoot "Tools\$MingwToolDir\bin"
$compiler = Join-Path $mingwBin "g++.exe"

foreach ($path in @($qtPrefix, $qtBin, $mingwBin, $compiler)) {
    if (-not (Test-Path -LiteralPath $path)) {
        throw "Required Qt path not found: $path"
    }
}

if ($Clean -and (Test-Path -LiteralPath $BuildDir)) {
    Remove-Item -LiteralPath $BuildDir -Recurse -Force
}

$env:PATH = "$qtBin;$mingwBin;$env:PATH"

$configureArgs = @(
    "-S", ".",
    "-B", $BuildDir,
    "-G", "Ninja",
    "-DCMAKE_PREFIX_PATH=$qtPrefix",
    "-DCMAKE_CXX_COMPILER=$compiler"
)

& cmake @configureArgs
& cmake --build $BuildDir
& cmake --build $BuildDir --target plop_gui_qt_deploy
