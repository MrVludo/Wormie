# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Vludo\AppData\Roaming\winlibs-x86_64-posix-seh-gcc-12.3.0-llvm-16.0.4-mingw-w64ucrt-11.0.0-r1\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Vludo\AppData\Roaming\winlibs-x86_64-posix-seh-gcc-12.3.0-llvm-16.0.4-mingw-w64ucrt-11.0.0-r1\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Vludo\Wormie

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Vludo\Wormie\build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include external/raylib/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include external/raylib/CMakeFiles/uninstall.dir/progress.make

external/raylib/CMakeFiles/uninstall:
	cd /d C:\Users\Vludo\Wormie\build\external\raylib && C:\Users\Vludo\AppData\Roaming\winlibs-x86_64-posix-seh-gcc-12.3.0-llvm-16.0.4-mingw-w64ucrt-11.0.0-r1\mingw64\bin\cmake.exe -P C:/Users/Vludo/Wormie/build/external/raylib/cmake_uninstall.cmake

uninstall: external/raylib/CMakeFiles/uninstall
uninstall: external/raylib/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
external/raylib/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : external/raylib/CMakeFiles/uninstall.dir/build

external/raylib/CMakeFiles/uninstall.dir/clean:
	cd /d C:\Users\Vludo\Wormie\build\external\raylib && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : external/raylib/CMakeFiles/uninstall.dir/clean

external/raylib/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Vludo\Wormie C:\Users\Vludo\Wormie\external\raylib C:\Users\Vludo\Wormie\build C:\Users\Vludo\Wormie\build\external\raylib C:\Users\Vludo\Wormie\build\external\raylib\CMakeFiles\uninstall.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external/raylib/CMakeFiles/uninstall.dir/depend

