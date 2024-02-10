#ifndef TETRIS_H
#define TETRIS_H

#include <time.h>
#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "physics.h"
#include "environment.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRAMINO_SIZE 4
#define POINTS_POS_Y 10
#define POINTS_POS_X 256
#define STOP_FALLING_TIMER 1
#define POINTS_FOR_LINES 100
#define ENDLESS_POINT 1000

enum state {MENU_STATE, GAME_STATE, FADING_STATE};

#endif  //TETRIS_H