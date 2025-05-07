#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"


char map[HEIGHT][WIDTH + 1] = {
    "##############################",
    "#P......#............#......Q#",
    "#.######..######.###.####.##.#",
    "#..............#...#........##",
    "#.#######.#####.###.#.##..##.#",
    "#.Q......#...Q.....#.........#",
    "#.####.####.#.#####...#.###.##",
    "#...........#.....#.#.#.#....#",
    "###.######.###.#.#.###...####.",
    "#...#Q..#....#.#...#...#....Q#",
    "#.###.#.###.#.##..#.#.###.##.#",
    "#.....#.#.....#.........#....#",
    "#.###.#.##.##.###.#####.#.##.#",
    "#Q....#.....#.#........#....F#",
    "##############################"
};

int player_x = 1, player_y = 1;
int score = 0;

Enemy enemies[MAX_ENEMIES];
int num_enemies = MAX_ENEMIES;

void print_map() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == player_x && y == player_y)
                printf("P");
            else
                printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

void print_status() {
    printf("\nScor: %d\n", score);
    printf("Controale: W/A/S/D pentru miscare, Q pentru iesire.\n");
}

//functie care returneaza caracterul de la o anumita pozitie
char get_tile(int x, int y) {
    return map[y][x];
}

//functie care modifica caracterul de la o anumita pozitie
void set_tile(int x, int y, char tile) {
    map[y][x] = tile;
}

void spawn_enemies() {
    int placed = 0;
    while (placed < num_enemies) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        char tile = get_tile(x, y);
        if ((tile == '.' || tile == ' ') && !(x == player_x && y == player_y)) {
            enemies[placed].x = x;
            enemies[placed].y = y;
            set_tile(x, y, 'E');
            placed++;
        }
    }
}

void move_enemies() {
    for (int i = 0; i < num_enemies; i++) {
        int dx = 0, dy = 0;
        int dir = rand() % 4;

        switch (dir) {
            case 0: dx = 1; break;
            case 1: dx = -1; break;
            case 2: dy = 1; break;
            case 3: dy = -1; break;
        }

        int new_x = enemies[i].x + dx;
        int new_y = enemies[i].y + dy;

        if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT)
            continue;

        char tile = get_tile(new_x, new_y);
        if (tile == '.' || tile == ' ') {
            set_tile(enemies[i].x, enemies[i].y, '.');
            enemies[i].x = new_x;
            enemies[i].y = new_y;
            set_tile(new_x, new_y, 'E');
        } else if (tile == 'P') {
            printf("\n Ai fost prins de un inamic! GAME OVER!\n");
            exit(0);
        }
    }
}

void check_for_finish() {
    if (player_x == FINISH_X && player_y == FINISH_Y) {
        printf("\n Ai castigat! Ai ajuns la finish!\n");
        exit(0);
    }
}