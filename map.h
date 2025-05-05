#ifndef MAP_H
#define MAP_H

void load_map();
void print_map();
void print_status();
char get_tile(int x, int y);
void set_tile(int x, int y, char tile);
extern int player_x, player_y;
extern int score;

#endif