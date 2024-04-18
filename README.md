<div align="center">
  <h1>Supported Version: 14.8</h1>
  <p>

  [![GitHub License](https://img.shields.io/github/license/Gn3po4g/OrbWalker)](https://mit-license.org/)
  [![imgui Version](https://img.shields.io/vcpkg/v/imgui?label=imgui)](https://github.com/ocornut/imgui)
  [![glm Version](https://img.shields.io/vcpkg/v/glm?label=glm)](https://github.com/g-truc/glm)
  [![nlohmann-json Version](https://img.shields.io/vcpkg/v/nlohmann-json?label=nlohmann-json)](https://github.com/nlohmann/json)

  </p>
</div>

# Features
+ The keys for all functions are configurable.
+ Show/Hide attack range and mouse clicks.
+ Attack champions only, or attack minions.
+ Lock the currently selected target.

# Build
+ Install Visual Studio 2022 and c++ components(msbuild).
+ Install [vcpkg](https://github.com/microsoft/vcpkg#user-content-quick-start-windows) for VS2022.
+ Run the command in `Developer PowerShell for VS 2022`.

  ```cmd
	git clone https://github.com/Gn3po4g/OrbWalker.git
	cd OrbWalker
	msbuild -p:Configuration=Release
  ```
  
  Or you can open `OrbWalker.sln` and use GUI to build.
+ The output file(Hid.dll) is generated at `Out` directory.

# Usage
Download or build `Hid.dll` and put it into your Game folder(e.g. xx\Riot Games\League of Legends\Game).
