# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /pvfsmnt/118010224/parallel_version_extend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /pvfsmnt/118010224/parallel_version_extend/build

# Include any dependencies generated for this target.
include CMakeFiles/odd-even-sort.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/odd-even-sort.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/odd-even-sort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/odd-even-sort.dir/flags.make

CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o: CMakeFiles/odd-even-sort.dir/flags.make
CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o: ../src/odd-even-sort.cpp
CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o: CMakeFiles/odd-even-sort.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/pvfsmnt/118010224/parallel_version_extend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o"
	/usr/local/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o -MF CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o.d -o CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o -c /pvfsmnt/118010224/parallel_version_extend/src/odd-even-sort.cpp

CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.i"
	/usr/local/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /pvfsmnt/118010224/parallel_version_extend/src/odd-even-sort.cpp > CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.i

CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.s"
	/usr/local/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /pvfsmnt/118010224/parallel_version_extend/src/odd-even-sort.cpp -o CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.s

# Object files for target odd-even-sort
odd__even__sort_OBJECTS = \
"CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o"

# External object files for target odd-even-sort
odd__even__sort_EXTERNAL_OBJECTS =

libodd-even-sort.so: CMakeFiles/odd-even-sort.dir/src/odd-even-sort.cpp.o
libodd-even-sort.so: CMakeFiles/odd-even-sort.dir/build.make
libodd-even-sort.so: /usr/local/lib/libmpi.so
libodd-even-sort.so: CMakeFiles/odd-even-sort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/pvfsmnt/118010224/parallel_version_extend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libodd-even-sort.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/odd-even-sort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/odd-even-sort.dir/build: libodd-even-sort.so
.PHONY : CMakeFiles/odd-even-sort.dir/build

CMakeFiles/odd-even-sort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/odd-even-sort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/odd-even-sort.dir/clean

CMakeFiles/odd-even-sort.dir/depend:
	cd /pvfsmnt/118010224/parallel_version_extend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /pvfsmnt/118010224/parallel_version_extend /pvfsmnt/118010224/parallel_version_extend /pvfsmnt/118010224/parallel_version_extend/build /pvfsmnt/118010224/parallel_version_extend/build /pvfsmnt/118010224/parallel_version_extend/build/CMakeFiles/odd-even-sort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/odd-even-sort.dir/depend

