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
CMAKE_SOURCE_DIR = /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug

# Include any dependencies generated for this target.
include CMakeFiles/sudoku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sudoku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sudoku.dir/flags.make

CMakeFiles/sudoku.dir/sudoku.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/sudoku.cpp.o: ../sudoku.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sudoku.dir/sudoku.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/sudoku.cpp.o -c /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku.cpp

CMakeFiles/sudoku.dir/sudoku.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/sudoku.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku.cpp > CMakeFiles/sudoku.dir/sudoku.cpp.i

CMakeFiles/sudoku.dir/sudoku.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/sudoku.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku.cpp -o CMakeFiles/sudoku.dir/sudoku.cpp.s

CMakeFiles/sudoku.dir/sudoku.cpp.o.requires:

.PHONY : CMakeFiles/sudoku.dir/sudoku.cpp.o.requires

CMakeFiles/sudoku.dir/sudoku.cpp.o.provides: CMakeFiles/sudoku.dir/sudoku.cpp.o.requires
	$(MAKE) -f CMakeFiles/sudoku.dir/build.make CMakeFiles/sudoku.dir/sudoku.cpp.o.provides.build
.PHONY : CMakeFiles/sudoku.dir/sudoku.cpp.o.provides

CMakeFiles/sudoku.dir/sudoku.cpp.o.provides.build: CMakeFiles/sudoku.dir/sudoku.cpp.o


CMakeFiles/sudoku.dir/sudoku4.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/sudoku4.cpp.o: ../sudoku4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sudoku.dir/sudoku4.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/sudoku4.cpp.o -c /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku4.cpp

CMakeFiles/sudoku.dir/sudoku4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/sudoku4.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku4.cpp > CMakeFiles/sudoku.dir/sudoku4.cpp.i

CMakeFiles/sudoku.dir/sudoku4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/sudoku4.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku4.cpp -o CMakeFiles/sudoku.dir/sudoku4.cpp.s

CMakeFiles/sudoku.dir/sudoku4.cpp.o.requires:

.PHONY : CMakeFiles/sudoku.dir/sudoku4.cpp.o.requires

CMakeFiles/sudoku.dir/sudoku4.cpp.o.provides: CMakeFiles/sudoku.dir/sudoku4.cpp.o.requires
	$(MAKE) -f CMakeFiles/sudoku.dir/build.make CMakeFiles/sudoku.dir/sudoku4.cpp.o.provides.build
.PHONY : CMakeFiles/sudoku.dir/sudoku4.cpp.o.provides

CMakeFiles/sudoku.dir/sudoku4.cpp.o.provides.build: CMakeFiles/sudoku.dir/sudoku4.cpp.o


CMakeFiles/sudoku.dir/generate.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/generate.cpp.o: ../generate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sudoku.dir/generate.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/generate.cpp.o -c /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/generate.cpp

CMakeFiles/sudoku.dir/generate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/generate.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/generate.cpp > CMakeFiles/sudoku.dir/generate.cpp.i

CMakeFiles/sudoku.dir/generate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/generate.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/generate.cpp -o CMakeFiles/sudoku.dir/generate.cpp.s

CMakeFiles/sudoku.dir/generate.cpp.o.requires:

.PHONY : CMakeFiles/sudoku.dir/generate.cpp.o.requires

CMakeFiles/sudoku.dir/generate.cpp.o.provides: CMakeFiles/sudoku.dir/generate.cpp.o.requires
	$(MAKE) -f CMakeFiles/sudoku.dir/build.make CMakeFiles/sudoku.dir/generate.cpp.o.provides.build
.PHONY : CMakeFiles/sudoku.dir/generate.cpp.o.provides

CMakeFiles/sudoku.dir/generate.cpp.o.provides.build: CMakeFiles/sudoku.dir/generate.cpp.o


CMakeFiles/sudoku.dir/sudoku9.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/sudoku9.cpp.o: ../sudoku9.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sudoku.dir/sudoku9.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/sudoku9.cpp.o -c /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku9.cpp

CMakeFiles/sudoku.dir/sudoku9.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/sudoku9.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku9.cpp > CMakeFiles/sudoku.dir/sudoku9.cpp.i

CMakeFiles/sudoku.dir/sudoku9.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/sudoku9.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku9.cpp -o CMakeFiles/sudoku.dir/sudoku9.cpp.s

CMakeFiles/sudoku.dir/sudoku9.cpp.o.requires:

.PHONY : CMakeFiles/sudoku.dir/sudoku9.cpp.o.requires

CMakeFiles/sudoku.dir/sudoku9.cpp.o.provides: CMakeFiles/sudoku.dir/sudoku9.cpp.o.requires
	$(MAKE) -f CMakeFiles/sudoku.dir/build.make CMakeFiles/sudoku.dir/sudoku9.cpp.o.provides.build
