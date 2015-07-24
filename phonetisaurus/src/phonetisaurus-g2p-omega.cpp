#include <fst/fstlib.h>
#include "PhonetisaurusOmega.hpp"
#include "FstPathFinder.hpp"
#include "util.hpp"
using namespace fst;

void phoneticize_word( PhonetisaurusOmega* _decoder, 
		       string _input, string _sep, bool _words, bool _scores, FstPathFinder* p
		       ){
  /*
    Phoneticize a single word.  Most of this process is automated.
  */

  vector<string>    tokens = tokenize_entry( &_input, &_sep, &_decoder->isyms );
  VectorFst<StdArc> pfsa   = _decoder->phoneticize( &tokens );
  p->extract_all_paths( pfsa );
  for( size_t i=0; i<p->paths.size(); i++ ){
    if( i>=_decoder->nbest )
      break;
    cout << _input << "\t" << p->paths[i].cost << "\t";
    for( size_t j=0; j<p->paths[i].path.size(); j++ ){
      string c = pfsa.InputSymbols()->Find(p->paths[i].path[j]);
      replace(c.begin(), c.end(), *_decoder->tie.c_str(), ' ');
      cout << c;
      if( j != p->paths[i].path.size()-1 )
	cout << " ";
    }
    cout << endl;
  }

  p->paths.clear();

  return;
}

void phoneticize_file( PhonetisaurusOmega* _decoder, string _input, string _sep, 
		       bool _words, bool _scores, FstPathFinder* p, int verbose ){
  ifstream test_fp;
  test_fp.open( _input.c_str() );
  string line;
  string delim = "\t";
  timespec start, end, elapsed;
  double entries = 0.;
  double nelapsed = 0.;

  if( test_fp.is_open() ){
    while( test_fp.good() ){
      getline( test_fp, line );
      if( line.compare(" ")==0 || line.compare("")==0 )
	continue;
      
      vector<string> parts  = tokenize_utf8_string( &line, &delim );
      if( verbose > 0 )
	start = get_time( );
      phoneticize_word( _decoder, parts.at(0), _sep, _words, _scores, p );
      if( verbose > 0 ){
	end = get_time( );
	elapsed = diff( start, end );
	nelapsed += elapsed.tv_nsec;
	entries += 1.;
      }
    }
    test_fp.close();
    if( verbose > 0 )
      cerr << "Total time (sec): " << nelapsed/1000000./1000. << " Total # entries: " << entries \
	   << " Avg time (msec): " << nelapsed/entries/1000000 << endl;
  }else{
    cout << "Problem opening test file..." << endl;
  }
 
  return;
}


DEFINE_string( model,   "",    "The input WFST G2P model, in compact format. REQUIRED" );
DEFINE_string( input,   "",    "The input word or test file. REQUIRED" );
DEFINE_string( sep,     "",    "The separator substring for input words. Default=''" );
DEFINE_string( far_suf, "far", "NOT IMPLEMENTED. The suffix to append to the output .far archive. Default='far'" );
DEFINE_bool  ( isfile,  false, "--input is a file. Default=false" );
DEFINE_string( decoder_type,   "fsa_eps", "Decoding type.  Must be one of 'fst_phi', 'fsa_phi', or 'fsa_eps'.");
DEFINE_bool  ( words,   true,  "Show the input words in the output. Default=true" );
DEFINE_bool  ( scores,  true,  "Show the final scores for the pronunciation hypotheses. Default=true" ); 
DEFINE_bool  ( map,     false, "Use the Maximum A-Posteriori (MAP) decoder. Default=false" );
DEFINE_bool  ( lmbr,    false, "Use the Lattice Minimum-Bayes Risk (LMBR) decoder. Default=false" );
DEFINE_bool  ( logopt,  false, "Optimize the result in the log semiring." );
DEFINE_bool  ( infar,   false, "NOT IMPLEMENTED. The input file is a .far archive.  Default=false" );
DEFINE_bool  ( allow_ins,   false, "Allow phoneme insertions when building the input FSA." );
DEFINE_bool  ( outfar,  false, "NOT IMPLEMENTED. The result should be output as a .far archive.  Default=false" );
DEFINE_int32 ( beam,    -1,   "Beam width to use during pruning (this is a bit hacky). Default=-1 (full lattice)" );
DEFINE_int32 ( nbest,   1,     "Show the n-best pronunciation hypotheses. Default=1" );
DEFINE_int32 ( order,   6,     "LMBR maximum N-gram order. Default=6" );
DEFINE_double( alpha,   0.6,   "LMBR alhpa LM scale factor. Default=0.6" );
DEFINE_double( prec,    0.85,  "LMBR precision factor.  Default=0.85" );
DEFINE_double( ratio,   0.72,  "LMBR ratio factor. Default=0.72" );
DEFINE_string( omodel,    "", "Write the (possibly modified) model out to file 'omodel', if specified." );
DEFINE_double( thresh, 100.0,  "Define a pruning threshold. Useful for n-best if you only want n-best that are 'close' to the 1-best result." );
DEFINE_int32 ( verbose, 1,     "Verbosity level.  Higher is more verbose. Default=1" );

int main( int argc, char** argv ){

  string usage = "phonetisaurus-g2p-omega decoder.\n\n Usage: ";
  set_new_handler(FailedNewHandler);
  SetFlags(usage.c_str(), &argc, &argv, false);
  if( FLAGS_model.compare("")==0 || FLAGS_input.compare("")==0 ){
    cout << "Both --model, and --input must be set!" << endl;
    exit(1);
  }

  PhonetisaurusOmega* decoder = new PhonetisaurusOmega( 
		     FLAGS_model.c_str(), FLAGS_decoder_type, FLAGS_logopt, FLAGS_beam, 
		     FLAGS_nbest, FLAGS_lmbr, FLAGS_order, FLAGS_alpha,
		     FLAGS_prec, FLAGS_ratio, FLAGS_verbose, FLAGS_allow_ins, FLAGS_thresh
		    );
  set<int> skips;
  skips.insert(0);
  skips.insert(1);
  skips.insert(2);
  FstPathFinder* p = new FstPathFinder( skips );
  if( FLAGS_isfile==true )
    phoneticize_file( decoder, FLAGS_input, FLAGS_sep, FLAGS_words, FLAGS_scores, p, FLAGS_verbose );
  else
    phoneticize_word( decoder, FLAGS_input, FLAGS_sep, FLAGS_words, FLAGS_scores, p );

  if( FLAGS_omodel.compare("")!=0 ){
    if( FLAGS_decoder_type.compare("fst_phi")==0 ){
      Decode(decoder->g2pmodel, *decoder->encoder);
      decoder->g2pmodel->SetInputSymbols(&decoder->isyms);
      decoder->g2pmodel->SetOutputSymbols(&decoder->osyms);
    }
    decoder->g2pmodel->Write(FLAGS_omodel);
  }

  delete p;
  return 0;
}
