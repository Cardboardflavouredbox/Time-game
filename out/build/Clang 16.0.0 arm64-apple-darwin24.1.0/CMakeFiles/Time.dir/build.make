# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/greenbox/GitHub/Time-platformer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0"

# Include any dependencies generated for this target.
include CMakeFiles/Time.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Time.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Time.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Time.dir/flags.make

CMakeFiles/Time.dir/codegen:
.PHONY : CMakeFiles/Time.dir/codegen

CMakeFiles/Time.dir/main.c.o: CMakeFiles/Time.dir/flags.make
CMakeFiles/Time.dir/main.c.o: /Users/greenbox/GitHub/Time-platformer/main.c
CMakeFiles/Time.dir/main.c.o: CMakeFiles/Time.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Time.dir/main.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Time.dir/main.c.o -MF CMakeFiles/Time.dir/main.c.o.d -o CMakeFiles/Time.dir/main.c.o -c /Users/greenbox/GitHub/Time-platformer/main.c

CMakeFiles/Time.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Time.dir/main.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/greenbox/GitHub/Time-platformer/main.c > CMakeFiles/Time.dir/main.c.i

CMakeFiles/Time.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Time.dir/main.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/greenbox/GitHub/Time-platformer/main.c -o CMakeFiles/Time.dir/main.c.s

# Object files for target Time
Time_OBJECTS = \
"CMakeFiles/Time.dir/main.c.o"

# External object files for target Time
Time_EXTERNAL_OBJECTS =

Time: CMakeFiles/Time.dir/main.c.o
Time: CMakeFiles/Time.dir/build.make
Time: /opt/homebrew/Cellar/sdl2/2.32.8/lib/libSDL2.dylib
Time: /opt/homebrew/Cellar/sdl2_image/2.8.8/lib/libSDL2_image.dylib
Time: /opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib/libSDL2_ttf.dylib
Time: /opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib/libSDL2_mixer.dylib
Time: CMakeFiles/Time.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Time"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Time.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Time.dir/build: Time
.PHONY : CMakeFiles/Time.dir/build

CMakeFiles/Time.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Time.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Time.dir/clean

CMakeFiles/Time.dir/depend:
	cd "/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/greenbox/GitHub/Time-platformer /Users/greenbox/GitHub/Time-platformer "/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0" "/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0" "/Users/greenbox/GitHub/Time-platformer/out/build/Clang 16.0.0 arm64-apple-darwin24.1.0/CMakeFiles/Time.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Time.dir/depend

