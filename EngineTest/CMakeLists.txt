# CMakeList.txt : CMake project for EngineTest, include source and define
# project specific logic here.
#

file(GLOB exec_src CONFIGURE_DEPENDS
        "*.cpp"

)

file(GLOB exec_head CONFIGURE_DEPENDS
        "include/*.h"
        "../WontonEngine/include/WontonEngine/*.h"
        "../WontonEngine/include/WontonEngine/Components/*.h"
        "../WontonEngine/include/WontonEngine/Rendering/*.h"
        "../WontonEngine/include/WontonEngine/Math/*.h"
        "${SDL_INCLUDE_PATH}"
        "${GLM_INCLUDE_PATH}"
)

# Add source to this project's executable.
add_executable (EngineTest ${exec_src} ${exec_head})

target_include_directories(EngineTest PRIVATE ../WontonEngine/include/)
target_include_directories(EngineTest PRIVATE "${SDL_INCLUDE_PATH}")
target_include_directories(EngineTest PRIVATE "${GLM_INCLUDE_PATH}")

target_link_libraries(EngineTest "${ENGINE_BIN_PATH}")
target_link_libraries(EngineTest "${SDL_LIB_PATH}")

set_property(TARGET EngineTest PROPERTY CXX_STANDARD 17)


# TODO: Add tests and install targets if needed.
