# You need to fill in whatever details are necessary to get 
# the makefile to work and compile your file. You have the
# bare minimum here.

CFLAGS=-g
OFILES= main.o wlist.o hash.o

all: wgame

wgame: $(OFILES)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(OFILES)

clean:
	rm -rf $(OFILES) wgame
