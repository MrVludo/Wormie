cmake_minimum_required(VERSION 3.5)
project(Wormie)

set(CMAKE_CXX_STANDARD 11)

# Подключаем raylib как подмодуль
add_subdirectory(external/raylib)
include_directories(external/raylib/src)

# Создаём исполняемый файл
add_executable(Wormie 
    src/config.hh 
    src/snakeClass.cc 
    src/snake.cc 
    src/tetorm.cc 
    src/TetormBlocks.cc
    src/KeyboardEvents.cc 
    src/main.cc
)

# Подключаем библиотеки в зависимости от платформы
if (WIN32)
    target_link_libraries(Wormie raylib opengl32 gdi32 winmm)
elseif (UNIX)
    target_link_libraries(Wormie raylib GL X11 pthread dl m)
endif()

# Делаем статическую линковку
# set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")

set_target_properties(Wormie PROPERTIES WIN32_EXECUTABLE TRUE)
