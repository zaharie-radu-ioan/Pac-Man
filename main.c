#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "question_raylib.h"

#define CELL_SIZE      38
#define MAP_WIDTH      21
#define MAP_HEIGHT     15

#define SCREEN_WIDTH   (MAP_WIDTH * CELL_SIZE)
#define SCREEN_HEIGHT  (MAP_HEIGHT * CELL_SIZE)

#define MOVE_DELAY     150    // ms intre mutari player
#define ENEMY_DELAY    300    // ms intre mutari inamici
#define MAX_ENEMIES    10

// harta: '#' zid, '.' punct, 'X' exit, 'P' spawn, 'E' inamic
char map1[MAP_HEIGHT][MAP_WIDTH+1] = {
    "#####################",
    "#P........#.........#",
    "#.#######.#.#######.#",
    "#.#.....#.#.#.....#.#",
    "#.#.###.#.#.#.###.#.#",
    "#.#.#.#...E...#.#.#.#",
    "#.#.###.#.###.###.#.#",
    "#Q#.....#.#.#.....#.#",
    "#.#######.#.###.###.#",
    "#.......#.#E........X",
    "#.#####.#.#.#####..##",
    "#...Q...#..........##",
    "#.##############..###",
    "#...Q...............#",
    "#####################"
};

typedef struct { int x, y; } Point;
typedef struct { 
    int x, y; 
    int type; 
} Enemy;

static Enemy enemies[MAX_ENEMIES];
static Point enemySpawn[MAX_ENEMIES];
static int enemyCount = 0;

static int player_x = 1, player_y = 1;
static int spawn_x = 1, spawn_y = 1;

int lives       = 3, score = 0;
bool game_over  = false, game_win = false;
static double lastPlayerMove = 0, lastEnemyMove = 0;

// variabile pentru animatie Pacman
static bool mouthOpen = false;
static double lastAnimTime = 0.0;

static const Point dirs[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

static bool valid(int x, int y) {
    return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT && map1[y][x] != '#';
}

static bool bfs_next_step(int sx, int sy, int tx, int ty, int *out_x, int *out_y) {
    static Point q[MAP_WIDTH*MAP_HEIGHT];
    static Point parent[MAP_HEIGHT][MAP_WIDTH];
    bool seen[MAP_HEIGHT][MAP_WIDTH] = {0};
    int qh = 0, qt = 0;

    q[qt++] = (Point){sx, sy};
    seen[sy][sx] = true;
    parent[sy][sx] = (Point){-1, -1};

    while (qh < qt) {
        Point cur = q[qh++];
        if (cur.x == tx && cur.y == ty) break;
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dirs[i].x;
            int ny = cur.y + dirs[i].y;
            if (valid(nx, ny) && !seen[ny][nx]) {
                seen[ny][nx] = true;
                parent[ny][nx] = cur;
                q[qt++] = (Point){nx, ny};
            }
        }
    }

    if (!seen[ty][tx]) return false;

    Point p = {tx, ty}, prev = parent[ty][tx];
    while (!(prev.x == sx && prev.y == sy)) {
        p = prev;
        prev = parent[p.y][p.x];
    }
    *out_x = p.x;
    *out_y = p.y;
    return true;
}

static void InitGame(void) {
    enemyCount = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            char c = map1[y][x];
            if (c == 'P') {
                player_x = spawn_x = x;
                player_y = spawn_y = y;
                map1[y][x] = ' ';
            } else if (c == 'E' && enemyCount < MAX_ENEMIES) {
                    enemies[enemyCount].x = x;
                    enemies[enemyCount].y = y;
                    enemySpawn[enemyCount].x = x;  // salveaza pozitia initiala
                    enemySpawn[enemyCount].y = y;
                    enemies[enemyCount].type = enemyCount % 2;  // alterneaza tipul 0 sau 1
                    enemyCount++;
                    map1[y][x] = '.'; // sub inamic era punct

            }
        }
    }
    InitQuestion(); // initializare intrebari
}

// Texturi pentru player (doua pentru animatie), inamic, intrebare
static Texture2D texPlayerClosed;
static Texture2D texPlayerOpen;
static Texture2D texEnemy;
static Texture2D texEnemy2;
static Texture2D texDot;
static Texture2D texQuestion;

