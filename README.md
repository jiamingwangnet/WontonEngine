# WontonEngine

A game engine/framework to help develop games.

See [EngineTest](https://github.com/jiamingwangnet/WontonEngine/tree/master/EngineTest) for example code.

Documentation coming soon.

Prebuilt binaries for Windows at the [latest release](https://github.com/jiamingwangnet/WontonEngine/releases/tag/v0.2.1)

## Build Instructions (for Windows only)

### Prerequisites

1. Clone and extract the files into your desired location.
2. Clone and build SDL3 at [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)
3. Download GLM at [https://sourceforge.net/projects/glm.mirror/](https://sourceforge.net/projects/glm.mirror/)

### Using Visual Studio

1. Start up Visual Studio and select _"Open a local folder"_
2. Open up the project root directory (the directory with `CMakeLists.txt`)
3. Edit the cache variables in `CMakePresets.json` for your desired build configuration
```json
...
"cacheVariables": {
	"CMAKE_BUILD_TYPE": "Release/Debug",
	"SDL_LIB_PATH": "/My/Path/To/SDL3.lib",
	"SDL_DLL_PATH": "/My/Path/To/SDL3.dll",
	"SDL_INCLUDE_PATH": "/My/Path/To/SDL3/include",
	"GLM_INCLUDE_PATH": "/My/Path/To/GLM"
},
...
```
4. Visual Studio should automatically configure after the file is saved
5. Build and run the project

### Using CMake GUI

1. Start up CMake GUI
2. Put in the project root directory in the _"Where is the source code"_ text box
3. Select the configuration (you may need to select twice for the cache variables to pop up)
4. Set the cache variables
```
Name                      Value
SDL_LIB_PATH              /My/Path/To/SDL3.lib
SDL_DLL_PATH              /My/Path/To/SDL3.dll
SDL_INCLUDE_PATH          /My/Path/To/SDL3/include
GLM_INCLUDE_PATH          /My/Path/To/GLM
```
5. Press _"Configure"_ and then _"Generate"_
6. Open command prompt and `cd` into the build directory (should be in the _"Where to build the binaries"_ text box)
7. Run `nmake` if using Nmake generator or `ninja` if using Ninja generator
	- Make sure both programs are in `Path`
