#ifndef TETROMINO_H
#define TETROMINO_H

#include "vector.h"

typedef struct tetromino
{
    vector2i_t position;
    int rotation;
    int type;
    int color;
} tetromino;

#endif //TETROMINO_H