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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yy/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yy/test/build

# Include any dependencies generated for this target.
include frame/CMakeFiles/frame.dir/depend.make

# Include the progress variables for this target.
include frame/CMakeFiles/frame.dir/progress.make

# Include the compile flags for this target's objects.
include frame/CMakeFiles/frame.dir/flags.make

frame/CMakeFiles/frame.dir/source/sche_oper_base.o: frame/CMakeFiles/frame.dir/flags.make
frame/CMakeFiles/frame.dir/source/sche_oper_base.o: ../frame/source/sche_oper_base.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yy/test/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object frame/CMakeFiles/frame.dir/source/sche_oper_base.o"
	cd /home/yy/test/build/frame && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/frame.dir/source/sche_oper_base.o -c /home/yy/test/frame/source/sche_oper_base.cpp

frame/CMakeFiles/frame.dir/source/sche_oper_base.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame.dir/source/sche_oper_base.i"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yy/test/frame/source/sche_oper_base.cpp > CMakeFiles/frame.dir/source/sche_oper_base.i

frame/CMakeFiles/frame.dir/source/sche_oper_base.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame.dir/source/sche_oper_base.s"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yy/test/frame/source/sche_oper_base.cpp -o CMakeFiles/frame.dir/source/sche_oper_base.s

frame/CMakeFiles/frame.dir/source/sche_oper_base.o.requires:
.PHONY : frame/CMakeFiles/frame.dir/source/sche_oper_base.o.requires

frame/CMakeFiles/frame.dir/source/sche_oper_base.o.provides: frame/CMakeFiles/frame.dir/source/sche_oper_base.o.requires
	$(MAKE) -f frame/CMakeFiles/frame.dir/build.make frame/CMakeFiles/frame.dir/source/sche_oper_base.o.provides.build
.PHONY : frame/CMakeFiles/frame.dir/source/sche_oper_base.o.provides

frame/CMakeFiles/frame.dir/source/sche_oper_base.o.provides.build: frame/CMakeFiles/frame.dir/source/sche_oper_base.o

frame/CMakeFiles/frame.dir/source/start.o: frame/CMakeFiles/frame.dir/flags.make
frame/CMakeFiles/frame.dir/source/start.o: ../frame/source/start.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yy/test/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object frame/CMakeFiles/frame.dir/source/start.o"
	cd /home/yy/test/build/frame && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/frame.dir/source/start.o -c /home/yy/test/frame/source/start.cpp

frame/CMakeFiles/frame.dir/source/start.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame.dir/source/start.i"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yy/test/frame/source/start.cpp > CMakeFiles/frame.dir/source/start.i

frame/CMakeFiles/frame.dir/source/start.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame.dir/source/start.s"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yy/test/frame/source/start.cpp -o CMakeFiles/frame.dir/source/start.s

frame/CMakeFiles/frame.dir/source/start.o.requires:
.PHONY : frame/CMakeFiles/frame.dir/source/start.o.requires

frame/CMakeFiles/frame.dir/source/start.o.provides: frame/CMakeFiles/frame.dir/source/start.o.requires
	$(MAKE) -f frame/CMakeFiles/frame.dir/build.make frame/CMakeFiles/frame.dir/source/start.o.provides.build
.PHONY : frame/CMakeFiles/frame.dir/source/start.o.provides

frame/CMakeFiles/frame.dir/source/start.o.provides.build: frame/CMakeFiles/frame.dir/source/start.o

frame/CMakeFiles/frame.dir/source/udpserver.o: frame/CMakeFiles/frame.dir/flags.make
frame/CMakeFiles/frame.dir/source/udpserver.o: ../frame/source/udpserver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yy/test/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object frame/CMakeFiles/frame.dir/source/udpserver.o"
	cd /home/yy/test/build/frame && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/frame.dir/source/udpserver.o -c /home/yy/test/frame/source/udpserver.cpp

frame/CMakeFiles/frame.dir/source/udpserver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame.dir/source/udpserver.i"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yy/test/frame/source/udpserver.cpp > CMakeFiles/frame.dir/source/udpserver.i

frame/CMakeFiles/frame.dir/source/udpserver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame.dir/source/udpserver.s"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yy/test/frame/source/udpserver.cpp -o CMakeFiles/frame.dir/source/udpserver.s

frame/CMakeFiles/frame.dir/source/udpserver.o.requires:
.PHONY : frame/CMakeFiles/frame.dir/source/udpserver.o.requires

frame/CMakeFiles/frame.dir/source/udpserver.o.provides: frame/CMakeFiles/frame.dir/source/udpserver.o.requires
	$(MAKE) -f frame/CMakeFiles/frame.dir/build.make frame/CMakeFiles/frame.dir/source/udpserver.o.provides.build
.PHONY : frame/CMakeFiles/frame.dir/source/udpserver.o.provides

frame/CMakeFiles/frame.dir/source/udpserver.o.provides.build: frame/CMakeFiles/frame.dir/source/udpserver.o

frame/CMakeFiles/frame.dir/source/sche_timer.o: frame/CMakeFiles/frame.dir/flags.make
frame/CMakeFiles/frame.dir/source/sche_timer.o: ../frame/source/sche_timer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yy/test/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object frame/CMakeFiles/frame.dir/source/sche_timer.o"
	cd /home/yy/test/build/frame && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/frame.dir/source/sche_timer.o -c /home/yy/test/frame/source/sche_timer.cpp

