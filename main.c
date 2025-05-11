#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "player.h"
#include "question.h"
#include "graph.h"

#define GAME_UPDATE_INTERVAL 100  // milliseconds between game updates
#define CELL_SIZE 24              // size of each cell in pixels
#define WIDTH 30                  // Lățimea hărții
#define HEIGHT 15                 // Înălțimea hărții


typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint64 last_update;
    int running;
} AppState;

void render_game(AppState* state) {
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state->renderer);
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            SDL_FRect rect = {
                x * CELL_SIZE,
                y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };

            char tile = get_tile(x, y);
            switch (tile) {
                case '#':  
                    SDL_SetRenderDrawColor(state->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                    break;
                case 'P':  
                    SDL_SetRenderDrawColor(state->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
                    break;
                case 'E':  
                    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    break;
                case 'Q':  
                    SDL_SetRenderDrawColor(state->renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                    break;
                case 'F':  
                    SDL_SetRenderDrawColor(state->renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
                    break;
                case '.':  
                default:
                    SDL_SetRenderDrawColor(state->renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
                    break;
            }

            if (tile != ' ') {
                SDL_RenderFillRect(state->renderer, &rect);
            }
        }
    }

    printf("\nScor: %d\n", score);
    SDL_FRect score_rect = {10, 10, 100, 20};
    SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(state->renderer, &score_rect);
    
    SDL_RenderPresent(state->renderer);
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    AppState* state = (AppState*)SDL_calloc(1, sizeof(AppState));
    if (!state) return SDL_APP_FAILURE;

    *appstate = state;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Try with basic window flags first
    state->window = SDL_CreateWindow("Game", 800, 600, 0);
    if (!state->window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    state->renderer = SDL_CreateRenderer(state->window, NULL);
    if (!state->renderer) {
        SDL_DestroyWindow(state->window);
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    // Force initial display
    SDL_SetRenderDrawColor(state->renderer, 255, 0, 255, 255);
    SDL_RenderClear(state->renderer);
    SDL_RenderPresent(state->renderer);
    
    state->last_update = SDL_GetTicks();
    state->running = 1;
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    AppState* state = (AppState*)appstate;
    
    switch (event->type) {
        case SDL_EVENT_QUIT:
            state->running = 0;
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_ESCAPE:
                case SDLK_Q:
                    state->running = 0;
                    return SDL_APP_SUCCESS;
                case SDLK_W:
                case SDLK_UP:
                    if (process_input() == 0) state->running = 0;
                    break;
                case SDLK_S:
                case SDLK_DOWN:
                    if (process_input() == 0) state->running = 0;
                    break;
                case SDLK_A:
                case SDLK_LEFT:
                    if (process_input() == 0) state->running = 0;
                    break;
                case SDLK_D:
                case SDLK_RIGHT:
                    if (process_input() == 0) state->running = 0;
                    break;
            }
            break;
    }
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* state = (AppState*)appstate;
    const Uint64 now = SDL_GetTicks();

    while ((now - state->last_update) >= GAME_UPDATE_INTERVAL) {
        if (!state->running) return SDL_APP_SUCCESS;
        check_for_question();
        move_enemies();
        check_for_finish();
        state->last_update += GAME_UPDATE_INTERVAL;
    }

    render_game(state);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    AppState* state = (AppState*)appstate;
    if (state) {
        if (state->renderer) SDL_DestroyRenderer(state->renderer);
        if (state->window) SDL_DestroyWindow(state->window);
        SDL_free(state);
    }
    SDL_Quit();
}
