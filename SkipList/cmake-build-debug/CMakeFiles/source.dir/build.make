# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /private/var/folders/7b/t_swdbxn72s7ffr_pqwwmfhr0000gn/T/AppTranslocation/3D536C73-14D0-41FF-BA54-8BDD303254B7/d/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /private/var/folders/7b/t_swdbxn72s7ffr_pqwwmfhr0000gn/T/AppTranslocation/3D536C73-14D0-41FF-BA54-8BDD303254B7/d/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/source.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/source.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/source.dir/flags.make

CMakeFiles/source.dir/main.cpp.o: CMakeFiles/source.dir/flags.make
CMakeFiles/source.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/source.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/source.dir/main.cpp.o -c /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/main.cpp

CMakeFiles/source.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/source.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/main.cpp > CMakeFiles/source.dir/main.cpp.i

CMakeFiles/source.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/source.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/main.cpp -o CMakeFiles/source.dir/main.cpp.s

# Object files for target source
source_OBJECTS = \
"CMakeFiles/source.dir/main.cpp.o"

# External object files for target source
source_EXTERNAL_OBJECTS =

source: CMakeFiles/source.dir/main.cpp.o
source: CMakeFiles/source.dir/build.make
source: CMakeFiles/source.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable source"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/source.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/source.dir/build: source

.PHONY : CMakeFiles/source.dir/build

CMakeFiles/source.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/source.dir/cmake_clean.cmake
.PHONY : CMakeFiles/source.dir/clean

CMakeFiles/source.dir/depend:
	cd /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug /Users/vitalijugnivenko/Downloads/Skip-List-master/SkipList/cmake-build-debug/CMakeFiles/source.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/source.dir/depend

