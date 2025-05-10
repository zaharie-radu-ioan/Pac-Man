#include "map.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int player_x = 1;
int player_y = 1;

// Vietile si scorul jucatorului
static int lives = 3;
static int score = 0;
// Initializez pozitia si vietile jucatorului
void init_player() {
    player_x = 1;
    player_y = 1;
    lives = 3;
}

int get_lives() {
    return lives;
}

void decrease_life() {
    lives--;
    if (lives <= 0) {
        printf("\nAi fost prins de un inamic! GAME OVER!\n");
        exit(0);
    } else {
        printf("\nAi fost prins de un inamic! Ai mai ramas cu %d vieti!\n", lives);
        player_x = 1;
        player_y = 1;
    }
}

void reset_lives() {
    lives = 3;
}

int is_alive() {
    return lives > 0;
}

int get_score() {
    return score;
}

void increase_score(int amount) {
    score += amount;
}

void reset_score() {
    score = 0;
}

int process_input()
{
    char input = get_input();

    int new_x = player_x;
    int new_y = player_y;

    if (input == 'q')
        return 0;
    else if (input == 'w')
        new_y--;
    else if (input == 's')
        new_y++;
    else if (input == 'a')
        new_x--;
    else if (input == 'd')
        new_x++;

    char tile = get_tile(new_x, new_y);

    if (tile == '#')
    {
        return 1;
    }

    if (tile == 'E')
    {
        printf("\n Ai fost prins de un inamic! GAME OVER!\n");
        exit(0);
    }

    set_tile(player_x, player_y, '.');
    player_x = new_x;
    player_y = new_y;
    set_tile(player_x, player_y, 'P');

    return 1;
}