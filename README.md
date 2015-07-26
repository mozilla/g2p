
## Steps

### Dependencies

0. A Linux or OS X environment
0. Install openfst from deps/ folder
0. Install phonetisaurus from root folder
0. Install srilm from deps/ folder
0. Install pocketsphinx (http://cmusphinx.sourceforge.net/wiki/tutorialpocketsphinx)

### Generating the models
0. From inside dicts/ folder, execute gen_arpa.sh from each language you want arpa models to be build
1. The .dmp and lm.bin (for faster loading) binary files and its text version (model.arpa) are generated the language root folder
