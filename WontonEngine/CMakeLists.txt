# CMakeList.txt : CMake project for WontonEngine, include source and define
# project specific logic here.
#

file(GLOB exec_src CONFIGURE_DEPENDS
        "*.cpp"
        "stb/stb_image.cpp"
        "glad/src/glad.c"

)

file(GLOB exec_head CONFIGURE_DEPENDS
        "include/WontonEngine/*.h"
        "include/WontonEngine/Components/*.h"
        "include/WontonEngine/Rendering/*.h"
        "include/WontonEngine/Math/*.h"
        "glad/include/glad/glad.h"
        "stb/include/stb/stb_image.h"
        "${SDL_INCLUDE_PATH}"
        "${GLM_INCLUDE_PATH}"
)

# Add source to this project's executable.
add_library (WontonEngine STATIC ${exec_src} ${exec_head})

target_include_directories(WontonEngine PRIVATE "${SDL_INCLUDE_PATH}")
target_include_directories(WontonEngine PRIVATE "${GLM_INCLUDE_PATH}")
target_include_directories(WontonEngine PRIVATE glad/include)
target_include_directories(WontonEngine PRIVATE stb/include)

target_link_libraries(WontonEngine "${SDL_LIB_PATH}")

set_property(TARGET WontonEngine PROPERTY CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID  STREQUAL "MSVC")
    target_compile_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/Zi>")
    target_link_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
    target_link_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
    target_link_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")
endif()



# TODO: Add tests and install targets if needed.
