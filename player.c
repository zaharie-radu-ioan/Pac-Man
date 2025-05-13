#include "map.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int player_x = 1;
int player_y = 1;

// Vietile si scorul jucatorului
static int lives = 3;
int score = 0;
// Initializez pozitia si vietile jucatorului
void init_player() {
    player_x = 1;
    player_y = 1;
    lives = 3;
}

int get_lives() {
    return lives;
}
void print_lives() {
        printf("Vieti: ");
    for (int i = 0; i < lives; i++) {
        printf("❤️ ");
    }
    printf("\n");
}

void reset_player_position() {
    set_tile(player_x, player_y, '.'); // curăță vechiul P
    player_x = 1;
    player_y = 1;
    set_tile(player_x, player_y, 'P');
}


void decrease_life() {
    
    lives--;
    print_lives();
    if (lives <= 0) {
        printf("\nAi ramas fara vieti! GAME OVER!\n");
        print_score();
        exit(0);
    }
     else {
        printf("\nAi fost prins de un inamic! Ai mai ramas cu %d vieti!\n", lives);
        reset_player_position(); // Resetăm poziția jucătorului
    }
}

void reset_lives() {
    lives = 3;
}

int is_alive() {
    return lives > 0;
}

int print_score() {
    printf("Scor: %d\n", score);
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
        return 1;

    if (tile == 'E') {
        decrease_life();
        return 1;
    }

    // Dacă pășim pe un punct nou, acordăm scor
    if (tile == '.') {
        increase_score(10);
    }

    // Mutare normală
    set_tile(player_x, player_y, ','); // Marcăm că am trecut pe acolo
    player_x = new_x;
    player_y = new_y;
    set_tile(player_x, player_y, 'P');

    return 1;
}
