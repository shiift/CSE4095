CFLAGS=-pthread
CC=cc

all:  ex6 mcpi

ex6: ex6.c
	$(CC) $(CFLAGS) -o $@ $<

mcpi: mcpi.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o a.out ex3 ex6 mcpi

