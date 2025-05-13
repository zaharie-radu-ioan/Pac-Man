#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "player.h"
#include "question.h"
#include "utils.h"
#include "graph.h"

int main() {
    init_terminal();
    srand(time(NULL));
    shuffle_questions();
    spawn_enemies();
    build_graph();

    while (1) {
    clear_screen();
    print_map();
    print_status();
    
    if (process_input() == 0) 
        break;

    check_player_position();
    move_enemies();
    
}


    reset_terminal();
    return 0;
}