flags := -Wall -O0 -std=c2x -I.
ldflags	:= 

.PONY: clean

all: xsc

xsc: xsc256.o
	cc $(flags) $^ -o $@  $(ldflags)

xsc256.o: xsc256.c
	cc $(flags) -c $<


clean:
	rm -f *.o xsc