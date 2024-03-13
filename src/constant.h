#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define OBJ_DIM 20

#define SPACE_WIDTH (WINDOW_WIDTH / OBJ_DIM)
#define SPACE_HEIGHT (WINDOW_HEIGHT / OBJ_DIM)

#define UP_POS 0
#define DOWN_POS 1
#define LEFT_POS 2
#define RIGHT_POS 3

#define EMPTY 0
#define WALL 1
#define APPLE 2

#define UP_ROOM -1
#define DOWN_ROOM -2
#define LEFT_ROOM -3
#define RIGHT_ROOM -4

#define N_SLIMES 3
#define POPULATION_SIZE 100000

#define VEL 1

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

#endif
