# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/smher/Documents/Linux_setup_files/clion-2017.1.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/smher/Documents/Linux_setup_files/clion-2017.1.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/smher/myCode/SLAMs/chapter13/DenseMapSingle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DenseMapSingle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DenseMapSingle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DenseMapSingle.dir/flags.make

CMakeFiles/DenseMapSingle.dir/main.cpp.o: CMakeFiles/DenseMapSingle.dir/flags.make
CMakeFiles/DenseMapSingle.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DenseMapSingle.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DenseMapSingle.dir/main.cpp.o -c /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/main.cpp

CMakeFiles/DenseMapSingle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DenseMapSingle.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/main.cpp > CMakeFiles/DenseMapSingle.dir/main.cpp.i

CMakeFiles/DenseMapSingle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DenseMapSingle.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/main.cpp -o CMakeFiles/DenseMapSingle.dir/main.cpp.s

CMakeFiles/DenseMapSingle.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/DenseMapSingle.dir/main.cpp.o.requires

CMakeFiles/DenseMapSingle.dir/main.cpp.o.provides: CMakeFiles/DenseMapSingle.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/DenseMapSingle.dir/build.make CMakeFiles/DenseMapSingle.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/DenseMapSingle.dir/main.cpp.o.provides

CMakeFiles/DenseMapSingle.dir/main.cpp.o.provides.build: CMakeFiles/DenseMapSingle.dir/main.cpp.o


# Object files for target DenseMapSingle
DenseMapSingle_OBJECTS = \
"CMakeFiles/DenseMapSingle.dir/main.cpp.o"

# External object files for target DenseMapSingle
DenseMapSingle_EXTERNAL_OBJECTS =

DenseMapSingle: CMakeFiles/DenseMapSingle.dir/main.cpp.o
DenseMapSingle: CMakeFiles/DenseMapSingle.dir/build.make
DenseMapSingle: CMakeFiles/DenseMapSingle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DenseMapSingle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DenseMapSingle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DenseMapSingle.dir/build: DenseMapSingle

.PHONY : CMakeFiles/DenseMapSingle.dir/build

CMakeFiles/DenseMapSingle.dir/requires: CMakeFiles/DenseMapSingle.dir/main.cpp.o.requires

.PHONY : CMakeFiles/DenseMapSingle.dir/requires

CMakeFiles/DenseMapSingle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DenseMapSingle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DenseMapSingle.dir/clean

CMakeFiles/DenseMapSingle.dir/depend:
	cd /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/smher/myCode/SLAMs/chapter13/DenseMapSingle /home/smher/myCode/SLAMs/chapter13/DenseMapSingle /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug /home/smher/myCode/SLAMs/chapter13/DenseMapSingle/cmake-build-debug/CMakeFiles/DenseMapSingle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DenseMapSingle.dir/depend

