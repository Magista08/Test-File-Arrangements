# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /opt/cmake-3.17.2/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.17.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TestFilesArrangement.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestFilesArrangement.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestFilesArrangement.dir/flags.make

CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.o: CMakeFiles/TestFilesArrangement.dir/flags.make
CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.o: ../TestFilesArrangement.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.o   -c /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/TestFilesArrangement.c

CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/TestFilesArrangement.c > CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.i

CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/TestFilesArrangement.c -o CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.s

# Object files for target TestFilesArrangement
TestFilesArrangement_OBJECTS = \
"CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.o"

# External object files for target TestFilesArrangement
TestFilesArrangement_EXTERNAL_OBJECTS =

TestFilesArrangement: CMakeFiles/TestFilesArrangement.dir/TestFilesArrangement.c.o
TestFilesArrangement: CMakeFiles/TestFilesArrangement.dir/build.make
TestFilesArrangement: CMakeFiles/TestFilesArrangement.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TestFilesArrangement"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestFilesArrangement.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestFilesArrangement.dir/build: TestFilesArrangement

.PHONY : CMakeFiles/TestFilesArrangement.dir/build

CMakeFiles/TestFilesArrangement.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestFilesArrangement.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestFilesArrangement.dir/clean

CMakeFiles/TestFilesArrangement.dir/depend:
	cd /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug /mnt/e/Internship_ShanghaiElectric/TestFilesArrangement/cmake-build-debug/CMakeFiles/TestFilesArrangement.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestFilesArrangement.dir/depend

