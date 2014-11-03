CFLAGS=-pthread
CC=cc

all: ex3 ex6 mcpi

ex3: ex3.c
	$(CC) $(CFLAGS) -o $@ $<

ex6: ex6.c
	$(CC) $(CFLAGS) -o $@ $<

mcpi: mcpi.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o a.out ex3 ex6 mcpi

