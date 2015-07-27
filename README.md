
## Steps

### Dependencies

0. A Linux or OS X environment
0. Install openfst from deps/ folder
0. Install phonetisaurus from root folder
0. Install srilm from deps/ folder
0. Install pocketsphinx (http://cmusphinx.sourceforge.net/wiki/tutorialpocketsphinx). Attention: since gecko-dev uses an outdated version of sphinxbase, this [1] specific commit should be used, otherwise the models generated will be incompatible with Gecko's sphinxbase and the models will fail to load
[1] https://github.com/cmusphinx/sphinxbase/tree/18aec4d11c5fc724a15f899bc1222bfcfe589def

### Generating the models
0. From inside dicts/ folder, execute gen_arpa.sh from each language you want arpa models to be build
1. The .dmp and lm.bin (for faster loading) binary files and its text version (model.arpa) are generated the language root folder
