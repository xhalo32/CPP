# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/niklas/CPP/netengine/netalk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/niklas/CPP/netengine/netalk/build

# Include any dependencies generated for this target.
include CMakeFiles/netalk.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/netalk.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/netalk.dir/flags.make

CMakeFiles/netalk.dir/netalk.cpp.o: CMakeFiles/netalk.dir/flags.make
CMakeFiles/netalk.dir/netalk.cpp.o: ../netalk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niklas/CPP/netengine/netalk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/netalk.dir/netalk.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/netalk.dir/netalk.cpp.o -c /home/niklas/CPP/netengine/netalk/netalk.cpp

CMakeFiles/netalk.dir/netalk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/netalk.dir/netalk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niklas/CPP/netengine/netalk/netalk.cpp > CMakeFiles/netalk.dir/netalk.cpp.i

CMakeFiles/netalk.dir/netalk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/netalk.dir/netalk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niklas/CPP/netengine/netalk/netalk.cpp -o CMakeFiles/netalk.dir/netalk.cpp.s

CMakeFiles/netalk.dir/netalk.cpp.o.requires:

.PHONY : CMakeFiles/netalk.dir/netalk.cpp.o.requires

CMakeFiles/netalk.dir/netalk.cpp.o.provides: CMakeFiles/netalk.dir/netalk.cpp.o.requires
	$(MAKE) -f CMakeFiles/netalk.dir/build.make CMakeFiles/netalk.dir/netalk.cpp.o.provides.build
.PHONY : CMakeFiles/netalk.dir/netalk.cpp.o.provides

CMakeFiles/netalk.dir/netalk.cpp.o.provides.build: CMakeFiles/netalk.dir/netalk.cpp.o


CMakeFiles/netalk.dir/client.cpp.o: CMakeFiles/netalk.dir/flags.make
CMakeFiles/netalk.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niklas/CPP/netengine/netalk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/netalk.dir/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/netalk.dir/client.cpp.o -c /home/niklas/CPP/netengine/netalk/client.cpp

CMakeFiles/netalk.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/netalk.dir/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niklas/CPP/netengine/netalk/client.cpp > CMakeFiles/netalk.dir/client.cpp.i

CMakeFiles/netalk.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/netalk.dir/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niklas/CPP/netengine/netalk/client.cpp -o CMakeFiles/netalk.dir/client.cpp.s

CMakeFiles/netalk.dir/client.cpp.o.requires:

.PHONY : CMakeFiles/netalk.dir/client.cpp.o.requires

CMakeFiles/netalk.dir/client.cpp.o.provides: CMakeFiles/netalk.dir/client.cpp.o.requires
	$(MAKE) -f CMakeFiles/netalk.dir/build.make CMakeFiles/netalk.dir/client.cpp.o.provides.build
.PHONY : CMakeFiles/netalk.dir/client.cpp.o.provides

CMakeFiles/netalk.dir/client.cpp.o.provides.build: CMakeFiles/netalk.dir/client.cpp.o


CMakeFiles/netalk.dir/server.cpp.o: CMakeFiles/netalk.dir/flags.make
CMakeFiles/netalk.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niklas/CPP/netengine/netalk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/netalk.dir/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/netalk.dir/server.cpp.o -c /home/niklas/CPP/netengine/netalk/server.cpp

CMakeFiles/netalk.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/netalk.dir/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niklas/CPP/netengine/netalk/server.cpp > CMakeFiles/netalk.dir/server.cpp.i

CMakeFiles/netalk.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/netalk.dir/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niklas/CPP/netengine/netalk/server.cpp -o CMakeFiles/netalk.dir/server.cpp.s

CMakeFiles/netalk.dir/server.cpp.o.requires:

.PHONY : CMakeFiles/netalk.dir/server.cpp.o.requires

CMakeFiles/netalk.dir/server.cpp.o.provides: CMakeFiles/netalk.dir/server.cpp.o.requires
	$(MAKE) -f CMakeFiles/netalk.dir/build.make CMakeFiles/netalk.dir/server.cpp.o.provides.build
.PHONY : CMakeFiles/netalk.dir/server.cpp.o.provides

CMakeFiles/netalk.dir/server.cpp.o.provides.build: CMakeFiles/netalk.dir/server.cpp.o


# Object files for target netalk
netalk_OBJECTS = \
"CMakeFiles/netalk.dir/netalk.cpp.o" \
"CMakeFiles/netalk.dir/client.cpp.o" \
"CMakeFiles/netalk.dir/server.cpp.o"

# External object files for target netalk
netalk_EXTERNAL_OBJECTS =

netalk: CMakeFiles/netalk.dir/netalk.cpp.o
netalk: CMakeFiles/netalk.dir/client.cpp.o
netalk: CMakeFiles/netalk.dir/server.cpp.o
netalk: CMakeFiles/netalk.dir/build.make
netalk: /usr/lib/libsfml-network.so
netalk: /usr/lib/libsfml-system.so
netalk: CMakeFiles/netalk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/niklas/CPP/netengine/netalk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable netalk"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/netalk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/netalk.dir/build: netalk

.PHONY : CMakeFiles/netalk.dir/build

CMakeFiles/netalk.dir/requires: CMakeFiles/netalk.dir/netalk.cpp.o.requires
CMakeFiles/netalk.dir/requires: CMakeFiles/netalk.dir/client.cpp.o.requires
CMakeFiles/netalk.dir/requires: CMakeFiles/netalk.dir/server.cpp.o.requires

.PHONY : CMakeFiles/netalk.dir/requires

CMakeFiles/netalk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/netalk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/netalk.dir/clean

CMakeFiles/netalk.dir/depend:
	cd /home/niklas/CPP/netengine/netalk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/niklas/CPP/netengine/netalk /home/niklas/CPP/netengine/netalk /home/niklas/CPP/netengine/netalk/build /home/niklas/CPP/netengine/netalk/build /home/niklas/CPP/netengine/netalk/build/CMakeFiles/netalk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/netalk.dir/depend
