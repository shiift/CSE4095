CFLAGS=-g
CC=cc

all: valgr1 valgr2

valgr1: valgr1.o
	$(CC) $(CFLAGS) -o $@ $<

valgr2: valgr2.o
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.c 
	$(CC) -c $(CFLAGS) $< 


clean:
	rm -rf *.o valgr1 valgr2

