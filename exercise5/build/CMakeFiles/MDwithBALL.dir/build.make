# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/bip15/bioinformatik/exercise5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bip15/bioinformatik/exercise5/build

# Include any dependencies generated for this target.
include CMakeFiles/MDwithBALL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MDwithBALL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MDwithBALL.dir/flags.make

CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o: CMakeFiles/MDwithBALL.dir/flags.make
CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o: ../molecularDynamics.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bip15/bioinformatik/exercise5/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o -c /home/bip15/bioinformatik/exercise5/molecularDynamics.cpp

CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bip15/bioinformatik/exercise5/molecularDynamics.cpp > CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.i

CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bip15/bioinformatik/exercise5/molecularDynamics.cpp -o CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.s

CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.requires:
.PHONY : CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.requires

CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.provides: CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.requires
	$(MAKE) -f CMakeFiles/MDwithBALL.dir/build.make CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.provides.build
.PHONY : CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.provides

CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.provides.build: CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o

# Object files for target MDwithBALL
MDwithBALL_OBJECTS = \
"CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o"

# External object files for target MDwithBALL
MDwithBALL_EXTERNAL_OBJECTS =

MDwithBALL: CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o
MDwithBALL: CMakeFiles/MDwithBALL.dir/build.make
MDwithBALL: ~/git/ball/build/lib/libBALL.so
MDwithBALL: CMakeFiles/MDwithBALL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable MDwithBALL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MDwithBALL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MDwithBALL.dir/build: MDwithBALL
.PHONY : CMakeFiles/MDwithBALL.dir/build

CMakeFiles/MDwithBALL.dir/requires: CMakeFiles/MDwithBALL.dir/molecularDynamics.cpp.o.requires
.PHONY : CMakeFiles/MDwithBALL.dir/requires

CMakeFiles/MDwithBALL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MDwithBALL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MDwithBALL.dir/clean

CMakeFiles/MDwithBALL.dir/depend:
	cd /home/bip15/bioinformatik/exercise5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bip15/bioinformatik/exercise5 /home/bip15/bioinformatik/exercise5 /home/bip15/bioinformatik/exercise5/build /home/bip15/bioinformatik/exercise5/build /home/bip15/bioinformatik/exercise5/build/CMakeFiles/MDwithBALL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MDwithBALL.dir/depend

