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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug

# Include any dependencies generated for this target.
include tests/CMakeFiles/tp2.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/tp2.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/tp2.dir/flags.make

tests/CMakeFiles/tp2.dir/tp2.c.o: tests/CMakeFiles/tp2.dir/flags.make
tests/CMakeFiles/tp2.dir/tp2.c.o: tests/tp2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/tp2.dir/tp2.c.o"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tp2.dir/tp2.c.o   -c /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/tp2.c

tests/CMakeFiles/tp2.dir/tp2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp2.dir/tp2.c.i"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/tp2.c > CMakeFiles/tp2.dir/tp2.c.i

tests/CMakeFiles/tp2.dir/tp2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp2.dir/tp2.c.s"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/tp2.c -o CMakeFiles/tp2.dir/tp2.c.s

tests/CMakeFiles/tp2.dir/tp2.c.o.requires:

.PHONY : tests/CMakeFiles/tp2.dir/tp2.c.o.requires

tests/CMakeFiles/tp2.dir/tp2.c.o.provides: tests/CMakeFiles/tp2.dir/tp2.c.o.requires
	$(MAKE) -f tests/CMakeFiles/tp2.dir/build.make tests/CMakeFiles/tp2.dir/tp2.c.o.provides.build
.PHONY : tests/CMakeFiles/tp2.dir/tp2.c.o.provides

tests/CMakeFiles/tp2.dir/tp2.c.o.provides.build: tests/CMakeFiles/tp2.dir/tp2.c.o


# Object files for target tp2
tp2_OBJECTS = \
"CMakeFiles/tp2.dir/tp2.c.o"

# External object files for target tp2
tp2_EXTERNAL_OBJECTS =

tests/tp2: tests/CMakeFiles/tp2.dir/tp2.c.o
tests/tp2: tests/CMakeFiles/tp2.dir/build.make
tests/tp2: tests/libdraw.a
tests/tp2: tests/CMakeFiles/tp2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable tp2"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/tp2.dir/build: tests/tp2

.PHONY : tests/CMakeFiles/tp2.dir/build

tests/CMakeFiles/tp2.dir/requires: tests/CMakeFiles/tp2.dir/tp2.c.o.requires

.PHONY : tests/CMakeFiles/tp2.dir/requires

tests/CMakeFiles/tp2.dir/clean:
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests && $(CMAKE_COMMAND) -P CMakeFiles/tp2.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/tp2.dir/clean

tests/CMakeFiles/tp2.dir/depend:
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/CMakeFiles/tp2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/tp2.dir/depend

