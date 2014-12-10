CC=cc
CFLAGS=-g -pthread

all: ex3 ex4 ex3_fixed ex4_fixed

ex3: ex3.c
	$(CC) $(CFLAGS) -o $@ $<

ex3_fixed: ex3_fixed.c
	$(CC) $(CFLAGS) -o $@ $<

ex4: ex4.c
	$(CC) $(CFLAGS) -o $@ $<

ex4_fixed: ex4_fixed.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf ex3 ex4 ex3_fixed ex4_fixed *.o *~

