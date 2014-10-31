CFLAGS=-pthread
CC=cc

all: start_processes start_threads hello hello_arg1 hello_arg2

start_processes: start_processes.o
	$(CC) $(CFLAGS) -o $@ $<

start_threads: start_threads.o
	$(CC) $(CFLAGS) -o $@ $<

hello: hello.o
	$(CC) $(CFLAGS) -o $@ $<

hello_arg1: hello_arg1.o
	$(CC) $(CFLAGS) -o $@ $<

hello_arg2: hello_arg2.o
	$(CC) $(CFLAGS) -o $@ $<


%.o : %.c
	$(CC) -c $(CFLAGS) $<


clean:
	rm -rf a.out *.o start_processes start_threads hello hello_arg1 hello_arg2

