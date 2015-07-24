/*
 phonetisaurus-arpa2fst.cpp

 Copyright (c) [2012-], Josef Robert Novak
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
  modification, are permitted #provided that the following conditions
  are met:

  * Redistributions of source code must retain the above copyright 
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above 
    copyright notice, this list of #conditions and the following 
    disclaimer in the documentation and/or other materials provided 
    with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#include "Arpa2Fst.hpp"

DEFINE_string( input,         "", "Input ARPA-format LM." );
DEFINE_string( eps,      "<eps>", "Epsilon symbol." );
DEFINE_string( phi,      "<phi>", "Optional Phi (failure) symbol (not currently in use)." );
DEFINE_string( split,        "|", "Delimiter used to split mult-token symbols." );
DEFINE_string( start,  "<start>", "Start symbol." );
DEFINE_string( sb,         "<s>", "Sentence begin symbol." );
DEFINE_string( se,        "</s>", "Sentence end symbol." );
DEFINE_string( delim,        "}", "Delimiter used to separate input and output tokens." );
DEFINE_string( prefix,    "test", "Output filename prefix." );
DEFINE_string( null_sep,     "_", "Graphemic null symbol." );
DEFINE_bool(   write_syms, false, "Write the symbol tables to disk." );


int main( int argc, char* argv[] ) {
  string usage = "phonetisaurus-arpa2fst ARPA LM to FST conversion tool.\n\n Usage: ";
  set_new_handler(FailedNewHandler);
  SetFlags(usage.c_str(), &argc, &argv, false );

  Arpa2OpenFST converter( 
			 FLAGS_input, FLAGS_eps, FLAGS_phi, FLAGS_split, 
			 FLAGS_start, FLAGS_sb, FLAGS_se, FLAGS_delim, FLAGS_null_sep
			  );

  converter.generateFST( );
  converter.arpafst.SetInputSymbols(converter.isyms);
  converter.arpafst.SetOutputSymbols(converter.osyms);

  ArcSort( &converter.arpafst, ILabelCompare<StdArc>() );
  converter.arpafst.Write(FLAGS_prefix+".fst");

  if( FLAGS_write_syms ){
    converter.ssyms->WriteText(FLAGS_prefix+".ssyms");
    converter.isyms->WriteText(FLAGS_prefix+".isyms");
    converter.osyms->WriteText(FLAGS_prefix+".osyms");
  }

  return 0;
}
