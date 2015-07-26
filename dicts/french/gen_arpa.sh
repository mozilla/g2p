#/bin/bash

../../bin/phonetisaurus-align --input=model.dic --ofile=model.corpus
../../deps/srilm/bin/i686-m64/ngram-count -text model.corpus -lm model-incomplete.arpa
perl normalize.pl > model.arpa
sphinx_lm_convert -ifmt arpa -i model.arpa -o model.dic.dmp
sphinx_lm_convert -i model.dic.dmp -o model.lm.bin

rm model.corpus
rm model-incomplete.arpa
