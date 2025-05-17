    #include "raylib.h"
    #include <string.h>
    #include <ctype.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define MAX_QUESTIONS 100

    typedef struct {
        char question[1024];
        char answer;
    } Question;

    extern int score;
    extern int lives;
    extern char map1[15][21];

    static Question questions[MAX_QUESTIONS];
    static int question_count = 0;
    static int shuffled_indexes[MAX_QUESTIONS];
    static int current_question_index = 0;
    static int question_active = 0;
    static int current_q = -1;
    static char selected_answer = '\0';

    void shuffle_questions() {
        for (int i = 0; i < question_count; i++) shuffled_indexes[i] = i;
        for (int i = question_count - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = shuffled_indexes[i];
            shuffled_indexes[i] = shuffled_indexes[j];
            shuffled_indexes[j] = temp;
        }
    }

    void init_questions() {
        question_count = 3; // doar câteva exemple
        strcpy(questions[0].question, "What is 2+2?\nA. 3\nB. 4\nC. 5\nD. 6"); questions[0].answer = 'B';
        strcpy(questions[1].question, "Capital of France?\nA. Berlin\nB. Madrid\nC. Paris\nD. Rome"); questions[1].answer = 'C';
        strcpy(questions[2].question, "What is AI?\nA. Artificial Intelligence\nB. Animal Instinct\nC. Auto Input\nD. None"); questions[2].answer = 'A';
        
        shuffle_questions();
    }

    int is_question_active() {
        return question_active;
    }

    void trigger_question_if_needed(int px, int py) {
        // Ex: dacă pășești pe o celulă 'Q' din hartă
        extern char map1[15][21];
        if (map1[py][px] == 'Q' && !question_active) {
            question_active = 1;
            current_q = shuffled_indexes[current_question_index++];
            selected_answer = '\0';
            map1[py][px] = '.'; // eliminăm întrebarea din hartă
        }
    }

    void update_question() {
        if (!question_active) return;
        if (IsKeyPressed(KEY_A)) selected_answer = 'A';
        if (IsKeyPressed(KEY_B)) selected_answer = 'B';
        if (IsKeyPressed(KEY_C)) selected_answer = 'C';
        if (IsKeyPressed(KEY_D)) selected_answer = 'D';

        if (selected_answer != '\0') {
            if (selected_answer == questions[current_q].answer) {
                score += 50;
            } else {
                // scade viața dacă ai un sistem de vieți extern
                extern int lives;
                lives--;
            }
            question_active = 0;
            selected_answer = '\0';
        }
    }

    void draw_question() {
        if (!question_active) return;
        DrawRectangle(50, 50, 700, 300, LIGHTGRAY);
        DrawRectangleLines(50, 50, 700, 300, BLACK);

        DrawText(questions[current_q].question, 60, 60, 20, DARKBLUE);
        DrawText("Press A / B / C / D", 60, 280, 20, MAROON);
    }
