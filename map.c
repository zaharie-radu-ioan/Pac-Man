#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "map.h"
#include "player.h"
#include "question.h"
#include "graph.h"

char map[HEIGHT][WIDTH + 1] = {
    "##############################",
    "#P...................#......Q#",
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
    "##############################"};

Enemy enemies[MAX_ENEMIES];
int num_enemies = MAX_ENEMIES;

void print_map()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == player_x && y == player_y)
                printf("P");
            else
                printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

void print_status()
{

    print_lives(); // afisam vietile
    printf("\n");

    print_score(); // afisam scorul
    printf("Controale: W/A/S/D pentru miscare, Q pentru iesire.\n");
}

// functie care returneaza caracterul de la o anumita pozitie
char get_tile(int x, int y)
{
    return map[y][x];
}

// functie care modifica caracterul de la o anumita pozitie
void set_tile(int x, int y, char tile)
{
    map[y][x] = tile;
}

void spawn_enemies()
{
    int placed = 0;
    while (placed < num_enemies)
    {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        char tile = get_tile(x, y);
        if ((tile == '.' || tile == ' ') && manhattan_distance(x, y, player_x, player_y) > 5)

        {
            enemies[placed].x = x;
            enemies[placed].y = y;
            enemies[placed].underneath = get_tile(x, y);  // salveaza ce era sub
            set_tile(x, y, 'E');

            placed++;
        }
    }
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void move_enemies() {
    bool player_hit = false;

    for (int i = 0; i < num_enemies; i++) {
        if (player_hit) break;  

        int ex = enemies[i].x;
        int ey = enemies[i].y;

        if (manhattan_distance(ex, ey, player_x, player_y) <= 6) {
            Path path = shortest_path(ex, ey, player_x, player_y);

            if (path.length > 0) {
                Node* next = path.steps[0];
                char next_tile = get_tile(next->x, next->y);

                // daca drumul e blocat sau deja ocupat, nu ne miscam
                if (next_tile == '#' || next_tile == 'E') 
                    continue;

                // daca il prinde pe player
                if (next->x == player_x && next->y == player_y) {
                    decrease_life();
                    player_hit = true;
                    continue;                // nu mutam inamicul acum
                }

                // restauram ce era sub inamicul anterior
                set_tile(ex, ey, enemies[i].underneath);

                // salvam ce e in noua pozitie si mutam inamicul
                enemies[i].underneath = get_tile(next->x, next->y);
                enemies[i].x = next->x;
                enemies[i].y = next->y;
                set_tile(next->x, next->y, 'E');
            }
        }
    }
}

void check_player_position() {
    if (tile_under_player == 'Q') {
        if (handleQuestion()) {
            increase_score(100); // raspuns corect
        } else {
            decrease_life(); // raspuns gresit
        }
        tile_under_player = '.'; // intrebarea a fost consumata
    }

    if (tile_under_player == 'F') {
        print_map();
        printf("\n Ai castigat! Ai ajuns la finish!\n");
        exit(0);
    }
}

