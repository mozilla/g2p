# Makefile
#
# Copyright (c) [2012-], Josef Robert Novak
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
#  modification, are permitted #provided that the following conditions
#  are met:
#
#  * Redistributions of source code must retain the above copyright 
#    notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above 
#    copyright notice, this list of #conditions and the following 
#    disclaimer in the documentation and/or other materials provided 
#    with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
# OF THE POSSIBILITY OF SUCH DAMAGE.
CC=g++

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LIBS=-lfst -ldl -lm
endif
ifeq ($(UNAME), Linux)
LIBS=-lfst -ldl -lm -lrt
GCCVERSION=$(shell expr `g++ -dumpversion | cut -f1` \>= 4.6)
ifeq "$(GCCVERSION)" "1"
CC += -std=c++0x
endif
endif

OUT=../../bin/phonetisaurus-g2p ../../bin/phonetisaurus-align ../../bin/phonetisaurus-arpa2fst ../../bin/phonetisaurus-arpa2wfst-omega ../../bin/phonetisaurus-g2p-omega
TMP=*.o
CFLAGS ?= -O2
THIRD_PARTIES_INCLUDE ?= -I3rdparty/sparsehash -I3rdparty/utfcpp
EXTRA=$(CFLAGS) $(THIRD_PARTIES_INCLUDE) $(CXXFLAGS) $(CPPFLAGS) 

POBJS=Phonetisaurus.o FstPathFinder.o MBRDecoder.o LatticePruner.o util.o
MOBJS=M2MFstAligner.o FstPathFinder.o MBRDecoder.o LatticePruner.o util.o
OOBJS=PhonetisaurusOmega.o PhonetisaurusE2F.o util.o FstPathFinder.o LatticePruner.o MBRDecoder.o

all: $(OUT)

%.o: %.cpp
	$(CC) $(EXTRA) -c $(<) -o $(@)

../../bin/phonetisaurus-align: $(MOBJS) phonetisaurus-align.cpp
	$(CC) $(EXTRA) $(LDFLAGS) $(MOBJS) phonetisaurus-align.cpp -o ../../bin/phonetisaurus-align $(LIBS)

../../bin/phonetisaurus-g2p: $(POBJS) phonetisaurus-g2p.cpp
	$(CC) $(EXTRA) $(LDFLAGS) $(POBJS) phonetisaurus-g2p.cpp -o ../../bin/phonetisaurus-g2p $(LIBS)

../../bin/phonetisaurus-arpa2fst: Arpa2Fst.o util.o phonetisaurus-arpa2fst.cpp
	$(CC) $(EXTRA) $(LDFLAGS) Arpa2Fst.o util.o phonetisaurus-arpa2fst.cpp -o ../../bin/phonetisaurus-arpa2fst $(LIBS)

../../bin/phonetisaurus-arpa2wfst-omega: ARPA2WFST.o util.o phonetisaurus-arpa2wfst-omega.cpp
	$(CC) $(EXTRA) $(LDFLAGS) ARPA2WFST.o util.o phonetisaurus-arpa2wfst-omega.cpp -o ../../bin/phonetisaurus-arpa2wfst-omega $(LIBS)

../../bin/phonetisaurus-g2p-omega: $(OOBJS) phonetisaurus-g2p-omega.cpp
	$(CC) $(EXTRA) $(LDFLAGS) $(OOBJS) phonetisaurus-g2p-omega.cpp -o ../../bin/phonetisaurus-g2p-omega $(LIBS)

clean:
	$(RM) $(OUT) $(TMP)
