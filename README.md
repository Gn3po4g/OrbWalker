<h1 style="text-align: center;">
    Supported Version: 13.13
</h1>

# Build:

+ Using Visual Studio 2022(for c++20 Module support).
+ Add Cmake in VS.
+ Build the project with Release instead of Debug(You need to build several times because the modules depend on each other and all the modules should be compiled).

# Usage:

**Use in any of the following ways：**

1. Download Hid.dll and put it into your Game folder(e.g. xx\Riot Games\League of Legends\Game).
2. Build the project and inject the output file(OrbWalker.dll) into League of Legends.exe with an injector.
3. Build the project and rename the output file to Hid.dll. Then put it into your Game folder.
