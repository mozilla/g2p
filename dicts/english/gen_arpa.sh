#/bin/bash

../../bin/phonetisaurus-align --input=model.dic --ofile=model.corpus
../../deps/srilm/bin/i686-m64/ngram-count -text model.corpus -lm model-unsorted.arpa
sphinx_lm_sort < model-unsorted.arpa > model.arpa
sphinx_lm_convert -ifmt arpa -i model.arpa -o model.dic.dmp
#sphinx_lm_convert -i model.dic.dmp -o model.lm.bin ##  Only works with lm trie sphinxbase version

rm model-unsorted.arpa