frame/CMakeFiles/frame.dir/source/sche_timer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame.dir/source/sche_timer.i"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yy/test/frame/source/sche_timer.cpp > CMakeFiles/frame.dir/source/sche_timer.i

frame/CMakeFiles/frame.dir/source/sche_timer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame.dir/source/sche_timer.s"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yy/test/frame/source/sche_timer.cpp -o CMakeFiles/frame.dir/source/sche_timer.s

frame/CMakeFiles/frame.dir/source/sche_timer.o.requires:
.PHONY : frame/CMakeFiles/frame.dir/source/sche_timer.o.requires

frame/CMakeFiles/frame.dir/source/sche_timer.o.provides: frame/CMakeFiles/frame.dir/source/sche_timer.o.requires
	$(MAKE) -f frame/CMakeFiles/frame.dir/build.make frame/CMakeFiles/frame.dir/source/sche_timer.o.provides.build
.PHONY : frame/CMakeFiles/frame.dir/source/sche_timer.o.provides

frame/CMakeFiles/frame.dir/source/sche_timer.o.provides.build: frame/CMakeFiles/frame.dir/source/sche_timer.o

frame/CMakeFiles/frame.dir/source/log.o: frame/CMakeFiles/frame.dir/flags.make
frame/CMakeFiles/frame.dir/source/log.o: ../frame/source/log.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yy/test/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object frame/CMakeFiles/frame.dir/source/log.o"
	cd /home/yy/test/build/frame && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/frame.dir/source/log.o -c /home/yy/test/frame/source/log.cpp

frame/CMakeFiles/frame.dir/source/log.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frame.dir/source/log.i"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yy/test/frame/source/log.cpp > CMakeFiles/frame.dir/source/log.i

frame/CMakeFiles/frame.dir/source/log.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frame.dir/source/log.s"
	cd /home/yy/test/build/frame && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yy/test/frame/source/log.cpp -o CMakeFiles/frame.dir/source/log.s

frame/CMakeFiles/frame.dir/source/log.o.requires:
.PHONY : frame/CMakeFiles/frame.dir/source/log.o.requires

frame/CMakeFiles/frame.dir/source/log.o.provides: frame/CMakeFiles/frame.dir/source/log.o.requires
	$(MAKE) -f frame/CMakeFiles/frame.dir/build.make frame/CMakeFiles/frame.dir/source/log.o.provides.build
.PHONY : frame/CMakeFiles/frame.dir/source/log.o.provides

frame/CMakeFiles/frame.dir/source/log.o.provides.build: frame/CMakeFiles/frame.dir/source/log.o

# Object files for target frame
frame_OBJECTS = \
"CMakeFiles/frame.dir/source/sche_oper_base.o" \
"CMakeFiles/frame.dir/source/start.o" \
"CMakeFiles/frame.dir/source/udpserver.o" \
"CMakeFiles/frame.dir/source/sche_timer.o" \
"CMakeFiles/frame.dir/source/log.o"

# External object files for target frame
frame_EXTERNAL_OBJECTS =

../deploy/bin/frame: frame/CMakeFiles/frame.dir/source/sche_oper_base.o
../deploy/bin/frame: frame/CMakeFiles/frame.dir/source/start.o
../deploy/bin/frame: frame/CMakeFiles/frame.dir/source/udpserver.o
../deploy/bin/frame: frame/CMakeFiles/frame.dir/source/sche_timer.o
../deploy/bin/frame: frame/CMakeFiles/frame.dir/source/log.o
../deploy/bin/frame: frame/CMakeFiles/frame.dir/build.make
../deploy/bin/frame: frame/CMakeFiles/frame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../deploy/bin/frame"
	cd /home/yy/test/build/frame && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/frame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
frame/CMakeFiles/frame.dir/build: ../deploy/bin/frame
.PHONY : frame/CMakeFiles/frame.dir/build

frame/CMakeFiles/frame.dir/requires: frame/CMakeFiles/frame.dir/source/sche_oper_base.o.requires
frame/CMakeFiles/frame.dir/requires: frame/CMakeFiles/frame.dir/source/start.o.requires
frame/CMakeFiles/frame.dir/requires: frame/CMakeFiles/frame.dir/source/udpserver.o.requires
frame/CMakeFiles/frame.dir/requires: frame/CMakeFiles/frame.dir/source/sche_timer.o.requires
frame/CMakeFiles/frame.dir/requires: frame/CMakeFiles/frame.dir/source/log.o.requires
.PHONY : frame/CMakeFiles/frame.dir/requires

frame/CMakeFiles/frame.dir/clean:
	cd /home/yy/test/build/frame && $(CMAKE_COMMAND) -P CMakeFiles/frame.dir/cmake_clean.cmake
.PHONY : frame/CMakeFiles/frame.dir/clean

frame/CMakeFiles/frame.dir/depend:
	cd /home/yy/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yy/test /home/yy/test/frame /home/yy/test/build /home/yy/test/build/frame /home/yy/test/build/frame/CMakeFiles/frame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : frame/CMakeFiles/frame.dir/depend
