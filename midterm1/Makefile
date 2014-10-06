all: bugs bugs_free cycle ack

bugs: bugs.o
	$(CC) $(LFLAGS) -o $@ $<

bugs.o: bugs.c
	$(CC) $(CFLAGS) -c $<

bugs_free: bugs_free.o
	$(CC) $(LFLAGS) -o $@ $<

bugs_free.o: bugs_free.c
	$(CC) $(CFLAGS) -c $<

cycle: cycle.o
	$(CC) $(LFLAGS) -o $@ $<

cycle.o: cycle.c
	$(CC) $(CFLAGS) -c $<

ack: ack.o
	$(CC) $(LFLAGS) -o $@ $<

ack.o: ack.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *~ bugs cycle bugs_free ack

