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
include CMakeFiles/Set_10mln.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Set_10mln.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Set_10mln.dir/flags.make

CMakeFiles/Set_10mln.dir/Set_10mln.cpp.o: CMakeFiles/Set_10mln.dir/flags.make
CMakeFiles/Set_10mln.dir/Set_10mln.cpp.o: ../Set_10mln.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Set_10mln.dir/Set_10mln.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Set_10mln.dir/Set_10mln.cpp.o -c /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/Set_10mln.cpp

CMakeFiles/Set_10mln.dir/Set_10mln.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Set_10mln.dir/Set_10mln.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/Set_10mln.cpp > CMakeFiles/Set_10mln.dir/Set_10mln.cpp.i

CMakeFiles/Set_10mln.dir/Set_10mln.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Set_10mln.dir/Set_10mln.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/Set_10mln.cpp -o CMakeFiles/Set_10mln.dir/Set_10mln.cpp.s

# Object files for target Set_10mln
Set_10mln_OBJECTS = \
"CMakeFiles/Set_10mln.dir/Set_10mln.cpp.o"

# External object files for target Set_10mln
Set_10mln_EXTERNAL_OBJECTS =

Set_10mln: CMakeFiles/Set_10mln.dir/Set_10mln.cpp.o
Set_10mln: CMakeFiles/Set_10mln.dir/build.make
Set_10mln: CMakeFiles/Set_10mln.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Set_10mln"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Set_10mln.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Set_10mln.dir/build: Set_10mln

.PHONY : CMakeFiles/Set_10mln.dir/build

CMakeFiles/Set_10mln.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Set_10mln.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Set_10mln.dir/clean

CMakeFiles/Set_10mln.dir/depend:
	cd /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/01_Set_implementation/cmake-build-debug/CMakeFiles/Set_10mln.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Set_10mln.dir/depend

