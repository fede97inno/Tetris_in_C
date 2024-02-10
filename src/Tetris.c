#include "Tetris.h"

typedef struct tetromino
{
    Color color;
    int rotations[4][16];
}tetromino;


void linesFall(int start_line_y);

int points_counter = 0;
int level = 1;              
int highscore_for_next_level = 200;

int current_tetr_index;
float blink_time = STOP_FALLING_TIMER;
float time_speed = 4.0;
float text_deleting_pos_x = 1;

int line_to_delete = 0;
int lines_to_delete[4];
int down_line = 0;

int current_state;

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
    0,0,0,0,
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
};
const int tetramino_S_270[] = 
{
    0,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
};
const int tetramino_Z_0[] =
{
    0,0,0,0,
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,
};

const int tetramino_Z_90[] =
{
    0,1,0,0,
    0,1,1,0,
    0,0,1,0,
    0,0,0,0,
};

const int tetramino_Z_180[] =
{
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
    0,0,0,0,
};

const int tetramino_Z_270[] =
{
    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,
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
    0,0,0,0,
    1,1,1,0,
    0,1,0,0,
    0,0,0,0,
};
const int tetramino_T_90[] = 
{
    0,1,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,
};
const int tetramino_T_180[] = 
{
    0,1,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0,
};
const int tetramino_T_270[] = 
{
    0,1,0,0,
    0,1,1,0,
    0,1,0,0,
    0,0,0,0,
};

const Color color_types[8] =
{
    {255,255,0,255},        //YELLOW
    {0,0,255,255},          //BLUE
    {0,255,0,255},          //GREEN
    {128,0,128,255},        //PURPLE
    {204,0,77,255},         //RED
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

tetromino* init_tetromino(tetromino *tetr, Color col, const int* rot_0, const int* rot_90,const int* rot_180,const int* rot_270)
{
    tetr->color = col;
    for (int i = 0; i < 16; i++)
    {
        tetr->rotations[0][i] = rot_0[i];
        tetr->rotations[1][i] = rot_90[i];
        tetr->rotations[2][i] = rot_180[i];
        tetr->rotations[3][i] = rot_270[i];
    }

    return NULL;
}

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
            points_counter += POINTS_FOR_LINES;
            if (points_counter <= ENDLESS_POINT && points_counter >= highscore_for_next_level)
            {
                time_speed += 1;
                highscore_for_next_level += POINTS_FOR_LINES * 2;
                level +=1;
                TraceLog(LOG_INFO, "FASTER!! next objective : %d, falling speed : %f", highscore_for_next_level, time_speed);
            }
            current_state = FADING_STATE;
            line_to_delete = i;
            lines_to_delete[down_line] = i;
            down_line++;
        }
    }
}

