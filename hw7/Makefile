CFLAGS=-pthread
CC=cc

SRCS1 = hw7_serial.c matrix.c
OBJS1 = $(SRCS1:.c=.o)

SRCS2 = threads.c matrix.c
OBJS2 = $(SRCS2:.c=.o)

all: hw7_serial threads

hw7_serial: $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS1)

threads: $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $(OBJS2)

%.o : %.c
	$(CC) -c $(CFLAGS) $<


clean:
	rm -rf a.out $(OBJS1) $(OBJS2) hw7_serial threads

