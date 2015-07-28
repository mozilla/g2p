#/bin/bash

../../bin/phonetisaurus-align --input=model.dic --ofile=model.corpus
estimate-ngram -s FixKN -o 3 -t model.corpus -wl model-unsorted.arpa
sphinx_lm_sort < model-unsorted.arpa > model.arpa
sphinx_lm_convert -ifmt arpa -i model.arpa -o model.dic.dmp
#sphinx_lm_convert -i model.dic.dmp -o model.lm.bin ##  Only works with lm trie sphinxbase version

rm model-unsorted.arpa
