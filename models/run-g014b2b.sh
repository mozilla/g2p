#!/bin/bash

#Align the corpus with reasonable params
phonetisaurus-align \
    --input=g014b2b.train \
    --ofile=g014b2b/g014b2b.corpus \
    --seq1_del=false

#Use the google ngramlibrary to 
# train a model
train-ngramlibrary.py \
    --prefix "g014b2b/g014b2b" \
    --order 8 \
    --bins 3

#Evaluate the corpus
phonetisaurus-calculateER-omega \
    --testfile g014b2b.test \
    --modelfile g014b2b/g014b2b8.fst \
    --prefix "g014b2b/g014b2b8" \
    --decoder_type fst_phi
