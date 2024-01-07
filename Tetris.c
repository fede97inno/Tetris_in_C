#include "raylib.h"
#include <time.h>
#include <string.h>
#include "Tetris.h"
#include <stdio.h>

void linesFall(int start_line_y);

int points_counter = 0;
int level = 1;              //WIP
int highscore_for_next_level = 200;
//float wait_for_falling = 1.5;

int is_deleting = 0;
float blink_time = STOP_FALLING_TIMER;
float time_speed = 4.0;
float text_deleting_pos_x = 0;

const int tetramino_L_0[] = 
{
    0,1,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,0,0
};
const int tetramino_L_90[] = 
{
    0,0,0,0,
    1,1,1,0,
    1,0,0,0,
    0,0,0,0
};
const int tetramino_L_180[] = 
{
    1,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,0,0,0
};
const int tetramino_L_270[] = 
{
    0,0,1,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0
};

const int tetramino_J_0[] = 
{
    0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0
};
const int tetramino_J_90[] = 
{
    1,0,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0
};

const int tetramino_J_180[] = 
{
    0,1,1,0,
    0,1,0,0,
    0,1,0,0,
    0,0,0,0
};
const int tetramino_J_270[] = 
{
    0,0,0,0,
    1,1,1,0,
    0,0,1,0,
    0,0,0,0
};
const int tetramino_O_0[] = 
{
    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0
};

const int tetramino_S_0[] = 
{
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
    0,0,0,0
};
const int tetramino_S_90[] = 
{
    0,0,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,1,0
};
const int tetramino_S_180[] = 
{
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
};
const int tetramino_S_270[] = 
{
    0, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
};
const int tetramino_Z_0[] =
{
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
};

const int tetramino_Z_90[] =
{
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
};

const int tetramino_Z_180[] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
};

