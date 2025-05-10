#ifndef PLAYER_H
#define PLAYER_H

// Coordonatele jucatorului
extern int player_x;
extern int player_y;

// Functii de initializare și procesare input
void init_player();
int process_input();

// Functii legate de vieți
int get_lives();
void decrease_life();
void reset_lives();
int is_alive();

// Functii legate de scor
int get_score();
void increase_score(int amount);
void reset_score();

#endif
