SOURCES = main.c chunk.c debug.c memory.c value.c vm.c compiler.c scanner.c

PROGRAM = x16perl

CC65_TARGET = cx16

CC	= cl65
CFLAGS 	= -t $(CC65_TARGET) --create-dep $(<:.c=.d) -O
LDFLAGS	= -t $(CC65_TARGET) -m $(PROGRAM).map
OBJDIR  = .obj

#############################################
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

.SUFFIXES: 
all: $(PROGRAM)

ifneq (($MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

clean:
	$(RM) $(OBJECTS) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map

.PHONY: all clean

$(PROGRAM): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJECTS): $(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<


