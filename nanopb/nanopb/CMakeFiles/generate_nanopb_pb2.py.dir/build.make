# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/cmake/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Desktop/nanopb/nanopb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Desktop/nanopb/nanopb

# Utility rule file for generate_nanopb_pb2.py.

# Include any custom commands dependencies for this target.
include CMakeFiles/generate_nanopb_pb2.py.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/generate_nanopb_pb2.py.dir/progress.make

CMakeFiles/generate_nanopb_pb2.py: nanopb_pb2.py

nanopb_pb2.py: generator/proto/nanopb.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/root/Desktop/nanopb/nanopb/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating nanopb_pb2.py"
	generator/protoc --python_out=/root/Desktop/nanopb/nanopb -I/root/Desktop/nanopb/nanopb/generator/proto /root/Desktop/nanopb/nanopb/generator/proto/nanopb.proto

generate_nanopb_pb2.py: CMakeFiles/generate_nanopb_pb2.py
generate_nanopb_pb2.py: nanopb_pb2.py
generate_nanopb_pb2.py: CMakeFiles/generate_nanopb_pb2.py.dir/build.make
.PHONY : generate_nanopb_pb2.py

# Rule to build all files generated by this target.
CMakeFiles/generate_nanopb_pb2.py.dir/build: generate_nanopb_pb2.py
.PHONY : CMakeFiles/generate_nanopb_pb2.py.dir/build

CMakeFiles/generate_nanopb_pb2.py.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generate_nanopb_pb2.py.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generate_nanopb_pb2.py.dir/clean

CMakeFiles/generate_nanopb_pb2.py.dir/depend:
	cd /root/Desktop/nanopb/nanopb && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Desktop/nanopb/nanopb /root/Desktop/nanopb/nanopb /root/Desktop/nanopb/nanopb /root/Desktop/nanopb/nanopb /root/Desktop/nanopb/nanopb/CMakeFiles/generate_nanopb_pb2.py.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/generate_nanopb_pb2.py.dir/depend

