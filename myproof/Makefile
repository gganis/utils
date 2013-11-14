# Makefile for a PROOF standalone program.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Author: G. Ganis, 11/2013

RC     := root-config
ifeq ($(shell which $(RC) 2>&1 | sed -ne "s@.*/$(RC)@$(RC)@p"),$(RC))
MKARCH := $(wildcard $(shell $(RC) --etcdir)/Makefile.arch)
RCONFIG := $(wildcard $(shell $(RC) --incdir)/RConfigure.h)
endif
ifneq ($(MKARCH),)
include $(MKARCH)
else
ifeq ($(ROOTSYS),)
ROOTSYS = ..
endif
include $(ROOTSYS)/etc/Makefile.arch
endif
# Tutorials dir needed by myProof
ifneq ($(RCONFIG),)
TUTDIR := $(wildcard $(shell grep ROOTDOCDIR $(RCONFIG) | sed "s|.*\"\(.*\)\"|\1|")/tutorials)
endif
ifeq ($(TUTDIR),)
ifeq ($(ROOTSYS),)
ROOTSYS = ..
endif
TUTDIR := $(ROOTSYS)/tutorials
endif
-include ../MyConfig.mk

#------------------------------------------------------------------------------

MYPROOFO  = myProof.$(ObjSuf)
MYPROOFS  = myProof.$(SrcSuf)
MYPROOF   = myProof$(ExeSuf)

OBJS          = $(MYPROOFO)

PROGRAMS      = $(MYPROOF)

ifeq ($(ARCH),aix5)
MAKESHARED    = /usr/vacpp/bin/makeC++SharedLib
endif

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)
.PHONY:    Aclock Hello Tetris

all:            $(PROGRAMS)

$(MYPROOF): $(MYPROOFO)
ifeq ($(PLATFORM),win32)
		$(LD) $(LDFLAGS) $^ $(LIBS) '$(ROOTSYS)/lib/libProof.lib' '$(ROOTSYS)/lib/libThread.lib' $(OutPutOpt)$@
		$(MT_EXE)
else
		$(LD) $(LDFLAGS) $(MYPROOFO) $(LIBS) -lProof -lProofPlayer -lThread $(OutPutOpt)$@
endif
		@echo "$@ done"

clean:
		@rm -f $(OBJS) core *Dict.*

distclean:      clean
		@rm -f $(PROGRAMS) *Dict.* *.def *.exp \
		   *.root *.ps *.so *.lib *.dll *.d *.log .def so_locations \
		   files/*
		@rm -rf cxx_repository

.SUFFIXES: .$(SrcSuf)

###
myProof.$(ObjSuf):	myProof.$(SrcSuf)
	$(CXX)  $(CXXFLAGS) -I$(TUTDIR) -c $<
