all: ex1-for ex1-while ex2 ex3

ex1-for: ex1-for.o
	$(CC) $(LFLAGS) -o $@ $<

ex1-for.o: ex1-for.c
	$(CC) $(CFLAGS) -c $<

ex1-while: ex1-while.o
	$(CC) $(LFLAGS) -o $@ $<

ex1-while.o: ex1-while.c
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
	rm -rf *.o *~ ex1-for ex1-while ex2 ex3

