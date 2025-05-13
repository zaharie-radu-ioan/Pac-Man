#ifndef MAP_H
#define MAP_H

#define MAX_ENEMIES 5
#define WIDTH 30
#define HEIGHT 15
#define FINISH_X 28
#define FINISH_Y 13

typedef struct
{
    int x, y;
} Enemy;

extern int player_x, player_y;
extern int score;
extern Enemy enemies[MAX_ENEMIES];
extern int num_enemies;

void print_map();
void print_status();
char get_tile(int x, int y);
void set_tile(int x, int y, char tile);
void spawn_enemies();
void move_enemies();
void check_player_position();

#endif