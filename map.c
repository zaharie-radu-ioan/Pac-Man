#include <stdio.h>
#include "map.h"

#define WIDTH 20
#define HEIGHT 10

char map[HEIGHT][WIDTH + 1] = {
    "###################",
    "#P......#.........#",
    "#.######.#####.##.#",
    "#.............#..Q#",
    "#.#######.####.##.#",
    "#.Q......#....Q...#",
    "#.####.######.###.#",
    "#......#.....#....#",
    "#.######.###.###.##",
    "###################"
};

int player_x = 1, player_y = 1;
int score = 0;

void load_map() {
    // hartă hardcodată deja
}

void print_map() {
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", map[i]);
    }
}

void print_status() {
    printf("\nScor: %d\n", score);
    printf("Controale: W/A/S/D pentru mișcare, Q pentru ieșire.\n");
}

//functie care returneaza caracterul de la o anumita pozitie
char get_tile(int x, int y) {
    return map[y][x];
}

//functie care modifica caracterul de la o anumita pozitie
void set_tile(int x, int y, char tile) {
    map[y][x] = tile;
}