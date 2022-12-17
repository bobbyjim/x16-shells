use strict;
#
#  Writes the disclaimer to a binary file.
#

#
#  We don't currently write the logo, but we could.
#
my @logo = (
    [],
    [0x9a, 18,  169, 32,  32, 0x1e], 
    [0x9a, 18,  32,  146, 32,  32,  18,   32,  146, 169, 0x1e], 
    [0x9a, 18,  32,  146, 32,  32,  0x1c, 18,  163, 223, 0x1e], 
    [0x9a, 146, 223, 18,  32,  32,  146, 0x1e],
    []
);

my @disclaimer = (
'  **************************************************************************** ',
'         not a warning!  all are welcome to access this system; there are no   ',
'         penalties, nor any system security policy,  and no applicable state   ',
'         or federal laws. sessions & e-mail are not monitored, as the system   ', 
'         has neither.     * * * note: system will be down if it is shut off.   ',
'  **************************************************************************** '
);

open my $out, '>:raw', 'DISCLAIM.BIN';
print $out pack 'xx';
foreach my $row (@disclaimer)
{
   #my $disc_row = shift @disclaimer;
   #print $out pack 'C*', @$rowref;
   print $out pack 'A*', $row;
   print $out pack 'x';
}
close $out;
