# CMakeList.txt : CMake project for EngineTest, include source and define
# project specific logic here.
#

file(GLOB exec_src CONFIGURE_DEPENDS
        "*.cpp"

)

file(GLOB exec_head CONFIGURE_DEPENDS
        "include/*.h"
        "../WontonEngine/include/*.h"
)

# Add source to this project's executable.
add_executable (EngineTest ${exec_src} ${exec_head})

target_include_directories(EngineTest PRIVATE ../WontonEngine/include/)

target_link_libraries(EngineTest "${ENGINE_BIN_PATH}")

set_property(TARGET EngineTest PROPERTY CXX_STANDARD 17)


# TODO: Add tests and install targets if needed.
