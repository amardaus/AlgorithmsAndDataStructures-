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
CMAKE_SOURCE_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/yourProj.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/yourProj.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yourProj.dir/flags.make

CMakeFiles/yourProj.dir/PriorityQueue.cpp.o: CMakeFiles/yourProj.dir/flags.make
CMakeFiles/yourProj.dir/PriorityQueue.cpp.o: ../PriorityQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yourProj.dir/PriorityQueue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yourProj.dir/PriorityQueue.cpp.o -c /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/PriorityQueue.cpp

CMakeFiles/yourProj.dir/PriorityQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yourProj.dir/PriorityQueue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/PriorityQueue.cpp > CMakeFiles/yourProj.dir/PriorityQueue.cpp.i

CMakeFiles/yourProj.dir/PriorityQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yourProj.dir/PriorityQueue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/PriorityQueue.cpp -o CMakeFiles/yourProj.dir/PriorityQueue.cpp.s

# Object files for target yourProj
yourProj_OBJECTS = \
"CMakeFiles/yourProj.dir/PriorityQueue.cpp.o"

# External object files for target yourProj
yourProj_EXTERNAL_OBJECTS =

yourProj: CMakeFiles/yourProj.dir/PriorityQueue.cpp.o
yourProj: CMakeFiles/yourProj.dir/build.make
yourProj: CMakeFiles/yourProj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable yourProj"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yourProj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yourProj.dir/build: yourProj

.PHONY : CMakeFiles/yourProj.dir/build

CMakeFiles/yourProj.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yourProj.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yourProj.dir/clean

CMakeFiles/yourProj.dir/depend:
	cd /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/08_Dijkstra/cmake-build-debug/CMakeFiles/yourProj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yourProj.dir/depend

