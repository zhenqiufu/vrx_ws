# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/skloe/vrx_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/skloe/vrx_ws/build

# Utility rule file for rxi__xacro_auto_generate.

# Include the progress variables for this target.
include rxi/CMakeFiles/rxi__xacro_auto_generate.dir/progress.make

rxi/CMakeFiles/rxi__xacro_auto_generate: rxi/worlds/rxi.world


rxi/worlds/rxi.world: /home/skloe/vrx_ws/src/rxi/worlds/rxi.world.xacro
rxi/worlds/rxi.world: /home/skloe/vrx_ws/src/vrx/wave_gazebo/world_models/ocean_waves/model.xacro
rxi/worlds/rxi.world: /home/skloe/vrx_ws/src/vrx/vrx_gazebo/worlds/xacros/usv_wind_plugin.xacro
rxi/worlds/rxi.world: /home/skloe/vrx_ws/src/vrx/vrx_gazebo/worlds/sandisland.xacro
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/skloe/vrx_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "xacro: generating worlds/rxi.world from worlds/rxi.world.xacro"
	cd /home/skloe/vrx_ws/src/rxi && /home/skloe/vrx_ws/build/catkin_generated/env_cached.sh xacro -o /home/skloe/vrx_ws/build/rxi/worlds/rxi.world worlds/rxi.world.xacro

rxi__xacro_auto_generate: rxi/CMakeFiles/rxi__xacro_auto_generate
rxi__xacro_auto_generate: rxi/worlds/rxi.world
rxi__xacro_auto_generate: rxi/CMakeFiles/rxi__xacro_auto_generate.dir/build.make

.PHONY : rxi__xacro_auto_generate

# Rule to build all files generated by this target.
rxi/CMakeFiles/rxi__xacro_auto_generate.dir/build: rxi__xacro_auto_generate

.PHONY : rxi/CMakeFiles/rxi__xacro_auto_generate.dir/build

rxi/CMakeFiles/rxi__xacro_auto_generate.dir/clean:
	cd /home/skloe/vrx_ws/build/rxi && $(CMAKE_COMMAND) -P CMakeFiles/rxi__xacro_auto_generate.dir/cmake_clean.cmake
.PHONY : rxi/CMakeFiles/rxi__xacro_auto_generate.dir/clean

rxi/CMakeFiles/rxi__xacro_auto_generate.dir/depend:
	cd /home/skloe/vrx_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/skloe/vrx_ws/src /home/skloe/vrx_ws/src/rxi /home/skloe/vrx_ws/build /home/skloe/vrx_ws/build/rxi /home/skloe/vrx_ws/build/rxi/CMakeFiles/rxi__xacro_auto_generate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : rxi/CMakeFiles/rxi__xacro_auto_generate.dir/depend

