# SCAN-8
A tokenizer for 8 bit systems.

# Building
The makefile uses CC65, and the source code uses a few pieces of the
cx16.h library for the Commander X16's RAM banking. The source can
be easily repurposed to other architectures.

The shell script 'x16' runs the Commander X16 emulator with the
SCAN8 binary.

# How it works
It's a fairly boring line tokenizer, with one caveat: the source
data is read from one memory bank, and the token stream is written 
to another.

Thankfully, banking is only used in a few places, so modification
is not difficult: just remove the bank assigments and set the output
address to whatever you need.

# Tokens
Each token is 5 bytes, which includes a pointer back into the source
for string data.  The original source is preserved: the length of the
referenced string is also stored.  This gives us better control than
relying on null-termination.

256 tokens are supported, with the top 32 reserved for tokenizer 
errors.
