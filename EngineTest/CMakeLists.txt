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
configure_file("${SDL_DLL_PATH}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

set_property(TARGET EngineTest PROPERTY CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID  MATCHES  "MSVC")
    target_compile_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/Zi>")
    target_link_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
    target_link_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
    target_link_options(WontonEngine PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES  "MSVC")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi" CACHE STRING "" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF" CACHE STRING "" FORCE)
endif()

file(COPY "Assets" DESTINATION "${CMAKE_BINARY_DIR}/EngineTest")
file(COPY "shaders" DESTINATION "${CMAKE_BINARY_DIR}/EngineTest")

# TODO: Add tests and install targets if needed.
