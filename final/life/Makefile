CC=cc
CFLAGS=-g
LIBS=-pthread
OBJS = live_threaded.o

all: life_threaded

life_threaded: $(OBJS)
	$(CC) -o life_threaded $(OBJS) $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -rf *.o life_threaded