const int tetramino_Z_270[] =
{
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};
const int tetramino_I_0[] = 
{
    0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0
};
const int tetramino_I_90[] = 
{
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0
};
const int tetramino_I_180[] = 
{
    0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0
};
const int tetramino_I_270[] = 
{
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0
};
const int tetramino_T_0[] = 
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};
const int tetramino_T_90[] = 
{
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};
const int tetramino_T_180[] = 
{
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};
const int tetramino_T_270[] = 
{
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const Color color_types[8] =
{
    {255,255,0,255},        //YELLOW
    {0,0,255,255},          //BLUE
    {0,255,0,255},          //GREEN
    {128,0,128,255},        //PURPLE
    {255,182,193,255},      //LIGHT PINK
    {255,0,255,255},        //MAGENTA
    {0,255,255,255},        //CYAN
    {255,165,0,255}         //ORANGE
};

const int *tetramino_types[7][4] =
{
    {tetramino_I_0, tetramino_I_90, tetramino_I_180,tetramino_I_270},
    {tetramino_J_0, tetramino_J_90, tetramino_J_180, tetramino_J_270},
    {tetramino_Z_0, tetramino_Z_90, tetramino_Z_180,tetramino_Z_270},
    {tetramino_S_0, tetramino_S_90, tetramino_S_180,tetramino_S_270},
    {tetramino_O_0, tetramino_O_0, tetramino_O_0,tetramino_O_0},
    {tetramino_L_0, tetramino_L_90, tetramino_L_180,tetramino_L_270},
    {tetramino_T_0, tetramino_T_90, tetramino_T_180,tetramino_T_270},
};

int stage[] = {                     //global var, array for the stage with walls
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1
    };

void drawTetraminos(int pos_x, int pos_y, const int *tetr_type, const int start_x_offset, const int start_y_offset, Color tetr_col)
{
    for (int i = 0; i < TETRAMINO_SIZE; i++)
    {
        for (int j = 0; j < TETRAMINO_SIZE; j++)
        {
            if(tetr_type[j+i*TETRAMINO_SIZE] >= 1)
            {
                    DrawRectangle((pos_x + j )* TILE_SIZE + start_x_offset,(pos_y + i) * TILE_SIZE + start_y_offset, TILE_SIZE, TILE_SIZE, tetr_col);
            }
        }
    }
    
}

void deleteLine()
{
    for (int i = 0; i < STAGE_HEIGHT - 1; i++)
    {
        int check_line = 1;

        for (int j = 1; j < STAGE_WIDTH - 1; j++)
        {
            const int offset = j + i * STAGE_WIDTH;

            if (stage[offset] == 0)
            {
                check_line = 0;
                break;
            }
        }

        if (check_line)
        {
            const int offset = i * STAGE_WIDTH + 1;
            memset(stage + offset, 0, (STAGE_WIDTH - 2) * sizeof(int)); //where to begin, what to write, for how much
            linesFall(i);
            points_counter += POINTS_FOR_LINES;


            if (points_counter <= ENDLESS_POINT && points_counter >= highscore_for_next_level)
            {
                time_speed += 1;
                highscore_for_next_level += POINTS_FOR_LINES * 2;
                level +=1;                                               //WIP
                TraceLog(LOG_INFO, "FASTER!! next objective : %d, falling speed : %f", highscore_for_next_level, time_speed);
            }
            is_deleting = i * TILE_SIZE;
            text_deleting_pos_x = 0;
        }
    }
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

int main(int argc, char **argv, char  **environ)
{
    const int stage_offset_x = WINDOW_WIDTH / 2 - STAGE_WIDTH / 2 * TILE_SIZE;          //better to use /2 when using int cause are faster than using *0.5, float operation are slower
    const int stage_offset_y = WINDOW_HEIGHT / 2 - STAGE_HEIGHT / 2 * TILE_SIZE;

    const int start_tetr_x = STAGE_WIDTH / 2;                                                       //we want this in cells
    const int start_tetr_y = 0; 

    int current_tetr_x = start_tetr_x;
    int current_tetr_y = start_tetr_y;

    time_t unix_time;
    time(&unix_time);
    
    SetRandomSeed(unix_time);
    int current_tetr_type = GetRandomValue(0,6);
    int current_tetr_rot = 0;
    int current_color = GetRandomValue(0, 7);

    float wait_for_falling = 1.5;
    float fall_down_timer = wait_for_falling;

    //float text_deleting_pos_x = 0;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Title");
    InitAudioDevice();

    SetTargetFPS(60);

    Music background_music = LoadMusicStream("Assets/Background_music.ogg");
    Sound block_fall_sound = LoadSound("Assets/Block_fall_sound.wav");
    background_music.looping = 1;

    PlayMusicStream(background_music);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(background_music);

        fall_down_timer = fall_down_timer - GetFrameTime() * time_speed;
        
        if (IsKeyPressed(KEY_SPACE))
        {
            const int last_rot = current_tetr_rot;

            current_tetr_rot++;
            if (current_tetr_rot > 3)
            {
                current_tetr_rot = 0;
            }
            
            if (checkCollision(current_tetr_x, current_tetr_y, tetramino_types[current_tetr_type][current_tetr_rot]))
            {
                current_tetr_rot = last_rot;
            }
            
        }
        
        if (fall_down_timer < 0 || IsKeyPressed(KEY_S))
        {
            const int next_offset_y_position = current_tetr_x + (current_tetr_y + 1) * STAGE_WIDTH;

            if (!checkCollision(current_tetr_x, current_tetr_y + 1, tetramino_types[current_tetr_type][current_tetr_rot]))
            {
                current_tetr_y++;
                fall_down_timer = wait_for_falling;
            }
            else
            {
                for (int i = 0; i < TETRAMINO_SIZE; i++)
                {
                    for (int j = 0; j < TETRAMINO_SIZE; j++)
                    {
                        const int tile_index = i * TETRAMINO_SIZE + j;
                        const int* tetr = tetramino_types[current_tetr_type][current_tetr_rot];
                        
                        if (tetr[tile_index] >= 1)
                        {
                            const int offset_stage = (i + current_tetr_y) * STAGE_WIDTH + (j + current_tetr_x);
                            stage[offset_stage] = current_color + 1;            //save current color, previous 1, we need to change the ==1 to >= 1, 0 it's not a value that we can consider
                        }
                    }
                }

                PlaySound(block_fall_sound);
                deleteLine();

                current_tetr_x = start_tetr_x;
                current_tetr_y = start_tetr_y;
                current_tetr_type = GetRandomValue(0, 6);
                current_color = GetRandomValue(0, 7);
            }

        }

        if (IsKeyPressed(KEY_D))
        {
            if (!checkCollision(current_tetr_x + 1, current_tetr_y, tetramino_types[current_tetr_type][current_tetr_rot]))       //the wall "1" prevent overflow
            {
                current_tetr_x++;
            }
        }

        if (IsKeyPressed(KEY_A))
        {
            if (!checkCollision(current_tetr_x - 1, current_tetr_y, tetramino_types[current_tetr_type][current_tetr_rot]))       //the wall "1" prevent overflow
            {
                current_tetr_x--;
            }
        }
        

        BeginDrawing();
        
        Color background_color = {200, 200, 200, 255};
        ClearBackground(background_color);

        drawTetraminos(current_tetr_x, current_tetr_y, tetramino_types[current_tetr_type][current_tetr_rot], stage_offset_x, stage_offset_y, color_types[current_color]);
        
       for (int i = 0; i < STAGE_HEIGHT; i++)
       {
            for (int j = 0; j < STAGE_WIDTH; j++)
            {
                const int offset = j+i*STAGE_WIDTH;
                const int color = stage[offset];

                if (stage[offset] != 0)
                {
                    DrawRectangle(j * TILE_SIZE + stage_offset_x,i * TILE_SIZE + stage_offset_y, TILE_SIZE, TILE_SIZE, color_types[color - 1]);
                }

                DrawRectangleLines(j * TILE_SIZE + stage_offset_x,i * TILE_SIZE + stage_offset_y, TILE_SIZE, TILE_SIZE, BLACK);
            }
       }

        DrawText(TextFormat("Score : %d", points_counter), stage_offset_x, POINTS_POS_Y, 16, WHITE);    //text format for formatting string
        DrawText(TextFormat("Level : %d", level), stage_offset_x, POINTS_POS_Y + 16, 16, WHITE);        //WIP
        
        if (is_deleting && text_deleting_pos_x <= STAGE_WIDTH * TILE_SIZE)
        {
            DrawRectangle(stage_offset_x + text_deleting_pos_x,is_deleting + stage_offset_y - TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
            text_deleting_pos_x += GetFrameTime() * 250;
            TraceLog(LOG_INFO, "%f - %d", text_deleting_pos_x, stage_offset_x + STAGE_WIDTH * TILE_SIZE);
        }
        
        EndDrawing();
    }

    UnloadMusicStream(background_music);
    UnloadSound(block_fall_sound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}