static void DrawMap(void) {
    float scale = 0.035f;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 pos = { x * CELL_SIZE, y * CELL_SIZE };
            switch (map1[y][x]) {
                case '#':
                    DrawRectangleV(pos, (Vector2){ CELL_SIZE, CELL_SIZE }, DARKGRAY);
                    break;
                case '.': {
                    float scale = 0.015f;  
                    Vector2 dotPos = {
                    x * CELL_SIZE + CELL_SIZE / 2 - (texDot.width * scale) / 2,
                    y * CELL_SIZE + CELL_SIZE / 2 - (texDot.height * scale) / 2
                    };
                 DrawTextureEx(texDot, dotPos, 0.0f, scale, WHITE);
                break;
                }
                case 'Q': {
                    Vector2 qpos = {
                        x * CELL_SIZE + CELL_SIZE / 2 - (texQuestion.width * scale) / 2,
                        y * CELL_SIZE + CELL_SIZE / 2 - (texQuestion.height * scale) / 2
                    };
                    DrawTextureEx(texQuestion, qpos, 0.0f, scale, WHITE);
                    break;
                }
                case 'X':
                    DrawRectangleV(pos, (Vector2){ CELL_SIZE, CELL_SIZE }, GREEN);
                    DrawText("EXIT", pos.x + 4, pos.y + CELL_SIZE / 2 - 8, 14, WHITE);
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 0; i < enemyCount; i++) {
    Vector2 p = {
        enemies[i].x * CELL_SIZE + CELL_SIZE / 2 - (texEnemy.width * scale) / 2,
        enemies[i].y * CELL_SIZE + CELL_SIZE / 2 - (texEnemy.height * scale) / 2
    };
    if (enemies[i].type == 0) {
        DrawTextureEx(texEnemy, p, 0.0f, scale, WHITE);
    } else {
        DrawTextureEx(texEnemy2, p, 0.0f, scale, WHITE);
    }
}

    // Actualizeaza animatia jucatorului
    double now = GetTime();
    if (now - lastAnimTime > 0.3) {
        mouthOpen = !mouthOpen;
        lastAnimTime = now;
    }

    Texture2D currentPlayerTex = mouthOpen ? texPlayerOpen : texPlayerClosed;
    Vector2 pp = {
        player_x * CELL_SIZE + CELL_SIZE / 2 - (currentPlayerTex.width * scale) / 2,
        player_y * CELL_SIZE + CELL_SIZE / 2 - (currentPlayerTex.height * scale) / 2
    };
    DrawTextureEx(currentPlayerTex, pp, 0.0f, scale, WHITE);
}

static void HandlePlayerInput(void) {
    double now = GetTime()*1000;
    if (now - lastPlayerMove < MOVE_DELAY) return;

    int nx = player_x, ny = player_y;
    if      (IsKeyDown(KEY_RIGHT)) nx++;
    else if (IsKeyDown(KEY_LEFT))  nx--;
    else if (IsKeyDown(KEY_UP))    ny--;
    else if (IsKeyDown(KEY_DOWN))  ny++;
    else return;

    if (!(nx >= 0 && ny >= 0 && nx < MAP_WIDTH && ny < MAP_HEIGHT)) return;
    if (map1[ny][nx] == '#') return;

    char title = map1[ny][nx];
    player_x = nx; player_y = ny;

    if (title == '.') { score += 10; map1[ny][nx] = ' '; }
    if (title == 'X') { game_win = true; game_over = true; score += 100; }
    if (title == 'Q') {
        map1[ny][nx] = '.';
        trigger_question_if_needed(player_x, player_y);
    }

    lastPlayerMove = now;
}

static void MoveEnemies(void) {
    double now = GetTime()*1000;
    if (now - lastEnemyMove < ENEMY_DELAY) return;
    lastEnemyMove = now;

    for (int i = 0; i < enemyCount; i++) {
        int ex = enemies[i].x, ey = enemies[i].y;
        int tx, ty;
        if (bfs_next_step(ex, ey, player_x, player_y, &tx, &ty)) {
            enemies[i].x = tx;
            enemies[i].y = ty;
        }
       if (enemies[i].x == player_x && enemies[i].y == player_y) {
    lives--;
    if (lives <= 0) game_over = true;
    else {
        // Reseteaza pozitia inamicului la spawn-ul lui
        enemies[i].x = enemySpawn[i].x;
        enemies[i].y = enemySpawn[i].y;

        // Reseteaza pozitia jucatorului la spawn
        player_x = spawn_x;
        player_y = spawn_y;
        break;
        }
        }
    }
}

void CheckQuestionTrigger() {
    trigger_question_if_needed(player_x, player_y);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man Grafic (BFS Graph)");
    SetTargetFPS(60);

    // incarca texturi
    texPlayerClosed = LoadTexture("pacman.png");  // imagine gura inchisa
    texPlayerOpen = LoadTexture("pacman2.png");      // imagine gura deschisa
    texEnemy = LoadTexture("ghost.png");
    texEnemy2 = LoadTexture("ghost2.png");
    texDot = LoadTexture("dot.png");
    texQuestion = LoadTexture("question.png");

    InitGame();

    while (!WindowShouldClose()) {
        if (!game_over) {
            if (!is_question_active()) {
                HandlePlayerInput();
                MoveEnemies();
            }
            update_question();
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawMap();
            char buf[64];
            sprintf(buf, "Score: %d  Lives: %d", score, lives);
            DrawText(buf, 10, SCREEN_HEIGHT - 28, 20, WHITE);

            if (is_question_active()) {
                draw_question();
            }

            if (game_over) {
                const char *msg = game_win ? "YOU WIN!" : "GAME OVER";
                Color c = game_win ? GREEN : RED;
                DrawText(msg, SCREEN_WIDTH / 2 - MeasureText(msg, 40) / 2,
                         SCREEN_HEIGHT / 2 - 20, 40, c);
            }
        EndDrawing();
    }

    // Elibereaza texturi
    UnloadTexture(texPlayerClosed);
    UnloadTexture(texPlayerOpen);
    UnloadTexture(texEnemy);
    UnloadTexture(texEnemy2);
    UnloadTexture(texDot);
    UnloadTexture(texQuestion);

    CloseWindow();
    return 0;
}