
$/ = undef;

open my $fp, '<', 'FORTUNE.YML';
my @lines = split '---', <$fp>;
close $fp;

shift @lines;  # discard first
pop @lines;    # discard last

open my $op, '>', 'FORTUNE.BIN';
print $op pack 'xx';              # initial two bytes

# initial 32 bytes
print $op pack 'A15', 'FORTUNE';  # header
print $op pack 'x';
print $op pack 'C', 63;           # count of fortunes + 1 (for modding)
print $op pack 'x15';             # unused

# remaning 7.8k bytes
foreach(@lines)
{
   print $op pack 'A*', uc $_; # the fortune
   print $op pack 'x';         # string terminator and fortune boundary

   print $_;
}

print $op pack 'x16';         # end of fortune

close $op;
