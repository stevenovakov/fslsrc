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
OCLLDFLAGS= -L/usr/lib -lOpenCL
OCLCFLAGS= -I/usr/local/cuda/include -I/opt/AMD-APP-SDK*/include -lpthread



OCLPTX=oclptx
OCLPTXOBJ = oclptx.o oclptxhandler.o
OCLPTXSHOBJ = oclptx.so

XFILES = oclptx

all: ${XFILES} 

#
#STEVE TODO
#	I can't figure out how to incorporate their make syntax, it just 
#	does not work for me. Maybe Jeff should take a look at this.
#

${OCLPTX}:
		$(GPP) $(OCLCFLAGS) -o oclptx.o -c -fPIC oclptx.cc
		$(GPP) $(OCLCFLAGS) -o oclptxhandler.o -c -fPIC oclptxhandler.cc
		$(GPP) $(OCLCFLAGS) -Wall -shared -o $(OCLPTXSHOBJ) $(OCLPTXOBJ)
		$(GPP) $(OCLPTXSHOBJ) -o $(OCLPTX) -g $(OCLLDFLAGS)

clean:
		rm $(OCLPTXOBJ) $(OCLPTXSHOBJ) $(XFILES)



#FIXING COMPATIBILITY ISSUES (FROM THE MIND OF JEFF TAYLOR):
#The quickest solution I can think of would be to add two rules:

#oclptx.o: oclptx.cc oclptx.h
#<tab>$(CPP) <your desired options> -o $@ $^

#oclptxhandler.o: oclptxhandler.cc oclptxhandler.h
#<tab>$(CPP) <your desired options> -o $@ $^

#A few notes:
 #- The tab must be a tab (no number of spaces will do).  You should only have one tab.  I don't know why FSL's files include a bunch.  Ignore them.
 #- $@ expands to the target ("oclptx.o",etc).  @^ expands to its dependency list ("oclptx.cc oclptx.h" or the other)
 #- $(VARIABLE) expands to that variable (text substitution).  I've never seen the squiggly braces, but I guess they work. :/
#EOF