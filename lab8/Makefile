SRCS=main.c tree.c dico.c spell.c

# This should be modified on a Windows O.S. to reflect the right extension.
OFILES= main.o tree.o dico.o spell.o

# Names of the compiler  / linker
CC=cc
LD=cc
# The 'CFLAGS' is a Makefile variable holding the arguments to the compiler. 
# In this case, we ask the compiler to 
# (1) only compile, not link (-c)
# (2) generate debug information (-g)
# Similarly, the 'LFLAGS' is a variable holding options for the linker and we
# ask to include debug information.

CFLAGS=-c -g -pthread
LFLAGS=-g -pthread 

all: spellCheck
	@echo "Done!"

spellCheck: $(OFILES)
	$(CC) $(LFLAGS) $(OFILES) -o $@

main.o : main.c
	$(CC) $(CFLAGS) $< -o $@

tree.o : tree.c
	$(CC) $(CFLAGS) $< -o $@

dico.o : dico.c
	$(CC) $(CFLAGS) $< -o $@
spell.o : spell.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OFILES) spellCheck
