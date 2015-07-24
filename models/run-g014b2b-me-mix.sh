#!/bin/bash

#Example of how to train a complementary max-ent model
# and linearly interpolate with the vanilla
# KN model from the baseline to quickly and easily
# get a very nice performance boost.
#
#These results and similar mixing stuff were not
# included in the paper due to lack of space.
#
#This just scratches the surface!

#NOTE1: This must be run AFTER running the 
#      basic run-g014b2b.sh script.

#NOTE2: Requires SRILM and the max-ent extension
# see: https://code.google.com/p/phonetisaurus/wiki/MaxEntModels

#Train the max-ent model from the aligned corpus
#Updated for compatibility with srilm-1.7.1 updates 
# to maxent interface
ngram-count \
    -text g014b2b/g014b2b.corpus \
    -lm g014b2b/g014b2b-me.arpa \
    -maxent \
    -order 8 \
    -maxent-convert-to-arpa

#Linearly interpolate with the baseline model
ngram \
    -order 8 \
    -mix-lm g014b2b/g014b2b-me.arpa \
    -lm g014b2b/g014b2b8.arpa \
    -write-lm g014b2b/g014b2b-mix.arpa \
    -lambda .5

#Convert the new interpolate model to FST format
phonetisaurus-arpa2wfst-omega \
    --lm=g014b2b/g014b2b-mix.arpa \
    --ofile=g014b2b/g014b2b-mix.fst

#Evaluate the result - note the nice boost
phonetisaurus-calculateER-omega \
    --testfile g014b2b.test \
    --modelfile g014b2b/g014b2b-mix.fst \
    --prefix "g014b2b/g014b2b-mix" \
    --decoder_type fst_phi
