#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "player.h"
#include "question.h"


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
    
    print_lives(); // afisam vietile
    printf("\n");

    print_score(); // afisam scorul
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
        decrease_life();  
    }
}

}
void check_player_position() {
    extern char tile_under_player;

    if (tile_under_player == 'Q') {
        if (!handleQuestion()) {
            decrease_life();
            printf("\nRaspuns gresit! Ai pierdut o viata!\n");
        } else {
            printf("\nRaspuns corect! Continui jocul!\n");
            set_tile(player_x, player_y, '.');
            increase_score(50);
            tile_under_player = '.';  //  actualizeaza și variabila
        }
    }

    if (player_x == FINISH_X && player_y == FINISH_Y) {
        increase_score(100);
        printf("\nAi castigat! Ai ajuns la finish!\n");
        print_score();
        printf("Felicitari!\n");
        exit(0);
    }
}


