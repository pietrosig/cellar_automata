#include "./constant.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = false;
int last_frame_time = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Rect cell;

int cell_vel_x;
int cell_vel_y;
double angle = 0;

const Uint8 *keys;

int space[SPACE_WIDTH][SPACE_HEIGHT];

///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
///////////////////////////////////////////////////////////////////////////////
int initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }
  window = SDL_CreateWindow("A simple game loop using C & SDL",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    fprintf(stderr, "Error creating SDL Window.\n");
    return false;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    fprintf(stderr, "Error creating SDL Renderer.\n");
    return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function to poll SDL events and process keyboard input
///////////////////////////////////////////////////////////////////////////////
void process_input(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      game_is_running = false;
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
  // Initialize the ball object moving down at a constant velocity
  srand(time(NULL));
  keys = SDL_GetKeyboardState(NULL);
  cell_vel_x = 1;
  cell_vel_y = -1;
  cell.x = (SPACE_WIDTH / 2) * OBJ_DIM;
  cell.y = (SPACE_HEIGHT / 2) * OBJ_DIM;
  cell.w = OBJ_DIM;
  cell.h = OBJ_DIM;
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////

void update(void) {
  cell_vel_x = cos(angle);
  cell_vel_y = sin(angle);

  int new_x = cell.x / OBJ_DIM + cell_vel_x;
  int new_y = cell.y / OBJ_DIM + cell_vel_y;

  int r = rand() % 100;
  if (r < 10) {
    new_x++;
    new_y--;
  }
  int mult = 1;

  if (new_x < 0 || new_x >= SPACE_WIDTH) {
    // X out of bound
    new_x -= cell_vel_x;
    angle += M_PI;
    return;
  }

  if (new_y < 0 || new_y >= SPACE_WIDTH) {
    // X out of bound
    new_y -= cell_vel_y;
    angle += M_PI;
    return;
  }

  if (space[new_x][new_y] == EMPTY) {
    space[new_x][new_y] = WALL;
    mult = -1;
  } else {
    space[new_x][new_y] = EMPTY;
  }

  angle += mult * (M_PI / 2);

  if (fabs(angle) > 2 * M_PI)
    angle = 0;
  cell.x = new_x * OBJ_DIM;
  cell.y = new_y * OBJ_DIM;
}

///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
///////////////////////////////////////////////////////////////////////////////
void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Rect r;
  r.w = OBJ_DIM;
  r.h = OBJ_DIM;

  // Draw player
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &cell);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  // Draw map
  for (int m = 0; m < SPACE_WIDTH; m++) {
    for (int n = 0; n < SPACE_HEIGHT; n++) {
      if (space[m][n] == EMPTY)
        continue;

      r.x = m * OBJ_DIM;
      r.y = n * OBJ_DIM;
      r.w = OBJ_DIM;
      r.h = OBJ_DIM;

      SDL_RenderFillRect(renderer, &r);
    }
  }

  SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
// Function to destroy SDL window and renderer
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *args[]) {
  game_is_running = initialize_window();

  setup();

  while (game_is_running) {
    process_input();
    update();
    render();
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
      SDL_Delay(time_to_wait);
    }

    last_frame_time = SDL_GetTicks();
  }

  destroy_window();

  return 0;
}
