#!/bin/bash

for gtool in ngramsymbols farcompilestrings ngramcount ngrammake ngramprint
do
    if ! hash ${gtool} 2>/dev/null; then
	echo "Couldn't find ${gtool}!  Is Google NGramLibrary installed?"
	echo "Google NGramLibrary is required for the run-g014b2b.sh example."
	echo ""
    fi
done

if ! hash estimate-ngram 2>/dev/null; then
    echo "Couldn't find estimate-ngram!  Did you install mitlm?"
    echo "estimate-ngram is required for the run-g014a2.sh script."
    echo ""
fi

if ! hash ngram-count 2>/dev/null; then
    echo "Couldn't find ngram-count! Did you install srilm?"
    echo "Did you add the max-ent patch?"
    echo "ngram-count is required for the max-ent example."
    echo ""
fi

if ! hash ngram 2>/dev/null; then
    echo "Couldn't find ngram! Did you install srilm?"
    echo "Did you add the max-ent patch?"
    echo "ngram-count is required for the max-ent example."
    echo ""
fi

for ptool in phonetisaurus-g2p-omega phonetisaurus-align phonetisaurus-arpa2wfst-omega 
do
    if ! hash ${ptool} 2>/dev/null; then
	echo "Couldn't find ${ptool}!"
	echo "Did you run make in phonetisaurus/src?"
	echo "Did you add ./bin to your PATH?"
	echo ""
    fi
done
