# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/daniel/Desktop/astar_self/list_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/Desktop/astar_self/list_test/build

# Include any dependencies generated for this target.
include CMakeFiles/list_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/list_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/list_test.dir/flags.make

CMakeFiles/list_test.dir/list_struct_sort.cpp.o: CMakeFiles/list_test.dir/flags.make
CMakeFiles/list_test.dir/list_struct_sort.cpp.o: ../list_struct_sort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniel/Desktop/astar_self/list_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/list_test.dir/list_struct_sort.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/list_test.dir/list_struct_sort.cpp.o -c /home/daniel/Desktop/astar_self/list_test/list_struct_sort.cpp

CMakeFiles/list_test.dir/list_struct_sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/list_test.dir/list_struct_sort.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniel/Desktop/astar_self/list_test/list_struct_sort.cpp > CMakeFiles/list_test.dir/list_struct_sort.cpp.i

CMakeFiles/list_test.dir/list_struct_sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/list_test.dir/list_struct_sort.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniel/Desktop/astar_self/list_test/list_struct_sort.cpp -o CMakeFiles/list_test.dir/list_struct_sort.cpp.s

CMakeFiles/list_test.dir/list_struct_sort.cpp.o.requires:

.PHONY : CMakeFiles/list_test.dir/list_struct_sort.cpp.o.requires

CMakeFiles/list_test.dir/list_struct_sort.cpp.o.provides: CMakeFiles/list_test.dir/list_struct_sort.cpp.o.requires
	$(MAKE) -f CMakeFiles/list_test.dir/build.make CMakeFiles/list_test.dir/list_struct_sort.cpp.o.provides.build
.PHONY : CMakeFiles/list_test.dir/list_struct_sort.cpp.o.provides

CMakeFiles/list_test.dir/list_struct_sort.cpp.o.provides.build: CMakeFiles/list_test.dir/list_struct_sort.cpp.o


# Object files for target list_test
list_test_OBJECTS = \
"CMakeFiles/list_test.dir/list_struct_sort.cpp.o"

# External object files for target list_test
list_test_EXTERNAL_OBJECTS =

list_test: CMakeFiles/list_test.dir/list_struct_sort.cpp.o
list_test: CMakeFiles/list_test.dir/build.make
list_test: CMakeFiles/list_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniel/Desktop/astar_self/list_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable list_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/list_test.dir/build: list_test

.PHONY : CMakeFiles/list_test.dir/build

CMakeFiles/list_test.dir/requires: CMakeFiles/list_test.dir/list_struct_sort.cpp.o.requires

.PHONY : CMakeFiles/list_test.dir/requires

CMakeFiles/list_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/list_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/list_test.dir/clean

CMakeFiles/list_test.dir/depend:
	cd /home/daniel/Desktop/astar_self/list_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/Desktop/astar_self/list_test /home/daniel/Desktop/astar_self/list_test /home/daniel/Desktop/astar_self/list_test/build /home/daniel/Desktop/astar_self/list_test/build /home/daniel/Desktop/astar_self/list_test/build/CMakeFiles/list_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/list_test.dir/depend