.PHONY : CMakeFiles/sudoku.dir/sudoku9.cpp.o.provides

CMakeFiles/sudoku.dir/sudoku9.cpp.o.provides.build: CMakeFiles/sudoku.dir/sudoku9.cpp.o


CMakeFiles/sudoku.dir/sudoku9_util.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/sudoku9_util.cpp.o: ../sudoku9_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sudoku.dir/sudoku9_util.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/sudoku9_util.cpp.o -c /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku9_util.cpp

CMakeFiles/sudoku.dir/sudoku9_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/sudoku9_util.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku9_util.cpp > CMakeFiles/sudoku.dir/sudoku9_util.cpp.i

CMakeFiles/sudoku.dir/sudoku9_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/sudoku9_util.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/sudoku9_util.cpp -o CMakeFiles/sudoku.dir/sudoku9_util.cpp.s

CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.requires:

.PHONY : CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.requires

CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.provides: CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.requires
	$(MAKE) -f CMakeFiles/sudoku.dir/build.make CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.provides.build
.PHONY : CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.provides

CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.provides.build: CMakeFiles/sudoku.dir/sudoku9_util.cpp.o


CMakeFiles/sudoku.dir/globals.cpp.o: CMakeFiles/sudoku.dir/flags.make
CMakeFiles/sudoku.dir/globals.cpp.o: ../globals.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sudoku.dir/globals.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sudoku.dir/globals.cpp.o -c /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/globals.cpp

CMakeFiles/sudoku.dir/globals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sudoku.dir/globals.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/globals.cpp > CMakeFiles/sudoku.dir/globals.cpp.i

CMakeFiles/sudoku.dir/globals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sudoku.dir/globals.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/globals.cpp -o CMakeFiles/sudoku.dir/globals.cpp.s

CMakeFiles/sudoku.dir/globals.cpp.o.requires:

.PHONY : CMakeFiles/sudoku.dir/globals.cpp.o.requires

CMakeFiles/sudoku.dir/globals.cpp.o.provides: CMakeFiles/sudoku.dir/globals.cpp.o.requires
	$(MAKE) -f CMakeFiles/sudoku.dir/build.make CMakeFiles/sudoku.dir/globals.cpp.o.provides.build
.PHONY : CMakeFiles/sudoku.dir/globals.cpp.o.provides

CMakeFiles/sudoku.dir/globals.cpp.o.provides.build: CMakeFiles/sudoku.dir/globals.cpp.o


# Object files for target sudoku
sudoku_OBJECTS = \
"CMakeFiles/sudoku.dir/sudoku.cpp.o" \
"CMakeFiles/sudoku.dir/sudoku4.cpp.o" \
"CMakeFiles/sudoku.dir/generate.cpp.o" \
"CMakeFiles/sudoku.dir/sudoku9.cpp.o" \
"CMakeFiles/sudoku.dir/sudoku9_util.cpp.o" \
"CMakeFiles/sudoku.dir/globals.cpp.o"

# External object files for target sudoku
sudoku_EXTERNAL_OBJECTS =

sudoku: CMakeFiles/sudoku.dir/sudoku.cpp.o
sudoku: CMakeFiles/sudoku.dir/sudoku4.cpp.o
sudoku: CMakeFiles/sudoku.dir/generate.cpp.o
sudoku: CMakeFiles/sudoku.dir/sudoku9.cpp.o
sudoku: CMakeFiles/sudoku.dir/sudoku9_util.cpp.o
sudoku: CMakeFiles/sudoku.dir/globals.cpp.o
sudoku: CMakeFiles/sudoku.dir/build.make
sudoku: CMakeFiles/sudoku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable sudoku"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sudoku.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sudoku.dir/build: sudoku

.PHONY : CMakeFiles/sudoku.dir/build

CMakeFiles/sudoku.dir/requires: CMakeFiles/sudoku.dir/sudoku.cpp.o.requires
CMakeFiles/sudoku.dir/requires: CMakeFiles/sudoku.dir/sudoku4.cpp.o.requires
CMakeFiles/sudoku.dir/requires: CMakeFiles/sudoku.dir/generate.cpp.o.requires
CMakeFiles/sudoku.dir/requires: CMakeFiles/sudoku.dir/sudoku9.cpp.o.requires
CMakeFiles/sudoku.dir/requires: CMakeFiles/sudoku.dir/sudoku9_util.cpp.o.requires
CMakeFiles/sudoku.dir/requires: CMakeFiles/sudoku.dir/globals.cpp.o.requires

.PHONY : CMakeFiles/sudoku.dir/requires

CMakeFiles/sudoku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sudoku.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sudoku.dir/clean

CMakeFiles/sudoku.dir/depend:
	cd /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug /home/heimlaszlo/Projektek/UniProjekt/sem04/mestint/lab02-sudoku/Debug/CMakeFiles/sudoku.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sudoku.dir/depend

