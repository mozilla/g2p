README.txt
Josef Robert Novak

UPDATE: 2014-06-18
Minor bugfixes:  
  * Updated MaxEnt example to be compatible
    with the latest version of srilm (1.7.1)
  * Fixed -std=c++0x requirement for Linux g++ v > 4.6
     (thanks to MatsRooth for pointing it out)

This is Relase 0.7.8
It is essentially a vanilla copy of the InterSpeech2013 distribution.
If you have already downloaded that, then there is no need to download
this.  This release was created primarily to provide continuity between 
this and the currently-broken compatibility with the repository trunk,
which now includes a variety of additional tools and bindings.

This distribution includes all the basic software and test/train sets
required to duplicate the results from the paper.

It also includes a small easter egg in the form of an example using 
the very nice max-ent SRILM extension.

A copy of the phonetisaurus distribution is included.
In general you can use any LM training toolkit you like to 
train the joint n-gram lm from an aligned dictionary.
The below examples illustrate specific use cases for a variety 
of popular LM training toolkits, and hence incur several 
additional dependencies.

DEPENDENCIES
OpenFst 1.3.+  
  www.openfst.org 
  Required for phonetisaurus

mitlm          
  https://code.google.com/p/mitlm/
  Used for the g014a2 example to train the LM.
  Required if you want to run the run-g014a2.sh example.

ngramlibrary
  http://www.openfst.org/twiki/bin/view/GRM/NGramLibrary
  Used for the g014b2b example to train the LM.
  This embodies an entirely FST-based approach.
  Required if you want to run the run-g014b2b.sh example.

srilm + max-ent extension
  http://www.speech.sri.com/projects/srilm/  (base distribution)
  http://www.phon.ioc.ee/dokuwiki/doku.php?id=people:tanel:srilm-me.en  (max-ent extension)
  Used for the easter-egg illustrating model combination with max-ent models.
  Required if you want to run the run-g014b2b-me-mix.sh script.  Highly recommended!

SETUP and TESTING
  To setup the distribution first add the local .bin directory to your path:
  $ cd bin
  $ export PATH=`pwd`:${PATH}

  Next compile phonetisaurus (make sure OpenFst is installed):
  $ cd ../phonetisaurus/src
  $ make
  $ cd ../../

  Next install whatever of the above-mentioned LM training libraries you want/need

  Now try running the basic nettalk test (uses mitlm):
  $ cd models
  $ ./run-g014a2.sh

  And/or try running the basic cmudict test (uses ngramlibrary):
  $ ./run-g014b2b.sh

  If you installed the srilm tools and max-ent extension try this and compare the 
  results to the vanilla run-g014b2b.sh script.
  $ ./run-g014b2b-me-mix.sh

Enjoy!

  
