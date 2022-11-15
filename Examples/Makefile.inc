# BEWARE
# This file must be renamed into Makefile.inc in order to work!!
#
# *****  This is the user defined part of the Makefile
#
#  It is included in almost all Makefiles of the example 
#
# It has been modified so to read some data from environmental variables
# and be compatible with the system of modules used at MOX
#
# YOU CAN change it to suit your need!!!!
#
# Recall that you may also change some options on the fly using
#
#   make target OPTION=MY_OPTION
#
# for instance if you want to change the compiler to clang on the fly
#
# make target CXX=clang++
#

# The directory where the examples reside (you HAVE to change this)
AMSC_ROOT?=/home/marco/Documents/Uni/4-1/AMfSC/CartellaDocker/AMSC-Examples/Examples/
# The directory with the Eigen (leave blank if they are in a standard directory)
mkEigenInc?=/usr/local/include/eigen3/
EIGEN_DIR=$(mkEigenInc)
#
# Mpi directories for library and include files
#
mkOpenmpiLib?=/usr/lib/x86_64-linux-gnu
mkOpenmpiInc?=/usr/lib/x86_64-linux-gnu/openmpi/include
MPI_LIBDIR=${mkOpenmpiLib}
MPI_INCDIR=${mkOpenmpiInc}
#
# C++ native parallelization support with g++ needs the TBB libraries
#
mkTbbInc?=/usr/include
mkTbbLib?=/usr/lib/x86_64-linux-gnu/
TBB_LIBDIR=${mkTbbLib}
TBB_INCDIR=${mkTbbIn}
#
# Boost libraries
# 
mkBoostInc?=/usr/include/boost/
mkBoostLib?=/usr/lib/x86_64-linux-gnu/
BOOST_INCDIR=mkBoostInc
BOOST_LIBDIR=mkBoostLib
#
# Name of additional libraries (set by the local Makefile.inc if necessary)
#
LIBRARIES=
# Extra directories. Set by local Makefile.inc if required
OTHER_LIB_DIR=
OTHER_INC_DIR=

#
# The C++ compiler (taken from an environmental variable)
#
mkCxxCompiler?=g++
CXX = ${mkCxxCompiler}
#
mkCCompiler?=gcc
CC = ${mkCCompiler}

mkMpiCCompiler?=mpicc
MPI_CC=$mkMpiCCompiler

mkMpiCxxCompiler?=mpic++
MPI_CXX=$mkMpiCCompiler

MPI_RUN=mpirun --use-hwthread-cpus


# Since we are only using c++ I set the linker LINK.o for object files
# so that it uses the c++ compiler. Make has no separate macro for the linker!
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)
#
# Maybe you have to add the library for the clang compiler
# if not installed in the standard directories.
#
ifeq ($(findstring clang, $(CXX)),clang)
 OTHER_LIB_DIR+=
endif
#
#  DEFINES: Possible -DXX statements
# Example
# -DNDEBUG disactivates asserts
DEFINES=
#
#  OPTIMIZATION
# Warning flags: Level of warning
# -Wall main warnings activated
# -Wextra some extra warnings activated
# -Wsuggest-override  as the name says
# -Wnon-virtual-dtor Warns if a class with virtual meths oda does not have virt dstructors
# -Weffc++ Wanrs about violation of the coding style in Scott Mayer's Effective C++

# I eliminate some warnings to avoid complaints when compiling with MPI
WARNFLAGS=-Wall -Wextra -Wno-suggest-override -Wnon-virtual-dtor -Wno-cast-function-type
#
# Optimization flags : May be selected by using the variable DEBUG
#
# DEBUG=no  -> OPTFLAGS=-O3
# DEBUG=yes -> OPTFLAGS=-g
# -c       compile only, generate corresponding .o files
# -g       generate code suitable for the debugger
# -p       generate code suitable for the profiler
# -O       attemp code optimizations
####
#
# Common file for Doxygen documentation
export DOXYFILE=$(AMSC_ROOT)/DoxyfileCommon
##
# ************ END USER MODIFIABLE PART *****************
##



ifeq ($(DEBUG),no)
  OPTFLAGS=-O3 -funroll-loops #maybe you want -O3
  DEFINES+=-DNDEBUG
else
  OPTFLAGS=-g
endif

#To simplify linking with local libraries
LDFLAGS=-Wl,-rpath=. -Wl,-rpath=$(AMSC_ROOT)/lib#

# Add verbosity if needed
ifeq ($(VERBOSE),yes)
  VERBOSITY=-DVERBOSE
endif
#
# Flags for standard 
#
STANDARD=c++20
# 
# Location of
# Doxygen configuration file
#
export STDFLAGS=-std=$(STANDARD)
#
#  libraries are stored here
#
export AMSC_LIB_DIR=$(AMSC_ROOT)/lib
#
# Main AMSC include directory
#
export AMSC_INC_DIR=$(AMSC_ROOT)/include
#
# Other directories with libraries (if needed)
#
export OTHER_LIB_DIR
#
# Other include directories (if needed)
#
export OTHER_INC_DIR
export CC
export CXX
#
# Compose options
#
# collect all includes
ALL_INC_DIR= $(AMSC_INC_DIR) $(OTHER_INC_DIR) $(EIGEN_DIR)
includes := $(foreach inc,$(ALL_INC_DIR),-I$(inc) )
# where to look for include files:
# first the current directory, then the directory ./include
# and then the possible other specifyed in OTHER_INC_DIR
INCLS  = -I. -I./include $(includes) 
# collect all library dirs
ALL_LIB_DIR=$(AMSC_LIB_DIR) $(OTHER_LIB_DIR)
LIBD := $(foreach lib,$(ALL_LIB_DIR),-L$(lib) )
#
# Set make macros
#
export CPPFLAGS=$(INCLS) $(DEFINES) $(VERBOSITY)
export CXXFLAGS=$(OPTFLAGS) $(STDFLAGS) $(WARNFLAGS)
#
# For C Programs 
#
export CCFLAGS=$(CXXFLAGS)
#
# name of file with dependencies
#
#header files
export LDFLAGS+=$(OPTFLAGS) 
export DEPEND=make.dep
# to avoid nasty warnings
export ARFLAGS=rsU
# Rule to generate pdf from latex files
# Twice to solve undefined labels
%.pdf:%.tex
	pdflatex $<
	pdflatex $<


