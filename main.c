#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"
#include "question.h"
#include "utils.h"
#include "graph.h"

int main() {
    init_terminal();
    load_map();
    load_questions();
    build_graph();

    while (1) {
        clear_screen();
        print_map();
        print_status();

        if (process_input() == 0) break;
        check_for_question();
    }

    reset_terminal();
    return 0;
}