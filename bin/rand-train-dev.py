#!/usr/bin/python
import random, re
from collections import defaultdict

def get_word( line ):
    chunks = re.split(r"\s+",line)
    word = ""
    for c in chunks:
        c = re.sub(r"\}.*","",c)
        c = re.sub(r"\|","",c)
        if not c=="_":
            word += c
    return word

def rand_train_dev( ifile, dev_perc=5.0, prefix="test", corpus=False ):
    dev_perc = dev_perc/100.
    items = defaultdict(list)

    for line in open(ifile,"r"):
        line = line.strip()
        if corpus==True:
            word = get_word(line)
            items[word].append(line)
        else:
            word,pron = re.split(r"\t",line)
            items[word].append(pron)
    item_list = [ tuple([key,val]) for key,val in items.iteritems() ]

    random.shuffle(item_list)
    d_num = int(len(item_list)*dev_perc)
    t_num = len(item_list)-d_num

    ofd = open("%s.dev"%(prefix),"w")
    oft = open("%s.train"%(prefix),"w")
    for i,item in enumerate(item_list):
        if i<d_num:
            for pron in item[1]:
                if corpus:
                    ofd.write("%s\n" % (pron))
                else:
                    ofd.write("%s\t%s\n" % (item[0],pron))
        else:
            for pron in item[1]:
                if corpus:
                    oft.write("%s\n" % (pron))
                else:
                    oft.write("%s\t%s\n" % (item[0],pron))
    ofd.close()
    oft.close()
    return
    


if __name__=="__main__":
    import sys, argparse

    example = "rand-train-dev.py --dev_perc 5 --ifile g014a2.train --prefix g014a2-1"
    parser = argparse.ArgumentParser(description=example)

    parser.add_argument(
        '--ifile', '-i',
        help="Input file to be split",
        required=True,
        )
    parser.add_argument(
        '--prefix', '-p',
        help="File output prefix",
        required=False, default="test",
        )
    parser.add_argument(
        '--dev_perc', '-d',
        help="Percentage of file to select for dev set.",
        type=float, default=5.0,
        )
    parser.add_argument(
        '--corpus', '-c',
        help="The input is an aligned corpus, not a dictionary.",
        default=False, action="store_true",
        )
    parser.add_argument(
        '--verbose', '-v',
        help="Verbose mode.",
        default=False, action="store_true",
        )
    args = parser.parse_args( )
    if args.verbose:
        for attr, value in args.__dict__.iteritems():
            print attr,"=",value

    rand_train_dev( 
        ifile=args.ifile, 
        dev_perc=args.dev_perc,
        prefix=args.prefix,
        corpus=args.corpus
        )


