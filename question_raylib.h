#ifndef QUESTION_RAYLIB_H
#define QUESTION_RAYLIB_H

#include <stdbool.h> // Pentru bool, true/false

// Initializare intrebari (shuffle + index reset)
void InitQuestion(void);

// Afiseaza intrebarea curenta si preia raspunsul (apelata cand player ajunge pe 'Q')
void trigger_question_if_needed(int player_x, int player_y);

// Daca este o intrebare activa, actualizeaza logica inputului (A/B/C/D)
void update_question(void);

// Daca este o intrebare activa, o deseneaza pe ecran
void draw_question(void);

// Returneaza 1 daca o intrebare este activa, altfel 0
int is_question_active(void);

#endif // QUESTION_RAYLIB_H
