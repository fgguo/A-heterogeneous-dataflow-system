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
include cudaCode/CMakeFiles/GPU.dir/depend.make

# Include the progress variables for this target.
include cudaCode/CMakeFiles/GPU.dir/progress.make

# Include the compile flags for this target's objects.
include cudaCode/CMakeFiles/GPU.dir/flags.make

cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o.depend
cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o.Build.cmake
cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o: ../cudaCode/gpuMap.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building NVCC (Device) object cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o"
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -E make_directory /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//.
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -D verbose:BOOL=$(VERBOSE) -D build_configuration:STRING=Build -D generated_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_gpuMap.cu.o -D generated_cubin_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_gpuMap.cu.o.cubin.txt -P /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//GPU_generated_gpuMap.cu.o.Build.cmake

cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o.depend
cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o.Build.cmake
cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o: ../cudaCode/gpuReduce.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building NVCC (Device) object cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o"
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -E make_directory /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//.
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -D verbose:BOOL=$(VERBOSE) -D build_configuration:STRING=Build -D generated_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_gpuReduce.cu.o -D generated_cubin_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_gpuReduce.cu.o.cubin.txt -P /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//GPU_generated_gpuReduce.cu.o.Build.cmake

cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o.depend
cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o.Build.cmake
cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o: ../cudaCode/hello.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building NVCC (Device) object cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o"
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -E make_directory /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//.
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -D verbose:BOOL=$(VERBOSE) -D build_configuration:STRING=Build -D generated_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_hello.cu.o -D generated_cubin_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_hello.cu.o.cubin.txt -P /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//GPU_generated_hello.cu.o.Build.cmake

cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o.depend
cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o.Build.cmake
cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o: ../cudaCode/multi.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building NVCC (Device) object cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o"
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -E make_directory /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//.
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -D verbose:BOOL=$(VERBOSE) -D build_configuration:STRING=Build -D generated_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_multi.cu.o -D generated_cubin_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_multi.cu.o.cubin.txt -P /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//GPU_generated_multi.cu.o.Build.cmake

cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o.depend
cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o: cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o.Build.cmake
cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o: ../cudaCode/sum.cu
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building NVCC (Device) object cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o"
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -E make_directory /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//.
	cd /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir && /usr/local/bin/cmake -D verbose:BOOL=$(VERBOSE) -D build_configuration:STRING=Build -D generated_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_sum.cu.o -D generated_cubin_file:STRING=/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//./GPU_generated_sum.cu.o.cubin.txt -P /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir//GPU_generated_sum.cu.o.Build.cmake

cudaCode/CMakeFiles/GPU.dir/cp.cpp.o: cudaCode/CMakeFiles/GPU.dir/flags.make
cudaCode/CMakeFiles/GPU.dir/cp.cpp.o: ../cudaCode/cp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object cudaCode/CMakeFiles/GPU.dir/cp.cpp.o"
	cd /home/fug/software/AIR-master/src/Build/cudaCode && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/GPU.dir/cp.cpp.o -c /home/fug/software/AIR-master/src/cudaCode/cp.cpp

cudaCode/CMakeFiles/GPU.dir/cp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GPU.dir/cp.cpp.i"
	cd /home/fug/software/AIR-master/src/Build/cudaCode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fug/software/AIR-master/src/cudaCode/cp.cpp > CMakeFiles/GPU.dir/cp.cpp.i

cudaCode/CMakeFiles/GPU.dir/cp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GPU.dir/cp.cpp.s"
	cd /home/fug/software/AIR-master/src/Build/cudaCode && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fug/software/AIR-master/src/cudaCode/cp.cpp -o CMakeFiles/GPU.dir/cp.cpp.s

# Object files for target GPU
GPU_OBJECTS = \
"CMakeFiles/GPU.dir/cp.cpp.o"

# External object files for target GPU
GPU_EXTERNAL_OBJECTS = \
"/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o" \
"/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o" \
"/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o" \
"/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o" \
"/home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o"

cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/cp.cpp.o
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/build.make
cudaCode/libGPU.a: cudaCode/CMakeFiles/GPU.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fug/software/AIR-master/src/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libGPU.a"
	cd /home/fug/software/AIR-master/src/Build/cudaCode && $(CMAKE_COMMAND) -P CMakeFiles/GPU.dir/cmake_clean_target.cmake
	cd /home/fug/software/AIR-master/src/Build/cudaCode && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GPU.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cudaCode/CMakeFiles/GPU.dir/build: cudaCode/libGPU.a

.PHONY : cudaCode/CMakeFiles/GPU.dir/build

cudaCode/CMakeFiles/GPU.dir/clean:
	cd /home/fug/software/AIR-master/src/Build/cudaCode && $(CMAKE_COMMAND) -P CMakeFiles/GPU.dir/cmake_clean.cmake
.PHONY : cudaCode/CMakeFiles/GPU.dir/clean

cudaCode/CMakeFiles/GPU.dir/depend: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuMap.cu.o
cudaCode/CMakeFiles/GPU.dir/depend: cudaCode/CMakeFiles/GPU.dir/GPU_generated_gpuReduce.cu.o
cudaCode/CMakeFiles/GPU.dir/depend: cudaCode/CMakeFiles/GPU.dir/GPU_generated_hello.cu.o
cudaCode/CMakeFiles/GPU.dir/depend: cudaCode/CMakeFiles/GPU.dir/GPU_generated_multi.cu.o
cudaCode/CMakeFiles/GPU.dir/depend: cudaCode/CMakeFiles/GPU.dir/GPU_generated_sum.cu.o
	cd /home/fug/software/AIR-master/src/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fug/software/AIR-master/src /home/fug/software/AIR-master/src/cudaCode /home/fug/software/AIR-master/src/Build /home/fug/software/AIR-master/src/Build/cudaCode /home/fug/software/AIR-master/src/Build/cudaCode/CMakeFiles/GPU.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cudaCode/CMakeFiles/GPU.dir/depend