int main(int argc, char **argv)
{
    current_state = MENU_STATE;

    const int stage_offset_x = WINDOW_WIDTH / 2 - STAGE_WIDTH / 2 * TILE_SIZE;          //better to use /2 when using int cause are faster than using *0.5, float operation are slower
    const int stage_offset_y = WINDOW_HEIGHT / 2 - STAGE_HEIGHT / 2 * TILE_SIZE;

    const int start_tetr_x = STAGE_WIDTH / 2;                                           //we want this in cells
    const int start_tetr_y = 0; 

    int current_tetr_x = start_tetr_x;
    int current_tetr_y = start_tetr_y;

    time_t unix_time;
    time(&unix_time);
    
    SetRandomSeed(unix_time);

    const int next_tetr_x = 25;
    const int next_tetr_y = 11;

    int next_tetr_type = GetRandomValue(0,6);
    int next_tetr_rot = 0;
    int next_tetr_color = GetRandomValue(0,6);

    int current_tetr_type = GetRandomValue(0,6);
    int current_tetr_rot = 0;
    int current_color = GetRandomValue(0, 7);

    float wait_for_falling = 1.5;
    float fall_down_timer = wait_for_falling;
    float stop_falling_timer = STOP_FALLING_TIMER;

    //tetromino tetr_l;
    //init_tetromino(&tetr_l, color_types[0], tetramino_L_0, tetramino_L_90,tetramino_L_180,tetramino_L_270);

    environment_init("Tetris");

    Music* background_music = environment_init_music("Assets/Background_music.ogg", true);
    Sound* block_fall_sound = environment_init_sound("Assets/Block_fall_sound.wav");

    PlayMusicStream(*background_music);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(*background_music);

        switch(current_state)
        {
            case MENU_STATE:
            if(IsKeyPressed(KEY_SPACE)) current_state = GAME_STATE;
            break;
            case GAME_STATE:
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

                    PlaySound(*block_fall_sound);
                    deleteLine();

                    current_tetr_x = start_tetr_x;
                    current_tetr_y = start_tetr_y;
                    current_tetr_type = next_tetr_type;
                    current_color = next_tetr_color;

                    next_tetr_type = GetRandomValue(0,6);
                    next_tetr_color = GetRandomValue(0,7);
                }
            }

            if (IsKeyPressed(KEY_D))
            {
                if (!checkCollision(current_tetr_x + 1, current_tetr_y, /*tetr_l.rotations[current_tetr_rot]*/tetramino_types[current_tetr_type][current_tetr_rot]))       //the wall "1" prevent overflow
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
            break;
            case FADING_STATE:
            stop_falling_timer = stop_falling_timer - GetFrameTime();

            if (stop_falling_timer < 0)
            {
                //const int offset = line_to_delete * STAGE_WIDTH + 1;
                current_state = GAME_STATE;
                stop_falling_timer = STOP_FALLING_TIMER;
                for (int i = 0; i < down_line; i++)
                {
                    const int offset = lines_to_delete[i] * STAGE_WIDTH + 1;

                    if (lines_to_delete[i])
                    {
                        memset(stage + offset, 0, (STAGE_WIDTH - 2) * sizeof(int)); //where to begin, what to write, for how much   
                        linesFall(lines_to_delete[i]);
                        lines_to_delete[i] = 0;
                    }
                }

                down_line = 0;
            }
            break;
        }
        
        BeginDrawing();
        
        const Color background_color = {200, 200, 200, 255};
        ClearBackground(background_color);

        drawTetraminos(current_tetr_x, current_tetr_y, tetramino_types[current_tetr_type][current_tetr_rot], stage_offset_x, stage_offset_y, color_types[current_color]);
        //drawTetraminos(current_tetr_x, current_tetr_y, tetr_l.rotations[current_tetr_rot], stage_offset_x, stage_offset_y, tetr_l.color);
        
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
        
        if (current_state == FADING_STATE)
        {
            for (int i = 0; i < down_line; i++)
            {
                if ((int)(stop_falling_timer * 10) % 2 == 0)
                {
                    DrawRectangle(stage_offset_x + text_deleting_pos_x * TILE_SIZE,lines_to_delete[i] * TILE_SIZE + stage_offset_y, TILE_SIZE * 10, TILE_SIZE, WHITE);
                }
            }
        }
        
        if (current_state == MENU_STATE) DrawText("PRESS SPACE TO BEGIN!",20, 258,36, WHITE);

        DrawRectangleLines(next_tetr_x * TILE_SIZE - TILE_SIZE,next_tetr_y * TILE_SIZE - TILE_SIZE, 5*TILE_SIZE, 5*TILE_SIZE, BLACK);
        drawTetraminos(next_tetr_x, next_tetr_y, tetramino_types[next_tetr_type][next_tetr_rot], 0, 0, color_types[next_tetr_color]);
        DrawText("NEXT", next_tetr_x * TILE_SIZE, next_tetr_y * TILE_SIZE - TILE_SIZE, 16, BLACK);

        EndDrawing();
    }

    environment_unload_music(*background_music);
    environment_unload_sound(*block_fall_sound);
    environment_close();


    return 0;
}