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
CMAKE_SOURCE_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Basic_version.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Basic_version.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Basic_version.dir/flags.make

CMakeFiles/Basic_version.dir/main_v1.cpp.o: CMakeFiles/Basic_version.dir/flags.make
CMakeFiles/Basic_version.dir/main_v1.cpp.o: ../main_v1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Basic_version.dir/main_v1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Basic_version.dir/main_v1.cpp.o -c /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/main_v1.cpp

CMakeFiles/Basic_version.dir/main_v1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Basic_version.dir/main_v1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/main_v1.cpp > CMakeFiles/Basic_version.dir/main_v1.cpp.i

CMakeFiles/Basic_version.dir/main_v1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Basic_version.dir/main_v1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/main_v1.cpp -o CMakeFiles/Basic_version.dir/main_v1.cpp.s

# Object files for target Basic_version
Basic_version_OBJECTS = \
"CMakeFiles/Basic_version.dir/main_v1.cpp.o"

# External object files for target Basic_version
Basic_version_EXTERNAL_OBJECTS =

Basic_version: CMakeFiles/Basic_version.dir/main_v1.cpp.o
Basic_version: CMakeFiles/Basic_version.dir/build.make
Basic_version: CMakeFiles/Basic_version.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Basic_version"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Basic_version.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Basic_version.dir/build: Basic_version

.PHONY : CMakeFiles/Basic_version.dir/build

CMakeFiles/Basic_version.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Basic_version.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Basic_version.dir/clean

CMakeFiles/Basic_version.dir/depend:
	cd /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug /home/olcia/Documents/2_AlgorytmyiStrukturyDanych/13_Clustering/cmake-build-debug/CMakeFiles/Basic_version.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Basic_version.dir/depend
