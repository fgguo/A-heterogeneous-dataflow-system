# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fug/software/AIR-master/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fug/software/AIR-master/src/Build

# Include any dependencies generated for this target.
include CMakeFiles/GPU.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GPU.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GPU.dir/flags.make

CMakeFiles/GPU.dir/host.cpp.o: CMakeFiles/GPU.dir/flags.make
CMakeFiles/GPU.dir/host.cpp.o: ../host.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GPU.dir/host.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GPU.dir/host.cpp.o -c /home/fug/software/AIR-master/src/host.cpp

CMakeFiles/GPU.dir/host.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GPU.dir/host.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fug/software/AIR-master/src/host.cpp > CMakeFiles/GPU.dir/host.cpp.i

CMakeFiles/GPU.dir/host.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GPU.dir/host.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fug/software/AIR-master/src/host.cpp -o CMakeFiles/GPU.dir/host.cpp.s

# Object files for target GPU
GPU_OBJECTS = \
"CMakeFiles/GPU.dir/host.cpp.o"

# External object files for target GPU
GPU_EXTERNAL_OBJECTS =

libGPU.a: CMakeFiles/GPU.dir/host.cpp.o
libGPU.a: CMakeFiles/GPU.dir/build.make
libGPU.a: CMakeFiles/GPU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGPU.a"
	$(CMAKE_COMMAND) -P CMakeFiles/GPU.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GPU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GPU.dir/build: libGPU.a

.PHONY : CMakeFiles/GPU.dir/build

CMakeFiles/GPU.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GPU.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GPU.dir/clean

CMakeFiles/GPU.dir/depend:
	cd /home/fug/software/AIR-master/src/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fug/software/AIR-master/src /home/fug/software/AIR-master/src /home/fug/software/AIR-master/src/Build /home/fug/software/AIR-master/src/Build /home/fug/software/AIR-master/src/Build/CMakeFiles/GPU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GPU.dir/depend

