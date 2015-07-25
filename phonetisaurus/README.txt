README.txt

Josef Robert Novak
2012-10-15

#Phonetisaurus: a WFST-based G2P Conversion toolkit

#Phonetisaurus is released under the BSD-2 license.

#Phonetisaurus contains 2 pieces of 3rd-party code, which are both located in the src/3rdparty directory,
  ## google's sparsehash:
    ### http://code.google.com/p/sparsehash/
      which is released under the BSD-3 license
  ## UTF8-CPP:
    ### http://utfcpp.sourceforge.net/
      which is released under a BSD-like/compatible license 
      (see src/3rdparty/utfcpp/utf8.h header file for details)

# Phonetisaurus also relies on the OpenFst library
  ## http://www.openfst.org
  ## which is released under the Apache-2.0 license

# Please see the googlecode repository for tutorial information:
 ## http://code.google.com/p/phonetisaurus
 ## http://code.google.com/p/phonetisaurus/wiki/FSMNLPTutorial

# Instructions to build
  ## Configure openfst with ./configure --enable-far, then build and install : make && sudo make install
  ## Go to phonetisaurus/src and build with: make

