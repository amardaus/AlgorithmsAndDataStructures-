# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/olcia/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/olcia/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Tree-based_Set.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tree-based_Set.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tree-based_Set.dir/flags.make

CMakeFiles/Tree-based_Set.dir/main.cpp.o: CMakeFiles/Tree-based_Set.dir/flags.make
CMakeFiles/Tree-based_Set.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tree-based_Set.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tree-based_Set.dir/main.cpp.o -c /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/main.cpp

CMakeFiles/Tree-based_Set.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tree-based_Set.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/main.cpp > CMakeFiles/Tree-based_Set.dir/main.cpp.i

CMakeFiles/Tree-based_Set.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tree-based_Set.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/main.cpp -o CMakeFiles/Tree-based_Set.dir/main.cpp.s

# Object files for target Tree-based_Set
Tree__based_Set_OBJECTS = \
"CMakeFiles/Tree-based_Set.dir/main.cpp.o"

# External object files for target Tree-based_Set
Tree__based_Set_EXTERNAL_OBJECTS =

Tree-based_Set: CMakeFiles/Tree-based_Set.dir/main.cpp.o
Tree-based_Set: CMakeFiles/Tree-based_Set.dir/build.make
Tree-based_Set: CMakeFiles/Tree-based_Set.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tree-based_Set"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tree-based_Set.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tree-based_Set.dir/build: Tree-based_Set

.PHONY : CMakeFiles/Tree-based_Set.dir/build

CMakeFiles/Tree-based_Set.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tree-based_Set.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tree-based_Set.dir/clean

CMakeFiles/Tree-based_Set.dir/depend:
	cd /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug/CMakeFiles/Tree-based_Set.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tree-based_Set.dir/depend

