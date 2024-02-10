#include "Tetris.h"

extern int stage[];         //if something arrive from outside

int checkCollision(const int tetr_start_x, const int tetr_start_y, const int* tetr)
{
    for (int i = 0; i < TETRAMINO_SIZE; i++)
    {
        for (int j = 0; j < TETRAMINO_SIZE; j++)
        {
            const int offset = i * TETRAMINO_SIZE + j;

            if (tetr[offset] >= 1)
            {
                const int offset_stage = (i + tetr_start_y) * STAGE_WIDTH + (j + tetr_start_x);

                if (stage[offset_stage] != 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void linesFall(int start_line_y)
{
    for (int i = start_line_y; i >= 0; i--)
    {
        for (int j = 1; j < STAGE_WIDTH - 1; j++)
        {
            const int offset = j + i * STAGE_WIDTH;
            const int offset_below = (i + 1) * STAGE_WIDTH + j;

            if (stage[offset_below] == 0 && stage[offset] > 0)
            {
                stage[offset_below] = stage[offset];
                stage[offset] = 0;
            }
        }
    }
}