
## Steps

### Dependencies

0. A Linux or OS X environment
0. Install openfst from deps/ folder
0. Install phonetisaurus from root folder
0. Install srilm from deps/ folder

#### Install Pocketsphinx (attention to sphinxbase version)
0. Instructions: http://cmusphinx.sourceforge.net/wiki/tutorialpocketsphinx
0. Sphinxbase: Since gecko-dev uses an outdated version of sphinxbase, this specific commit (https://github.com/cmusphinx/sphinxbase/tree/18aec4d11c5fc724a15f899bc1222bfcfe589def) should be used, otherwise the models generated will be incompatible with Gecko's current sphinxbase implementation and will fail to load  
0. Pocketsphinx: Install from master https://github.com/cmusphinx/pocketsphinx/


### Generating the models
0. From inside dicts/ folder, execute gen_arpa.sh from each language you want arpa models to be build
1. The .dmp and lm.bin (for faster loading) binary files and its text version (model.arpa) are generated the language root folder
