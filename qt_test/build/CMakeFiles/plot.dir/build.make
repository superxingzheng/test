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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zheng/Gits/my_github/test/qt_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zheng/Gits/my_github/test/qt_test/build

# Include any dependencies generated for this target.
include CMakeFiles/plot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plot.dir/flags.make

moc_form.cxx: ../form.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zheng/Gits/my_github/test/qt_test/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_form.cxx"
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/zheng/Gits/my_github/test/qt_test/build/moc_form.cxx_parameters

ui_form.h: ../form.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zheng/Gits/my_github/test/qt_test/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_form.h"
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic -o /home/zheng/Gits/my_github/test/qt_test/build/ui_form.h /home/zheng/Gits/my_github/test/qt_test/form.ui

CMakeFiles/plot.dir/main.cpp.o: CMakeFiles/plot.dir/flags.make
CMakeFiles/plot.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zheng/Gits/my_github/test/qt_test/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plot.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plot.dir/main.cpp.o -c /home/zheng/Gits/my_github/test/qt_test/main.cpp

CMakeFiles/plot.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plot.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zheng/Gits/my_github/test/qt_test/main.cpp > CMakeFiles/plot.dir/main.cpp.i

CMakeFiles/plot.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plot.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zheng/Gits/my_github/test/qt_test/main.cpp -o CMakeFiles/plot.dir/main.cpp.s

CMakeFiles/plot.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/plot.dir/main.cpp.o.requires

CMakeFiles/plot.dir/main.cpp.o.provides: CMakeFiles/plot.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/plot.dir/build.make CMakeFiles/plot.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/plot.dir/main.cpp.o.provides

CMakeFiles/plot.dir/main.cpp.o.provides.build: CMakeFiles/plot.dir/main.cpp.o

CMakeFiles/plot.dir/form.cpp.o: CMakeFiles/plot.dir/flags.make
CMakeFiles/plot.dir/form.cpp.o: ../form.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zheng/Gits/my_github/test/qt_test/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plot.dir/form.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plot.dir/form.cpp.o -c /home/zheng/Gits/my_github/test/qt_test/form.cpp

CMakeFiles/plot.dir/form.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plot.dir/form.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zheng/Gits/my_github/test/qt_test/form.cpp > CMakeFiles/plot.dir/form.cpp.i

CMakeFiles/plot.dir/form.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plot.dir/form.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zheng/Gits/my_github/test/qt_test/form.cpp -o CMakeFiles/plot.dir/form.cpp.s

CMakeFiles/plot.dir/form.cpp.o.requires:
.PHONY : CMakeFiles/plot.dir/form.cpp.o.requires

CMakeFiles/plot.dir/form.cpp.o.provides: CMakeFiles/plot.dir/form.cpp.o.requires
	$(MAKE) -f CMakeFiles/plot.dir/build.make CMakeFiles/plot.dir/form.cpp.o.provides.build
.PHONY : CMakeFiles/plot.dir/form.cpp.o.provides

CMakeFiles/plot.dir/form.cpp.o.provides.build: CMakeFiles/plot.dir/form.cpp.o

CMakeFiles/plot.dir/moc_form.cxx.o: CMakeFiles/plot.dir/flags.make
CMakeFiles/plot.dir/moc_form.cxx.o: moc_form.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zheng/Gits/my_github/test/qt_test/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/plot.dir/moc_form.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/plot.dir/moc_form.cxx.o -c /home/zheng/Gits/my_github/test/qt_test/build/moc_form.cxx

CMakeFiles/plot.dir/moc_form.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plot.dir/moc_form.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zheng/Gits/my_github/test/qt_test/build/moc_form.cxx > CMakeFiles/plot.dir/moc_form.cxx.i

CMakeFiles/plot.dir/moc_form.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plot.dir/moc_form.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zheng/Gits/my_github/test/qt_test/build/moc_form.cxx -o CMakeFiles/plot.dir/moc_form.cxx.s

CMakeFiles/plot.dir/moc_form.cxx.o.requires:
.PHONY : CMakeFiles/plot.dir/moc_form.cxx.o.requires

CMakeFiles/plot.dir/moc_form.cxx.o.provides: CMakeFiles/plot.dir/moc_form.cxx.o.requires
	$(MAKE) -f CMakeFiles/plot.dir/build.make CMakeFiles/plot.dir/moc_form.cxx.o.provides.build
.PHONY : CMakeFiles/plot.dir/moc_form.cxx.o.provides

CMakeFiles/plot.dir/moc_form.cxx.o.provides.build: CMakeFiles/plot.dir/moc_form.cxx.o

# Object files for target plot
plot_OBJECTS = \
"CMakeFiles/plot.dir/main.cpp.o" \
"CMakeFiles/plot.dir/form.cpp.o" \
"CMakeFiles/plot.dir/moc_form.cxx.o"

# External object files for target plot
plot_EXTERNAL_OBJECTS =

plot: CMakeFiles/plot.dir/main.cpp.o
plot: CMakeFiles/plot.dir/form.cpp.o
plot: CMakeFiles/plot.dir/moc_form.cxx.o
plot: CMakeFiles/plot.dir/build.make
plot: /usr/lib/x86_64-linux-gnu/libQtGui.so
plot: /usr/lib/x86_64-linux-gnu/libQtCore.so
plot: CMakeFiles/plot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable plot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plot.dir/build: plot
.PHONY : CMakeFiles/plot.dir/build

CMakeFiles/plot.dir/requires: CMakeFiles/plot.dir/main.cpp.o.requires
CMakeFiles/plot.dir/requires: CMakeFiles/plot.dir/form.cpp.o.requires
CMakeFiles/plot.dir/requires: CMakeFiles/plot.dir/moc_form.cxx.o.requires
.PHONY : CMakeFiles/plot.dir/requires

CMakeFiles/plot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plot.dir/clean

CMakeFiles/plot.dir/depend: moc_form.cxx
CMakeFiles/plot.dir/depend: ui_form.h
	cd /home/zheng/Gits/my_github/test/qt_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zheng/Gits/my_github/test/qt_test /home/zheng/Gits/my_github/test/qt_test /home/zheng/Gits/my_github/test/qt_test/build /home/zheng/Gits/my_github/test/qt_test/build /home/zheng/Gits/my_github/test/qt_test/build/CMakeFiles/plot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plot.dir/depend
