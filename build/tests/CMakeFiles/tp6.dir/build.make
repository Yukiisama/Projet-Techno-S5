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
CMAKE_BINARY_DIR = /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/tp6.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/tp6.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/tp6.dir/flags.make

tests/CMakeFiles/tp6.dir/tp6.cpp.o: tests/CMakeFiles/tp6.dir/flags.make
tests/CMakeFiles/tp6.dir/tp6.cpp.o: ../tests/tp6.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/tp6.dir/tp6.cpp.o"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tp6.dir/tp6.cpp.o -c /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/tp6.cpp

tests/CMakeFiles/tp6.dir/tp6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp6.dir/tp6.cpp.i"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/tp6.cpp > CMakeFiles/tp6.dir/tp6.cpp.i

tests/CMakeFiles/tp6.dir/tp6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp6.dir/tp6.cpp.s"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/tp6.cpp -o CMakeFiles/tp6.dir/tp6.cpp.s

tests/CMakeFiles/tp6.dir/tp6.cpp.o.requires:

.PHONY : tests/CMakeFiles/tp6.dir/tp6.cpp.o.requires

tests/CMakeFiles/tp6.dir/tp6.cpp.o.provides: tests/CMakeFiles/tp6.dir/tp6.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/tp6.dir/build.make tests/CMakeFiles/tp6.dir/tp6.cpp.o.provides.build
.PHONY : tests/CMakeFiles/tp6.dir/tp6.cpp.o.provides

tests/CMakeFiles/tp6.dir/tp6.cpp.o.provides.build: tests/CMakeFiles/tp6.dir/tp6.cpp.o


tests/CMakeFiles/tp6.dir/viewer.cpp.o: tests/CMakeFiles/tp6.dir/flags.make
tests/CMakeFiles/tp6.dir/viewer.cpp.o: ../tests/viewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/tp6.dir/viewer.cpp.o"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tp6.dir/viewer.cpp.o -c /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/viewer.cpp

tests/CMakeFiles/tp6.dir/viewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp6.dir/viewer.cpp.i"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/viewer.cpp > CMakeFiles/tp6.dir/viewer.cpp.i

tests/CMakeFiles/tp6.dir/viewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp6.dir/viewer.cpp.s"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/viewer.cpp -o CMakeFiles/tp6.dir/viewer.cpp.s

tests/CMakeFiles/tp6.dir/viewer.cpp.o.requires:

.PHONY : tests/CMakeFiles/tp6.dir/viewer.cpp.o.requires

tests/CMakeFiles/tp6.dir/viewer.cpp.o.provides: tests/CMakeFiles/tp6.dir/viewer.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/tp6.dir/build.make tests/CMakeFiles/tp6.dir/viewer.cpp.o.provides.build
.PHONY : tests/CMakeFiles/tp6.dir/viewer.cpp.o.provides

tests/CMakeFiles/tp6.dir/viewer.cpp.o.provides.build: tests/CMakeFiles/tp6.dir/viewer.cpp.o


tests/CMakeFiles/tp6.dir/Rectangle.cpp.o: tests/CMakeFiles/tp6.dir/flags.make
tests/CMakeFiles/tp6.dir/Rectangle.cpp.o: ../tests/Rectangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/tp6.dir/Rectangle.cpp.o"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tp6.dir/Rectangle.cpp.o -c /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/Rectangle.cpp

tests/CMakeFiles/tp6.dir/Rectangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp6.dir/Rectangle.cpp.i"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/Rectangle.cpp > CMakeFiles/tp6.dir/Rectangle.cpp.i

tests/CMakeFiles/tp6.dir/Rectangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp6.dir/Rectangle.cpp.s"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests/Rectangle.cpp -o CMakeFiles/tp6.dir/Rectangle.cpp.s

tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.requires:

.PHONY : tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.requires

tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.provides: tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.requires
	$(MAKE) -f tests/CMakeFiles/tp6.dir/build.make tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.provides.build
.PHONY : tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.provides

tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.provides.build: tests/CMakeFiles/tp6.dir/Rectangle.cpp.o


# Object files for target tp6
tp6_OBJECTS = \
"CMakeFiles/tp6.dir/tp6.cpp.o" \
"CMakeFiles/tp6.dir/viewer.cpp.o" \
"CMakeFiles/tp6.dir/Rectangle.cpp.o"

# External object files for target tp6
tp6_EXTERNAL_OBJECTS =

tests/tp6: tests/CMakeFiles/tp6.dir/tp6.cpp.o
tests/tp6: tests/CMakeFiles/tp6.dir/viewer.cpp.o
tests/tp6: tests/CMakeFiles/tp6.dir/Rectangle.cpp.o
tests/tp6: tests/CMakeFiles/tp6.dir/build.make
tests/tp6: libei.a
tests/tp6: tests/CMakeFiles/tp6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tp6"
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/tp6.dir/build: tests/tp6

.PHONY : tests/CMakeFiles/tp6.dir/build

tests/CMakeFiles/tp6.dir/requires: tests/CMakeFiles/tp6.dir/tp6.cpp.o.requires
tests/CMakeFiles/tp6.dir/requires: tests/CMakeFiles/tp6.dir/viewer.cpp.o.requires
tests/CMakeFiles/tp6.dir/requires: tests/CMakeFiles/tp6.dir/Rectangle.cpp.o.requires

.PHONY : tests/CMakeFiles/tp6.dir/requires

tests/CMakeFiles/tp6.dir/clean:
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/tp6.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/tp6.dir/clean

tests/CMakeFiles/tp6.dir/depend:
	cd /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/tests /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests /net/cremi/aperigno/PROJET_TECHNO_L3/ptl3iug/build/tests/CMakeFiles/tp6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/tp6.dir/depend

