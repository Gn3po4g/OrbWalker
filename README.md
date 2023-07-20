<h1 align="center">Supported Version: 13.14</h1>

# Build:

+ Use Visual Studio 2022.
+ Add CMake and C++ Modules in VS.
+ Change GAME_DIRECTORY in CMakeLists.txt to your game installation directory.
+ Build the project with Release instead of Debug(You need to build several times because the modules depend on each
  other and all the modules should be compiled).
+ The output file will automatically be generated into Game folder.

# Usage:

Download Hid.dll and put it into your Game folder(e.g. xx\Riot Games\League of Legends\Game).