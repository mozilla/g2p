#!/usr/bin/python
import re, os

def g014a2_test( printc=False, no_run=False, no_align=True ):
    print "Running g014a2 vanilla test...\n"

    #Make a directory for the models and evaluation results
    command = "mkdir -p models/g014a2"
    if printc:     
        print command
    if no_run==False: 
        os.system(command)

    #Run the aligner, if necessary
    if no_align==False:
        command = "phonetisaurus-align --input=data/g014a2.train --ofile=models/g014a2/g014a2.corpus"
        if printc: 
            print command
        if no_run==False: 
            os.system(command)
    
    #Train the model
    command = "estimate-ngram -t models/g014a2/g014a2.corpus -o 7 -s FixKN -wl models/g014a2/g014a2.arpa"
    if printc:
        print command
    if no_run==False:
        os.system(command)

    #Convert the model to Phonetisaurus WFST format
    command = "phonetisaurus-arpa2wfst-omega --lm=models/g014a2/g014a2.arpa --ofile=models/g014a2/g014a2.fst"
    if printc:
        print command
    if no_run==False:
        os.system(command)

    #Run the evaluation
    command = """phonetisaurus-calculateER-omega --testfile data/g014a2.test --modelfile models/g014a2/g014a2.fst --prefix "models/g014a2/g014a2" --decoder_type=fst_phi"""
    if printc:
        print command
    if no_run==False:
        os.system(command)
            
    return

tests = { "g014a2": g014a2_test }

if __name__=="__main__":
    import argparse, sys

    example = """$ run-test.py --test g014a2_mkn"""
    parser = argparse.ArgumentParser(description=example)
    parser.add_argument(
        '--test', '-t', 
        help="Test type to run.  To see all available tests, run --show_tests", 
        default="g014a2" 
        )
    parser.add_argument(
        '--show_tests', '-s',
        help="Show all available tests and quit.", 
        default=False, action="store_true",
        )
    parser.add_argument(
        '--print_commands', '-p',
        help="Print all commands to the console.",
        default=False, action="store_true",
        )
    parser.add_argument(
        '--no_run_commands', '-r',
        help="Don't run any commands. Use with '--print_commands' to just get a listing.",
        default=False, action="store_true",
        )
    parser.add_argument(
        '--no_align', '-a',
        help="Don't run the aligner.",
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

    if args.show_tests:
        print "Supported tests: g014a2:  Vanilla ngram test."
        sys.exit()

    if args.test in tests:
        tests[args.test](
            printc=args.print_commands, 
            no_run=args.no_run_commands,
            no_align=args.no_align
            )
    else:
        raise ValueError, "Test: %s doesn't exist!" % args.test
