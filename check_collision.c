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
