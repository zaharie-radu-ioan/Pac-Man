CC = gcc
CFLAGS = -Wall -g -Isrc/include
LDFLAGS = -Lsrc/lib -lraylib -lopengl32 -lm

SRC = main.c map.c player.c question.c graph.c utils.c
OBJ = $(SRC:.c=.o)
TARGET = game.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o *.exe
