CFLAGS=-g
CC=cc

all: ex1 ex2 ex3

ex1: ex1.o
	$(CC) $(LFLAGS) -o $@ $<

ex1.o: ex1.c
	$(CC) $(CFLAGS) -c $<

ex2: ex2.o
	$(CC) $(LFLAGS) -o $@ $<

ex2.o: ex2.c
	$(CC) $(CFLAGS) -c $<

ex3: ex3.o
	$(CC) $(LFLAGS) -o $@ $<

ex3.o: ex3.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *~ ex1 ex2 ex3

