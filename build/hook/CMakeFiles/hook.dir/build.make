# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/mizuta/Documents/LittleSLAM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mizuta/Documents/LittleSLAM/build

# Include any dependencies generated for this target.
include hook/CMakeFiles/hook.dir/depend.make

# Include the progress variables for this target.
include hook/CMakeFiles/hook.dir/progress.make

# Include the compile flags for this target's objects.
include hook/CMakeFiles/hook.dir/flags.make

hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o: ../hook/RefScanMakerBS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/RefScanMakerBS.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/RefScanMakerBS.cpp

hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/RefScanMakerBS.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/RefScanMakerBS.cpp > CMakeFiles/hook.dir/RefScanMakerBS.cpp.i

hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/RefScanMakerBS.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/RefScanMakerBS.cpp -o CMakeFiles/hook.dir/RefScanMakerBS.cpp.s

hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.requires

hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.provides: hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.provides

hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.provides.build: hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o


hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o: ../hook/RefScanMakerLM.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/RefScanMakerLM.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/RefScanMakerLM.cpp

hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/RefScanMakerLM.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/RefScanMakerLM.cpp > CMakeFiles/hook.dir/RefScanMakerLM.cpp.i

hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/RefScanMakerLM.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/RefScanMakerLM.cpp -o CMakeFiles/hook.dir/RefScanMakerLM.cpp.s

hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.requires

hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.provides: hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.provides

hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.provides.build: hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o


hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o: ../hook/CostFunctionED.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/CostFunctionED.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/CostFunctionED.cpp

hook/CMakeFiles/hook.dir/CostFunctionED.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/CostFunctionED.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/CostFunctionED.cpp > CMakeFiles/hook.dir/CostFunctionED.cpp.i

hook/CMakeFiles/hook.dir/CostFunctionED.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/CostFunctionED.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/CostFunctionED.cpp -o CMakeFiles/hook.dir/CostFunctionED.cpp.s

hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.requires

hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.provides: hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.provides

hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.provides.build: hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o


hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o: ../hook/CostFunctionPD.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/CostFunctionPD.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/CostFunctionPD.cpp

hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/CostFunctionPD.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/CostFunctionPD.cpp > CMakeFiles/hook.dir/CostFunctionPD.cpp.i

hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/CostFunctionPD.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/CostFunctionPD.cpp -o CMakeFiles/hook.dir/CostFunctionPD.cpp.s

hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.requires

hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.provides: hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.provides

hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.provides.build: hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o


hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o: ../hook/PoseOptimizerSD.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/PoseOptimizerSD.cpp

hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/PoseOptimizerSD.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/PoseOptimizerSD.cpp > CMakeFiles/hook.dir/PoseOptimizerSD.cpp.i

hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/PoseOptimizerSD.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/PoseOptimizerSD.cpp -o CMakeFiles/hook.dir/PoseOptimizerSD.cpp.s

hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.requires

hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.provides: hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.provides

hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.provides.build: hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o


hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o: ../hook/PoseOptimizerSL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/PoseOptimizerSL.cpp

hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/PoseOptimizerSL.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/PoseOptimizerSL.cpp > CMakeFiles/hook.dir/PoseOptimizerSL.cpp.i

hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/PoseOptimizerSL.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/PoseOptimizerSL.cpp -o CMakeFiles/hook.dir/PoseOptimizerSL.cpp.s

hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.requires

hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.provides: hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.provides

hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.provides.build: hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o


hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o: ../hook/DataAssociatorLS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/DataAssociatorLS.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/DataAssociatorLS.cpp

hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/DataAssociatorLS.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/DataAssociatorLS.cpp > CMakeFiles/hook.dir/DataAssociatorLS.cpp.i

hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/DataAssociatorLS.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/DataAssociatorLS.cpp -o CMakeFiles/hook.dir/DataAssociatorLS.cpp.s

hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.requires

hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.provides: hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.provides

hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.provides.build: hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o


hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o: ../hook/DataAssociatorGT.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/DataAssociatorGT.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/DataAssociatorGT.cpp

hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/DataAssociatorGT.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/DataAssociatorGT.cpp > CMakeFiles/hook.dir/DataAssociatorGT.cpp.i

hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/DataAssociatorGT.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/DataAssociatorGT.cpp -o CMakeFiles/hook.dir/DataAssociatorGT.cpp.s

hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.requires

hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.provides: hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.provides

hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.provides.build: hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o


hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o: ../hook/PointCloudMapBS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/PointCloudMapBS.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapBS.cpp

hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/PointCloudMapBS.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapBS.cpp > CMakeFiles/hook.dir/PointCloudMapBS.cpp.i

hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/PointCloudMapBS.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapBS.cpp -o CMakeFiles/hook.dir/PointCloudMapBS.cpp.s

hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.requires

hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.provides: hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.provides

hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.provides.build: hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o


hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o: ../hook/PointCloudMapGT.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/PointCloudMapGT.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapGT.cpp

hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/PointCloudMapGT.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapGT.cpp > CMakeFiles/hook.dir/PointCloudMapGT.cpp.i

hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/PointCloudMapGT.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapGT.cpp -o CMakeFiles/hook.dir/PointCloudMapGT.cpp.s

hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.requires

hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.provides: hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.provides

hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.provides.build: hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o


hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o: ../hook/PointCloudMapLP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/PointCloudMapLP.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapLP.cpp

hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/PointCloudMapLP.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapLP.cpp > CMakeFiles/hook.dir/PointCloudMapLP.cpp.i

hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/PointCloudMapLP.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/PointCloudMapLP.cpp -o CMakeFiles/hook.dir/PointCloudMapLP.cpp.s

hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.requires

hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.provides: hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.provides

hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.provides.build: hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o


hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o: hook/CMakeFiles/hook.dir/flags.make
hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o: ../hook/LoopDetectorSS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hook.dir/LoopDetectorSS.cpp.o -c /home/mizuta/Documents/LittleSLAM/hook/LoopDetectorSS.cpp

hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hook.dir/LoopDetectorSS.cpp.i"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mizuta/Documents/LittleSLAM/hook/LoopDetectorSS.cpp > CMakeFiles/hook.dir/LoopDetectorSS.cpp.i

hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hook.dir/LoopDetectorSS.cpp.s"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mizuta/Documents/LittleSLAM/hook/LoopDetectorSS.cpp -o CMakeFiles/hook.dir/LoopDetectorSS.cpp.s

hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.requires:

.PHONY : hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.requires

hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.provides: hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.requires
	$(MAKE) -f hook/CMakeFiles/hook.dir/build.make hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.provides.build
.PHONY : hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.provides

hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.provides.build: hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o


# Object files for target hook
hook_OBJECTS = \
"CMakeFiles/hook.dir/RefScanMakerBS.cpp.o" \
"CMakeFiles/hook.dir/RefScanMakerLM.cpp.o" \
"CMakeFiles/hook.dir/CostFunctionED.cpp.o" \
"CMakeFiles/hook.dir/CostFunctionPD.cpp.o" \
"CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o" \
"CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o" \
"CMakeFiles/hook.dir/DataAssociatorLS.cpp.o" \
"CMakeFiles/hook.dir/DataAssociatorGT.cpp.o" \
"CMakeFiles/hook.dir/PointCloudMapBS.cpp.o" \
"CMakeFiles/hook.dir/PointCloudMapGT.cpp.o" \
"CMakeFiles/hook.dir/PointCloudMapLP.cpp.o" \
"CMakeFiles/hook.dir/LoopDetectorSS.cpp.o"

# External object files for target hook
hook_EXTERNAL_OBJECTS =

hook/libhook.a: hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o
hook/libhook.a: hook/CMakeFiles/hook.dir/build.make
hook/libhook.a: hook/CMakeFiles/hook.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mizuta/Documents/LittleSLAM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX static library libhook.a"
	cd /home/mizuta/Documents/LittleSLAM/build/hook && $(CMAKE_COMMAND) -P CMakeFiles/hook.dir/cmake_clean_target.cmake
	cd /home/mizuta/Documents/LittleSLAM/build/hook && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hook.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hook/CMakeFiles/hook.dir/build: hook/libhook.a

.PHONY : hook/CMakeFiles/hook.dir/build

hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/RefScanMakerBS.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/RefScanMakerLM.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/CostFunctionED.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/CostFunctionPD.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/PoseOptimizerSD.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/PoseOptimizerSL.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/DataAssociatorLS.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/DataAssociatorGT.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/PointCloudMapBS.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/PointCloudMapGT.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/PointCloudMapLP.cpp.o.requires
hook/CMakeFiles/hook.dir/requires: hook/CMakeFiles/hook.dir/LoopDetectorSS.cpp.o.requires

.PHONY : hook/CMakeFiles/hook.dir/requires

hook/CMakeFiles/hook.dir/clean:
	cd /home/mizuta/Documents/LittleSLAM/build/hook && $(CMAKE_COMMAND) -P CMakeFiles/hook.dir/cmake_clean.cmake
.PHONY : hook/CMakeFiles/hook.dir/clean

hook/CMakeFiles/hook.dir/depend:
	cd /home/mizuta/Documents/LittleSLAM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mizuta/Documents/LittleSLAM /home/mizuta/Documents/LittleSLAM/hook /home/mizuta/Documents/LittleSLAM/build /home/mizuta/Documents/LittleSLAM/build/hook /home/mizuta/Documents/LittleSLAM/build/hook/CMakeFiles/hook.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hook/CMakeFiles/hook.dir/depend

