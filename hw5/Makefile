CC = gcc

all: shell

shell: shellp.c shellp.h
	$(CC) --std=gnu99 -g $< -o $@

clean:
	rm -rf *.o shell *~
