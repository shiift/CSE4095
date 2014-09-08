all: collatz 

collatz: file.o
	$(CC) $(LFLAGS) -o $@ $<

file.o: file.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *~ collatz

