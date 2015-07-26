#!/usr/local/bin/perl

 open (MYFILE, 'model-incomplete.arpa');
 $trigramarea = 0;
 while (<MYFILE>) {
 	chomp;
#	print "$_";
#	$valor = $_;
#	print $valor;
	my @values = split("	",$_);
	
	if ($values[1] ne ""){
		
		if ($values[0] eq "\\3-grams:"){
			$trigramarea = 1;
		}
	
		if ($trigramarea == "0"){
			$weight = $values[2];
			if ($values[2] eq ""){
				$weight = "0.0000";
			}
		 	print $values[0] . "	"  . $values[1] . "	"  .  $weight . "\n" ;
		} else {
		 	print $values[0] . "	"  . $values[1] . "	"  . $values[2] . "	" . "\n" ;
		}
	} else {
		print $values[0] . "	"  . $values[1] . "	"  . $values[2] . "	" . "\n" ;
	}
 }
 close (MYFILE)
