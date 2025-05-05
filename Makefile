CC = gcc
CFLAGS = -Wall

OBJS = main.o map.o player.o question.o utils.o graph.o

all: game

game: $(OBJS)
	$(CC) $(CFLAGS) -o game $(OBJS)

clean:
	rm -f *.o game