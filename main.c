#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  600
#define CELL_SIZE      32

#define MAP_WIDTH      20
#define MAP_HEIGHT     15

#define MOVE_DELAY     150    // ms între mutări player
#define ENEMY_DELAY    300    // ms între mutări inamici
#define MAX_ENEMIES    10

// hartă: '#' zid, '.' punct, 'X' exit, 'P' spawn, 'E' inamic
static char map1[MAP_HEIGHT][MAP_WIDTH+1] = {
    "####################",
    "#P........#........#",
    "#.#######.#.#######.#",
    "#.#.....#.#.#.....#.#",
    "#.#.###.#.#.#.###.#.#",
    "#.#.#.#...E...#.#.#.#",
    "#.#.###.#.###.###.#.#",
    "#.#.....#.#.#.....#.#",
    "#.#######.#.###.###.#",
    "#.......#.#........X",
    "#.#####.#.#.#####.##",
    "#.......#.........##",
    "#.##############.###",
    "#..................#",
    "####################"
};

typedef struct { int x, y; } Point;
typedef struct { int x, y; } Enemy;

static Enemy enemies[MAX_ENEMIES];
static int enemyCount = 0;

static int player_x = 1, player_y = 1;
static int lives       = 3, score = 0;
static bool game_over  = false, game_win = false;
static double lastPlayerMove = 0, lastEnemyMove = 0;

// direcții pentru vecini (4-way)
static const Point dirs[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

// verifică validitate celulă
static bool valid(int x, int y) {
    return x>=0 && x<MAP_WIDTH && y>=0 && y<MAP_HEIGHT && map1[y][x] != '#';
}

// BFS care returnează pasul următor din pontaj spre target
// Dacă nu există drum, returnează false.
static bool bfs_next_step(int sx, int sy, int tx, int ty, int *out_x, int *out_y) {
    static Point q[MAP_WIDTH*MAP_HEIGHT];
    static Point parent[MAP_HEIGHT][MAP_WIDTH];
    bool seen[MAP_HEIGHT][MAP_WIDTH] = {0};
    int qh = 0, qt = 0;

    // inițializări
    q[qt++] = (Point){sx, sy};
    seen[sy][sx] = true;
    parent[sy][sx] = (Point){-1, -1};

    // BFS
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

    // dacă goal nevizitat
    if (!seen[ty][tx]) return false;

    // reconstruiește drumul înapoi până la start
    Point p = {tx, ty}, prev = parent[ty][tx];
    while (!(prev.x == sx && prev.y == sy)) {
        p = prev;
        prev = parent[p.y][p.x];
    }
    *out_x = p.x;
    *out_y = p.y;
    return true;
}

// găsește spawn și inamicii
static void InitGame(void) {
    enemyCount = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            char c = map1[y][x];
            if (c == 'P') {
                player_x = x; player_y = y;
                map1[y][x] = ' ';
            } else if (c == 'E' && enemyCount < MAX_ENEMIES) {
                enemies[enemyCount++] = (Enemy){x, y};
                map1[y][x] = '.'; // sub inamic era punct
            }
        }
    }
}

// desenează hartă + entități
static void DrawMap(void) {
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 pos = {x*CELL_SIZE, y*CELL_SIZE};
            switch (map1[y][x]) {
                case '#': DrawRectangleV(pos, (Vector2){CELL_SIZE,CELL_SIZE}, DARKGRAY); break;
                case '.': DrawCircle(pos.x+CELL_SIZE/2,pos.y+CELL_SIZE/2,5,GOLD); break;
                case 'X': DrawRectangleV(pos,(Vector2){CELL_SIZE,CELL_SIZE},GREEN);
                          DrawText("EXIT",pos.x+4,pos.y+CELL_SIZE/2-8,14,WHITE); break;
                default: break;
            }
        }
    // inamici
    for (int i = 0; i < enemyCount; i++) {
        Vector2 p = { enemies[i].x*CELL_SIZE+CELL_SIZE/2,
                      enemies[i].y*CELL_SIZE+CELL_SIZE/2 };
        DrawCircleV(p, CELL_SIZE/2-2, RED);
    }
    // player
    Vector2 pp = { player_x*CELL_SIZE+CELL_SIZE/2,
                   player_y*CELL_SIZE+CELL_SIZE/2 };
    DrawCircleV(pp, CELL_SIZE/2-2, SKYBLUE);
}

// mută player doar pe vecini ai grafului
static void HandlePlayerInput(void) {
    double now = GetTime()*1000;
    if (now - lastPlayerMove < MOVE_DELAY) return;

    int nx = player_x, ny = player_y;
    if      (IsKeyDown(KEY_RIGHT)) nx++;
    else if (IsKeyDown(KEY_LEFT))  nx--;
    else if (IsKeyDown(KEY_UP))    ny--;
    else if (IsKeyDown(KEY_DOWN))  ny++;
    else return;

    if (!valid(nx, ny) && map1[ny][nx] != 'X') return;

    // colecție punct
    if (map1[ny][nx] == '.') { score += 10; map1[ny][nx] = ' '; }
    // exit
    if (map1[ny][nx] == 'X') { game_win = true; game_over = true; }

    player_x = nx; player_y = ny;
    lastPlayerMove = now;
}

// mută fiecare inamic cu BFS pe graf
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
        // coliziune
        if (enemies[i].x == player_x && enemies[i].y == player_y) {
            lives--;
            if (lives <= 0) game_over = true;
            else { player_x = player_y = 1; }
        }
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pac-Man Grafic (BFS Graph)");
    SetTargetFPS(60);
    InitGame();

    while (!WindowShouldClose()) {
        if (!game_over) {
            HandlePlayerInput();
            MoveEnemies();
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawMap();
            char buf[64];
            sprintf(buf, "Score: %d  Lives: %d", score, lives);
            DrawText(buf, 10, SCREEN_HEIGHT-28, 20, WHITE);

            if (game_over) {
                const char *msg = game_win ? "YOU WIN!" : "GAME OVER";
                Color c = game_win ? GREEN : RED;
                DrawText(msg, SCREEN_WIDTH/2-MeasureText(msg,40)/2,
                         SCREEN_HEIGHT/2-20, 40, c);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
