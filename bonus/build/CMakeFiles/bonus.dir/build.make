# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vr3rajag/tutorial/vr3rajag/bonus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vr3rajag/tutorial/vr3rajag/bonus/build

# Include any dependencies generated for this target.
include CMakeFiles/bonus.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bonus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bonus.dir/flags.make

CMakeFiles/bonus.dir/main.cc.o: CMakeFiles/bonus.dir/flags.make
CMakeFiles/bonus.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vr3rajag/tutorial/vr3rajag/bonus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bonus.dir/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bonus.dir/main.cc.o -c /home/vr3rajag/tutorial/vr3rajag/bonus/main.cc

CMakeFiles/bonus.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonus.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vr3rajag/tutorial/vr3rajag/bonus/main.cc > CMakeFiles/bonus.dir/main.cc.i

CMakeFiles/bonus.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonus.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vr3rajag/tutorial/vr3rajag/bonus/main.cc -o CMakeFiles/bonus.dir/main.cc.s

# Object files for target bonus
bonus_OBJECTS = \
"CMakeFiles/bonus.dir/main.cc.o"

# External object files for target bonus
bonus_EXTERNAL_OBJECTS =

bonus: CMakeFiles/bonus.dir/main.cc.o
bonus: CMakeFiles/bonus.dir/build.make
bonus: CMakeFiles/bonus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vr3rajag/tutorial/vr3rajag/bonus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bonus"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bonus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bonus.dir/build: bonus

.PHONY : CMakeFiles/bonus.dir/build

CMakeFiles/bonus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bonus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bonus.dir/clean

CMakeFiles/bonus.dir/depend:
	cd /home/vr3rajag/tutorial/vr3rajag/bonus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vr3rajag/tutorial/vr3rajag/bonus /home/vr3rajag/tutorial/vr3rajag/bonus /home/vr3rajag/tutorial/vr3rajag/bonus/build /home/vr3rajag/tutorial/vr3rajag/bonus/build /home/vr3rajag/tutorial/vr3rajag/bonus/build/CMakeFiles/bonus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bonus.dir/depend

