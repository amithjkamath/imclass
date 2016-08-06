# Copyright 2005-2016 Intel Corporation.  All Rights Reserved.
#
# The source code contained or described herein and all documents related
# to the source code ("Material") are owned by Intel Corporation or its
# suppliers or licensors.  Title to the Material remains with Intel
# Corporation or its suppliers and licensors.  The Material is protected
# by worldwide copyright laws and treaty provisions.  No part of the
# Material may be used, copied, reproduced, modified, published, uploaded,
# posted, transmitted, distributed, or disclosed in any way without
# Intel's prior express written permission.
#
# No license under any patent, copyright, trade secret or other
# intellectual property right is granted to or conferred upon you by
# disclosure or delivery of the Materials, either expressly, by
# implication, inducement, estoppel or otherwise.  Any license under such
# intellectual property rights must be express and approved by Intel in
# writing.

# GNU Makefile that builds and runs example.
NAME=ipp_blur_rotate
ARGS=auto
PERF_RUN_ARGS=auto 1 1000000 silent
LIGHT_ARGS=auto 1 1000

# The C++ compiler
ifneq (,$(shell which icc 2>/dev/null))
CXX=icc
endif # icc

ifeq ($(shell uname), Linux)
LIBS+= -lrt
endif

GUIFOLDER=./src/gui

include $(GUIFOLDER)/Makefile.gmake

LIBS+= -L/opt/intel/ipp/lib

INC=-I/opt/intel/ipp/include

SOURCES= $(GUIFOLDER)/$(UI)video.cpp ./src/bmpreader.cpp ./src/ipp_blur_rotate.cpp ./src/main.cpp

override CXXFLAGS += $(UI_CXXFLAGS)

all:	release

resources:
ifeq ($(UI),mac)
	mkdir -p $(APPRES)/en.lproj $(NAME).app/Contents/MacOS
	cp $(GUIFOLDER)/xcode/guiExample/Info.plist $(NAME).app/Contents
	cp $(GUIFOLDER)/xcode/guiExample/PkgInfo $(NAME).app/Contents
	cp $(GUIFOLDER)/xcode/guiExample/en.lproj/* $(APPRES)/en.lproj
endif # OS X*

release: $(SOURCES) resources
ifeq ($(UI),mac)
	$(CXX_UI) -O2 -DNDEBUG $(CXXFLAGS) -c $(MACUISOURCES)
endif # OS X*
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $(EXE) $(INC) $(SOURCES) $(MACUIOBJS) -lippcore -lippvm -lippi -lipps $(LIBS)

debug: resources
ifeq ($(UI),mac)
	$(CXX_UI) -g -O0 $(CXXFLAGS) -c $(MACUISOURCES)
endif # OS X*
	$(CXX) -g -O0 $(CXXFLAGS) -o $(EXE) $(INC) $(SOURCES) $(MACUIOBJS) -lippcore -lippvm -lippi -lipps $(LIBS)

clean:
	$(RM) $(EXE) *.o *.d
ifeq ($(UI),mac)
	rm -rf $(NAME).app
endif

run:
	echo $(EXE) $(ARGS)
	@PATH=.:$(PATH) $(run_cmd) $(EXE) $(ARGS)
