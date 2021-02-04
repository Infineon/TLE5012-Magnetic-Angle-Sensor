#!/usr/bin/perl -w

# Run this from the Arduino library directory to generate keywords.txt
# Optionally pass the name of the library as the first argument

# $ gen_keywords.pl Foo > keywords.txt

use strict;
use warnings;
use Data::Dumper;

my $in_public = 0; 
my %class;
my %func;
my $curr_class;

my @h_files = glob('*.hpp');
print Dumper(\@h_files);

my $library_name = shift || "<LIBRARY_NAME>";

print <<EOF;
#######################################
# Syntax Coloring Map For $library_name
#######################################

EOF

for my $header (@h_files) {
    print Dumper($header);
    open(my $fh, $header) or die "Couldn't open $header: $!";

    while (<$fh>) { 
        if (/^class (\w+)/) {
            $class{$1}++; 
            $curr_class = $1;
        }
        if (/public:/) { 
            $in_public = 1;
        } 
        if ($in_public) { 
            if (/private:/ || /};/) { 
                $in_public = 0; 
            } elsif (/(\w+)\(/) { 
                if ($1 ne $curr_class) {
                    $func{$1}++;
                }
            } 
        }
    }
}

print <<EOF;
#######################################
# Datatypes (KEYWORD1)
#######################################

EOF

foreach (sort keys %class) {
    print "$_ KEYWORD1\n";
}

print <<EOF;

#######################################
# Methods and Functions (KEYWORD2)
#######################################

EOF

foreach (sort keys %func) {
    print "$_ KEYWORD2\n";
}
