CC=gcc
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS=-g -Wall -Iinclude
OUTFILE=bin/gamename.out
SRC=*.c src/*.c src/GUI/*.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTFILE) $(LIBS)

clean:
	rm $(OUTFILE)