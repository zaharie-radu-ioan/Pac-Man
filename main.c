#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_SPEED 5.0f
#define CELL_SIZE 40

// Structura pentru harta jocului
char map1[15][23] = {
    "####################",
    "#........#.........#",
    "#.#######.#.#######.#",
    "#.#######.#.#######.#",
    "#........#.........#",
    "#.#######.#.#######.#",
    "#........#.........#",
    "#.#######.#.#######.#",
    "#........#.........#",
    "#.#######.#.#######.#",
    "#........#.........#",
    "#.#######.#.#######.#",
    "#........#.........#",
    "####################"};

// Funcție de coliziune cu pereții
int CheckCollisionWithWalls(Vector2 playerPosition)
{
    int mapX = playerPosition.x / CELL_SIZE;
    int mapY = playerPosition.y / CELL_SIZE;

    if (map1[mapY][mapX] == '#')
    {
        return 1; // Coliziune cu peretele
    }
    return 0; // Fără coliziune
}

int main(void)
{
    // Inițializare fereastră
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man simplu cu Raylib");

    // Setarea FPS-ului jocului
    SetTargetFPS(60);

    // Poziția inițială a jucătorului
    Vector2 playerPosition = {(float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2)};

    // Jocul rulează până când utilizatorul închide fereastra
    while (!WindowShouldClose())
    {
        // Detectarea input-ului pentru mișcarea jucătorului
        if (IsKeyDown(KEY_RIGHT))
        {
            if (!CheckCollisionWithWalls((Vector2){playerPosition.x + PLAYER_SPEED, playerPosition.y}))
            {
                playerPosition.x += PLAYER_SPEED;
            }
        }
        if (IsKeyDown(KEY_LEFT))
        {
            if (!CheckCollisionWithWalls((Vector2){playerPosition.x - PLAYER_SPEED, playerPosition.y}))
            {
                playerPosition.x -= PLAYER_SPEED;
            }
        }
        if (IsKeyDown(KEY_UP))
        {
            if (!CheckCollisionWithWalls((Vector2){playerPosition.x, playerPosition.y - PLAYER_SPEED}))
            {
                playerPosition.y -= PLAYER_SPEED;
            }
        }
        if (IsKeyDown(KEY_DOWN))
        {
            if (!CheckCollisionWithWalls((Vector2){playerPosition.x, playerPosition.y + PLAYER_SPEED}))
            {
                playerPosition.y += PLAYER_SPEED;
            }
        }

        // Limităm mișcarea jucătorului la zona hărții
        if (playerPosition.x < 0)
            playerPosition.x = 0;
        if (playerPosition.x > SCREEN_WIDTH - CELL_SIZE)
            playerPosition.x = SCREEN_WIDTH - CELL_SIZE;
        if (playerPosition.y < 0)
            playerPosition.y = 0;
        if (playerPosition.y > SCREEN_HEIGHT - CELL_SIZE)
            playerPosition.y = SCREEN_HEIGHT - CELL_SIZE;

        // Desenarea jocului
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Desenăm harta
        for (int y = 0; y < 15; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                if (map1[y][x] == '#') // Peretele
                {
                    Vector2 wallPosition = {x * CELL_SIZE, y * CELL_SIZE};
                    DrawRectangleV(wallPosition, (Vector2){CELL_SIZE, CELL_SIZE}, BLUE);
                }
            }
        }

        // Desenăm jucătorul (Pac-Man)
        DrawRectangleV(playerPosition, (Vector2){CELL_SIZE, CELL_SIZE}, YELLOW);

        // Text pentru scor
        DrawText("Pac-Man simplu", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Închidem fereastra și eliberăm resursele
    CloseWindow();

    return 0;
}
