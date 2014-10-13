CFLAGS=-g
CC=cc

all: client server

client: client.o
	$(CC) $(CFLAGS) -o $@ $<

server: server.o
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.c 
	$(CC) -c $(CFLAGS) $< 


clean:
	rm -rf *.o client server

