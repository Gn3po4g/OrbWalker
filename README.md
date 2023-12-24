<h1 align="center">Supported Version: 13.24</h1>

# Feature
1. Skin Changer(thanks to [R3nzSkin](https://github.com/R3nzTheCodeGOD/R3nzSkin)).
2. Show attack range.
3. Hold space to attack champions, hold v to clean line(configurable).
4. Left-click to lock on target.

# Build:

+ Use Visual Studio 2022.
+ Use the following command to install the dependencies in Visual Studio 2022 via [vcpkg](https://github.com/microsoft/vcpkg):
```cmd
vcpkg install imgui[core,dx11-binding,win32-binding]:x64-windows-static
vckpg install glm
```
+ Build the solution or project.
+ The output file(Hid.dll) is generated at Out directory.

# Usage:

Download or build Hid.dll and put it into your Game folder(e.g. xx\Riot Games\League of Legends\Game).