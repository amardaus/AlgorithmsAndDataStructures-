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
CMAKE_SOURCE_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Count_SCC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Count_SCC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Count_SCC.dir/flags.make

CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.o: CMakeFiles/Count_SCC.dir/flags.make
CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.o: ../countStronglyConnectedComponents.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.o -c /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/countStronglyConnectedComponents.cpp

CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/countStronglyConnectedComponents.cpp > CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.i

CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/countStronglyConnectedComponents.cpp -o CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.s

# Object files for target Count_SCC
Count_SCC_OBJECTS = \
"CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.o"

# External object files for target Count_SCC
Count_SCC_EXTERNAL_OBJECTS =

Count_SCC: CMakeFiles/Count_SCC.dir/countStronglyConnectedComponents.cpp.o
Count_SCC: CMakeFiles/Count_SCC.dir/build.make
Count_SCC: CMakeFiles/Count_SCC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Count_SCC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Count_SCC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Count_SCC.dir/build: Count_SCC

.PHONY : CMakeFiles/Count_SCC.dir/build

CMakeFiles/Count_SCC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Count_SCC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Count_SCC.dir/clean

CMakeFiles/Count_SCC.dir/depend:
	cd /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/06_Graph_Strongly_Connected_Components/cmake-build-debug/CMakeFiles/Count_SCC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Count_SCC.dir/depend

