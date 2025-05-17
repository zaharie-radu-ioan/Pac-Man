#ifndef QUESTION_RAYLIB_H
#define QUESTION_RAYLIB_H

#include <stdbool.h> // Pentru bool, true/false

// Inițializare întrebări (shuffle + index reset)
void InitQuestion(void);

// Afișează întrebarea curentă și preia răspunsul (apelată când player ajunge pe 'Q')
void trigger_question_if_needed(int player_x, int player_y);

// Dacă este o întrebare activă, actualizează logica inputului (A/B/C/D)
void update_question(void);

// Dacă este o întrebare activă, o desenează pe ecran
void draw_question(void);

// Returnează 1 dacă o întrebare este activă, altfel 0
int is_question_active(void);

#endif // QUESTION_RAYLIB_H
