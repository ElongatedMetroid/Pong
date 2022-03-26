CC=gcc
CFLAGS=-g -Wall
SRC=*.c
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
OUTFILE=main.out

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTFILE) $(LIBS)