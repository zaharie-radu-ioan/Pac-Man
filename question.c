#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "graph.h"

typedef struct {
    char question[128];
    char answer;
} Question;

Question questions[] = {
    {"Care este complexitatea lui BFS?\nA. O(n^2)\nB. O(n)\nC. O(V+E)", 'C'},
    {"Ce este un graf orientat?\nA. Fara sens\nB. Cu directii\nC. Doar cu valori pozitive", 'B'},
    {"DFS parcurge nodurile în:\nA. Lățime\nB. Adâncime\nC. Aleatoriu", 'B'}
};
int question_count = 3;

void load_questions() {}

void ask_graph_question() {
    int tx = rand() % 20;
    int ty = rand() % 10;

    while (get_tile(tx, ty) == '#') {
        tx = rand() % 20;
        ty = rand() % 10;
    }

    int dist = shortest_path(player_x, player_y, tx, ty);
    printf("Care este distanța minimă de la (%d,%d) la (%d,%d)?\n", player_x, player_y, tx, ty);
    printf("Raspuns: ");
    int rasp;
    scanf("%d", &rasp);
    if (rasp == dist) {
        printf("Corect! +10 puncte\n");
        score += 10;
    } else {
        printf("Gresit. Raspuns corect: %d\n", dist);
    }
    printf("Apasa ENTER pentru a continua...");
    getchar(); getchar();
}

void check_for_question() {
    if (get_tile(player_x, player_y) == 'Q') {
        set_tile(player_x, player_y, '.');

        if (score % 2 == 0)
            ask_graph_question();
        else {
            int q_index = rand() % question_count;
            printf("\n%s\n", questions[q_index].question);
            printf("Raspuns: ");
            char r;
            scanf(" %c", &r);

            if (r == questions[q_index].answer) {
                printf("Corect!\n");
                score += 10;
            } else {
                printf("Gresit! Raspunsul era: %c\n", questions[q_index].answer);
            }

            printf("Apasa ENTER pentru a continua...");
            getchar(); getchar();
        }
    }
}