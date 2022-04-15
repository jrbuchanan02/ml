################################################################################
# This is the file that allows you to make ML.
#
# ML can compile for these targets:
#
# 1. shared library
# 2. source library
# 3. unittest executable
#
# Source library does not compile anything, but does append to the variables
# "source files" and "include directories." Use the variable "ML_REL_PATH" to
# modify the prefixes to these files.
#
# Shared library produces a shared library called ml.dll on Windows Systems and
# libml on POSIX systems. While this shared library contains all the same
# features as the source library, you must use the C interface on any system.
# Using the C interface is optional (and not recommmended) when used as a 
# source library.
#
# The unittest executable target produces an executable file of the default name
# (either a.out or a.exe) which contains a set of internal unittests.
#
# On all path names, ML expects forward slashes. This is not a problem on POSIX
# systems but should be known on Windows systems.
################################################################################


# set the ML_REL_PATH variable if it is not set already. This value is the one
# natively in the ML repository.
ML_REL_PATH ?= ./source

# Where the files ML needs to build for itself reside
ml_code_location := $(ML_REL_PATH)/code
# Where the build.cc and ml.hh files reside
ml_intf_location := $(ML_REL_PATH)/intf
# The directories ML needs included to build properly
ml_internal_include_dirs := $(ML_REL_PATH) $(ml_code_location) $(ml_intf_location)

# In a vacuum, explicitly go with the default in g++ 10.3. ML requires at least
# C++ 11 for its features.
CXX_STANDARD ?= 14

ML_LIB_NAME ?= ml.dll

# code in all targets
# CC -> C++ source files which do not implement templates. TCC files are
# included with their header files.
ml_source += $(wildcard $(ml_code_location)/math/*.cc)

shared:
	$(CXX) $(CXXFLAGS) --std=c++$(CXX_STANDARD) --shared $(ml_source) $(ML_REL_PATH)/intf/build.cc -o $(ML_REL_PATH)/../$(ML_LIB_NAME) $(foreach dir, $(ml_internal_include_dirs), -I $(dir))

source: SOURCE_FILES += $(ml_source)

unittest:
	$(CXX) $(CXXFLAGS) --std=c++$(CXX_STANDARD) $(ml_source) $(ML_REL_PATH)/code/unittest.cc $(foreach dir, $(ml_internal_include_dirs), -I $(dir))

shared_test: shared
	$(CXX) $(CXXFLAGS) --std=c++$(CXX_STANDARD) $(ml_source) $(ML_REL_PATH)/test/shared.cc $(foreach dir, $(ml_internal_include_dirs), -I $(dir)) $(join -L,$(ML_REL_PATH)/..) $(join -l,ml) -o $(ML_REL_PATH)/../ml_lib_test.exe