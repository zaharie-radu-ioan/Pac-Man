CC = gcc
CFLAGS = -Wall -I src/include -g
LDFLAGS = -L src/lib -lSDL3

# List all source files needed for your project
SRC = main.c map.c player.c question.c graph.c utils.c
OBJ = $(SRC:.c=.o)
TARGET = game.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Pattern rule for compiling .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o *.exe
