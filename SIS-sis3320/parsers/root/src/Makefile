# Makefile for ReadSIS3302 parser
# by Micah Folsom 8/24/2013

CC = g++
CCFLAGS = -O3 -Wall -std=c++0x
ROOTLIB := $(shell root-config --glibs)
INC := $(shell root-config --incdir)

EXE = SIS3302ToROOT

all: $(EXE)

SIS3302ToROOT: main/main.cpp ReadSIS3302.cpp
	$(CC) $(CCFLAGS) -o $@ $^ -I$(INC) ReadSIS3302.hpp $(ROOTLIB)
	mv $@ ../bin/

clean:
	rm ../bin/$(EXE)
