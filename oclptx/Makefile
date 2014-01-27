# NOTE
# Based off of Makefile of ptx2
#
# -std=c++0x is required for using <chrono>, for benchmarking
#

include $(FSLCONFDIR)/default.mk

# IMPORTANT
#
# Make sure following enviroment variables set
# $OCLDIR (cl.h/cl.hpp location)
# $OCLLIBDIR (libOpenCl.so location)
#
# IMPORTANT

PROJNAME = fdt

#OPTFLAGS = -ggdb

#ARCHFLAGS = -arch i386
#ARCHLDFLAGS = -arch i386

ifeq ($(FSLMACHTYPE),apple-darwin8-gcc4.0)
        ARCHFLAGS =  -arch i386 -isysroot /Developer/SDKs/MacOSX10.4u.sdk -I/usr/X11R6/include/
        ARCHLDFLAGS = -Wl,-search_paths_first -arch i386 -isysroot /Developer/SDKs/MacOSX10.4u.sdk -L/Developer/SDKs/MacOSX10.4u.sdk/usr/X11R6/lib/ 
endif 

#figure out how to just use gcc w/ their c++ flags
GPP=g++

# to be included when compiling any executables making use of ocl runtime
OCLLDFLAGS= -L/opt/AMD-APP-SDK-v2.8-RC-lnx64/lib/x86_64 -lOpenCL
# one or the other
OCLCFLAGS=  ${CXXFLAGS} -fPIC -I/opt/AMD-APP-SDK-v2.8-RC-lnx64/include -std=c++0x
#OCLCFLAGS=  ${CXXFLAGS} -fPIC -I/usr/local/cuda/include -std=c++0x -g

OCLPTX=oclptx
OCLPTXOBJ = oclptx.o oclptxhandler.o
OCLPTXSHOBJ = oclptx.so

XFILES = oclptx

all: ${XFILES} 

${OCLPTX}:
		$(GPP) $(OCLCFLAGS) -o oclptx.o -c -fPIC oclptx.cc
		$(GPP) $(OCLCFLAGS) -o oclptxhandler.o -c -fPIC oclptxhandler.cc
		$(GPP) $(OCLCFLAGS) -Wall -shared -o $(OCLPTXSHOBJ) $(OCLPTXOBJ)
		$(GPP) $(OCLPTXSHOBJ) -o $(OCLPTX) -g $(OCLLDFLAGS)
		

clean:
		rm $(OCLPTXOBJ) $(XFILES)
