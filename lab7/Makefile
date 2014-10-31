# Makefile Copyright 2008 Groetker, Holtmann, Keding, Wloka

# clean

CLEAN_TARGETS = *.o *.stackdump a.out

CLEAN_TARGETS_EDIT = *~ *.bak

all: beancounter beancounter_printf beancounter_assert ex1

beancounter: beancounter.c
	gcc -Wall -g -c beancounter.c
	gcc -o beancounter beancounter.o -lpthread

beancounter_printf: beancounter_printf.c
	gcc -Wall -g -c beancounter_printf.c
	gcc -o beancounter_printf beancounter_printf.o -lpthread

beancounter_assert: beancounter_assert.c
	gcc -DDEBUG -Wall -g -c beancounter_assert.c
	gcc -o beancounter_assert beancounter_assert.o -lpthread

ex1: ex1.c
	gcc -Wall -g -c ex1.c
	gcc -o ex1 ex1.o -lpthread

clean:
	rm -rf $(CLEAN_TARGETS) beancounter beancounter_printf beancounter_assert ex1
