#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
void clear_screen() { system("cls"); }
char get_input() { return _getch(); }
void init_terminal() {}
void reset_terminal() {}

#else
#include <termios.h>
#include <unistd.h>

static struct termios old, current;

void init_terminal() {
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &current);
}

void reset_terminal() {
    tcsetattr(0, TCSANOW, &old);
}

char get_input() {
    char c;
    read(0, &c, 1);
    return c;
}

void clear_screen() {
    printf("\033[H\033[J");
}
#endif