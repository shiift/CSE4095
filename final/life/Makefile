CC=cc
CFLAGS=-g -std=c89
LIBS=-pthread
OBJS = live.o

all: life

life: $(OBJS)
	$(CC) -o life $(OBJS) $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -rf *.o life
