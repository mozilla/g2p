#!/bin/bash

#Align the dictionary
phonetisaurus-align \
    --input=g014a2.train \
    --ofile=g014a2/g014a2.corpus \
    --seq1_del=false

#Train a model
estimate-ngram \
    -t g014a2/g014a2.corpus \
    -o 7 \
    -s FixKN \
    -wl g014a2/g014a2.arpa

#Convert to FST format
phonetisaurus-arpa2wfst-omega \
    --lm=g014a2/g014a2.arpa \
    --ofile=g014a2/g014a2.fst

#Decode/Evaluate
phonetisaurus-calculateER-omega \
    --testfile g014a2.test \
    --modelfile g014a2/g014a2.fst \
    --prefix "g014a2/g014a2" \
    --decoder_type fst_phi