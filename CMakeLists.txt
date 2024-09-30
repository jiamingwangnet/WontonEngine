# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# CACHE variables
set(SDL_LIB_PATH "" CACHE STRING "Path to the SDL library file (.lib).")
set(SDL_DLL_PATH "" CACHE STRING "Path to the SDL dynamic link library (.dll).")
set(SDL_INCLUDE_PATH "" CACHE STRING "Path to the SDL include directory.")
set(GLM_INCLUDE_PATH "" CACHE STRING "Path to the GLM include directory.")
set(ENGINE_BIN_PATH "" CACHE STRING "Path to the engine output binaries.")

message("----------PATHS----------")
message("SDL STATIC LIBRARY : ${SDL_LIB_PATH}")
message("SDL DYNAMIC LIBRARY: ${SDL_DLL_PATH}")
message("SDL INCLUDE        : ${SDL_INCLUDE_PATH}")
message("GLM INCLUDE        : ${GLM_INCLUDE_PATH}")
message("ENGINE BIN PATH    : ${ENGINE_BIN_PATH}")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if("${CMAKE_CXX_COMPILER}" STREQUAL "g++.exe")
	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

project ("WontonEngine")

# Include sub-projects.
add_subdirectory ("WontonEngine")
add_subdirectory ("EngineTest")
