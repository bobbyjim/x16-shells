

my $source = shift || die "SYNOPSIS: $0 <input chargen file>\n";
open my $in,  '<:raw', $source or die "SYNOPSIS: $0 <input chargen file>\n";
open my $out, '>:raw', 'CHARGEN.BIN'or die "SYNOPSIS: $0 <input chargen file>\n";

my $buffer;

read $in, $buffer, 4096;

print $out pack('xx');
print $out $buffer;

close $out;
close $in;

