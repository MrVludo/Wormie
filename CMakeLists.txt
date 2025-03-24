cmake_minimum_required(VERSION 3.5)
project(Wormie)

set(CMAKE_CXX_STANDARD 11)

include_directories(raylib/include)
link_directories(raylib/lib)

add_executable(Wormie 
    src/config.hh 
    src/snakeClass.cc 
    src/snake.cc 
    src/tetorm.cc 
    src/TetormBlocks.cc
    src/KeyboardEvents.cc 
    src/main.cc
)
target_link_libraries(Wormie raylib opengl32 gdi32 winmm)

# set_target_properties(Wormie PROPERTIES WIN32_EXECUTABLE TRUE)