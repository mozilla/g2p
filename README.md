
## Steps

### Dependencies

0. C++11 with TR1 for opemfst is required;
0. A Linux or OS X environment
0. Install openfst from deps/ folder (configure with --enable-far)
0. Install phonetisaurus from root folder
0. Install mitlm from deps/ folder

#### Install Sphinxbase (attention to sphinxbase version)
0. Sphinxbase: Since gecko-dev uses an outdated version of sphinxbase, this specific commit (https://github.com/cmusphinx/sphinxbase/tree/18aec4d11c5fc724a15f899bc1222bfcfe589def) should be used, otherwise generated models will be incompatible with Gecko's sphinxbase and will fail to load. Build with traditional ./configure && make && make install   


### Generating the models
0. From inside dicts/ folder, execute gen_arpa.sh from each language you want arpa models to be build
1. The .dmp and lm.bin (for faster loading) binary files and its text version (model.arpa) are generated the language root folder
