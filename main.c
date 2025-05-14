#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "map.h"
#include "player.h"
#include "question.h"
#include "utils.h"
#include "graph.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 5.0f
#define CELL_SIZE 40

// Structura pentru harta jocului
extern char map1[15][23]; // Presupunem că harta este definită într-un fișier extern

int main(void)
{
    // Inițializare fereastră
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Joc simplu cu Raylib");

    // Setarea FPS-ului jocului
    SetTargetFPS(60);

    // Inițializare terminal și setări
    init_terminal();
    srand(time(NULL));

    // Shuffle pentru întrebări (presupunem că funcția shuffle_questions există)
    shuffle_questions();

    // Spawn al inamicilor (presupunem că funcția spawn_enemies există)
    spawn_enemies();

    // Construire graf (presupunem că funcția build_graph există)
    build_graph();

    // Poziția inițială a jucătorului
    Vector2 playerPosition = {(float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2)};

    while (!WindowShouldClose()) // Jocul rulează până când utilizatorul închide fereastra
    {
        // Detectarea input-ului pentru mișcarea jucătorului
        if (IsKeyDown(KEY_RIGHT))
        {
            playerPosition.x += PLAYER_SPEED;
        }
        if (IsKeyDown(KEY_LEFT))
        {
            playerPosition.x -= PLAYER_SPEED;
        }
        if (IsKeyDown(KEY_UP))
        {
            playerPosition.y -= PLAYER_SPEED;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            playerPosition.y += PLAYER_SPEED;
        }

        // Limitează mișcarea jucătorului în zona hărții
        if (playerPosition.x < 0)
            playerPosition.x = 0;
        if (playerPosition.x > SCREEN_WIDTH - CELL_SIZE)
            playerPosition.x = SCREEN_WIDTH - CELL_SIZE;
        if (playerPosition.y < 0)
            playerPosition.y = 0;
        if (playerPosition.y > SCREEN_HEIGHT - CELL_SIZE)
            playerPosition.y = SCREEN_HEIGHT - CELL_SIZE;

        // Verifică poziția jucătorului pe hartă
        check_player_position(); // Presupunem că funcția există

        // Mișcă inamicii
        move_enemies(); // Presupunem că funcția move_enemies există

        // Desenarea jocului
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Desenăm harta
        print_map(); // Presupunem că funcția print_map există și desenează harta corect

        // Desenăm jucătorul
        DrawRectangleV(playerPosition, (Vector2){CELL_SIZE, CELL_SIZE}, YELLOW);

        // Desenăm scorul sau starea jocului
        print_status(); // Presupunem că funcția print_status există

        EndDrawing();

        // Procesarea input-ului (presupunem că funcția process_input returnează 0 pentru ieșire)
        if (process_input() == 0)
            break;
    }

    // Resetare terminal
    reset_terminal(); // Presupunem că funcția reset_terminal face curățenie la final

    // Închidem fereastra
    CloseWindow();

    return 0;
}
