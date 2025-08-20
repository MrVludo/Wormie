cmake_minimum_required(VERSION 3.5)
project(Wormie)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external/raylib)
include_directories(external/raylib/src)

add_executable(Wormie 
    src/config.hh 
    src/snakeClass.cc 
    src/snake.cc 
    src/tetorm.cc 
    src/TetormBlocks.cc
    src/KeyboardEvents.cc 
    src/main.cc
    res/resources.rc
)

if (WIN32)
    target_link_libraries(Wormie raylib opengl32 gdi32 winmm)
    set_target_properties(Wormie PROPERTIES WIN32_EXECUTABLE TRUE)
elseif (UNIX)
    target_link_libraries(Wormie raylib GL X11 pthread dl m)
endif()
