#include "Tetris.h"

void linesFall(int start_line_y);

int points_counter = 0;
int level = 1;              
int highscore_for_next_level = 200;

float blink_time = STOP_FALLING_TIMER;
float time_speed = 4.0;
float text_deleting_pos_x = 1;

int line_to_delete = 0;
int lines_to_delete[4];
int down_line = 0;

int current_state;

const int tetromino_L_0[] = 
{
    0,1,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,0,0
};
const int tetromino_L_90[] = 
{
    0,0,0,0,
    1,1,1,0,
    1,0,0,0,
    0,0,0,0
};
const int tetromino_L_180[] = 
{
    1,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,0,0,0
};
const int tetromino_L_270[] = 
{
    0,0,1,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0
};

const int tetromino_J_0[] = 
{
    0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0
};
const int tetromino_J_90[] = 
{
    1,0,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0
};

const int tetromino_J_180[] = 
{
    0,1,1,0,
    0,1,0,0,
    0,1,0,0,
    0,0,0,0
};
const int tetromino_J_270[] = 
{
    0,0,0,0,
    1,1,1,0,
    0,0,1,0,
    0,0,0,0
};
const int tetromino_O_0[] = 
{
    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0
};

const int tetromino_S_0[] = 
{
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
    0,0,0,0
};
const int tetromino_S_90[] = 
{
    0,0,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,1,0
};
const int tetromino_S_180[] = 
{
    0,0,0,0,
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
};
const int tetromino_S_270[] = 
{
    0,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
};
const int tetromino_Z_0[] =
{
    0,0,0,0,
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,
};

const int tetromino_Z_90[] =
{
    0,1,0,0,
    0,1,1,0,
    0,0,1,0,
    0,0,0,0,
};

const int tetromino_Z_180[] =
{
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
    0,0,0,0,
};

const int tetromino_Z_270[] =
{
    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,
};
const int tetromino_I_0[] = 
{
    0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0
};
const int tetromino_I_90[] = 
{
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0
};
const int tetromino_I_180[] = 
{
    0,0,0,0,
    1,1,1,1,
    0,0,0,0,
    0,0,0,0
};
const int tetromino_I_270[] = 
{
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0
};
const int tetromino_T_0[] = 
{
    0,0,0,0,
    1,1,1,0,
    0,1,0,0,
    0,0,0,0,
};
const int tetromino_T_90[] = 
{
    0,1,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,
};
const int tetromino_T_180[] = 
{
    0,1,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0,
};
const int tetromino_T_270[] = 
{
    0,1,0,0,
    0,1,1,0,
    0,1,0,0,
    0,0,0,0,
};

const Color color_types[9] =
{
    {255,255,0,255},        //YELLOW
    {0,0,255,255},          //BLUE
    {0,255,0,255},          //GREEN
    {128,0,128,255},        //PURPLE
    {204,0,77,255},         //RED
    {255,0,255,255},        //MAGENTA
    {0,255,255,255},        //CYAN
    {255,165,0,255},        //ORANGE
    {200,200,200,255}       //BACKGROUND
};

const int *tetromino_types[7][4] =
{
    {tetromino_I_0, tetromino_I_90, tetromino_I_180,tetromino_I_270},
    {tetromino_J_0, tetromino_J_90, tetromino_J_180, tetromino_J_270},
    {tetromino_Z_0, tetromino_Z_90, tetromino_Z_180,tetromino_Z_270},
    {tetromino_S_0, tetromino_S_90, tetromino_S_180,tetromino_S_270},
    {tetromino_O_0, tetromino_O_0, tetromino_O_0,tetromino_O_0},
    {tetromino_L_0, tetromino_L_90, tetromino_L_180,tetromino_L_270},
    {tetromino_T_0, tetromino_T_90, tetromino_T_180,tetromino_T_270},
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

void drawTetromino(const tetromino* tetr, const int stage_x_offset, const int stage_y_offset)
{
    for (int i = 0; i < TETROMINO_SIZE; i++)
    {
        for (int j = 0; j < TETROMINO_SIZE; j++)
        {
            if((tetromino_types[tetr->type][tetr->rotation])[j+i*TETROMINO_SIZE] >= 1)
            {
                    DrawRectangle((tetr->position.x + j )* TILE_SIZE + stage_x_offset,(tetr->position.y + i) * TILE_SIZE + stage_y_offset, TILE_SIZE, TILE_SIZE, color_types[tetr->color]);
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

void update(tetromino* current_tetr, tetromino* next_tetr, float* fall_down_timer, Sound* block_fall_sound)
{
    *fall_down_timer = (*fall_down_timer) - GetFrameTime() * time_speed;
    if (IsKeyPressed(KEY_SPACE))
    {
        const int last_rot = current_tetr->rotation;

        current_tetr->rotation++;
        if (current_tetr->rotation > 3)
        {
            current_tetr->rotation = 0;
        }
                
        if (checkCollision(current_tetr->position.x, current_tetr->position.y, tetromino_types[current_tetr->type][current_tetr->rotation]))
        {
            current_tetr->rotation = last_rot;
        }
    }
            
    if (*fall_down_timer < 0 || IsKeyPressed(KEY_S))
    {
        const int next_offset_y_position = current_tetr->position.x + (current_tetr->position.y + 1) * STAGE_WIDTH;

        if (!checkCollision(current_tetr->position.x, current_tetr->position.y + 1, tetromino_types[current_tetr->type][current_tetr->rotation]))
        {
            current_tetr->position.y++;
           *fall_down_timer = WAIT_FOR_FALLING;
        }
        else
        {
            for (int i = 0; i < TETROMINO_SIZE; i++)
            {
                for (int j = 0; j < TETROMINO_SIZE; j++)
                {
                    const int tile_index = i * TETROMINO_SIZE + j;
                    const int* tetr = tetromino_types[current_tetr->type][current_tetr->rotation];
                        
                    if (tetr[tile_index] >= 1)
                    {
                        const int offset_stage = (i + current_tetr->position.y) * STAGE_WIDTH + (j + current_tetr->position.x);
                        stage[offset_stage] = current_tetr->color + 1;            //save current color, previous 1, we need to change the ==1 to >= 1, 0 it's not a value that we can consider
                    }
                }
            }

            PlaySound(*block_fall_sound);
            deleteLine();

            current_tetr->position.x = STAGE_WIDTH / 2;
            current_tetr->position.y = 0;
            current_tetr->type = next_tetr->type;
            current_tetr->color = next_tetr->color;

            next_tetr->type = GetRandomValue(0,6);
            next_tetr->color = GetRandomValue(0,7);
        }
    }

    if (IsKeyPressed(KEY_D))
    {
        if (!checkCollision(current_tetr->position.x + 1, current_tetr->position.y, tetromino_types[current_tetr->type][current_tetr->rotation]))       //the wall "1" prevent overflow
        {
            current_tetr->position.x++;
        }
    }

    if (IsKeyPressed(KEY_A))
    {
        if (!checkCollision(current_tetr->position.x - 1, current_tetr->position.y, tetromino_types[current_tetr->type][current_tetr->rotation]))       //the wall "1" prevent overflow
        {
            current_tetr->position.x--;
        }
    }
}

void fading(float* stop_falling_timer)
{
    *stop_falling_timer = *stop_falling_timer - GetFrameTime();

            if (*stop_falling_timer < 0)
            {
                current_state = GAME_STATE;
                *stop_falling_timer = STOP_FALLING_TIMER;
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
}

void draw(const tetromino* current_tetr,const tetromino* next_tetr,const int stage_offset_x, const int stage_offset_y, float stop_falling_timer)
{
        BeginDrawing();
        
        ClearBackground(color_types[COLOR_BACKGROUND]);

        drawTetromino(current_tetr, stage_offset_x, stage_offset_y);
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

        DrawRectangleLines(next_tetr->position.x * TILE_SIZE - TILE_SIZE,next_tetr->position.y * TILE_SIZE - TILE_SIZE, 5*TILE_SIZE, 5*TILE_SIZE, BLACK);
        drawTetromino(next_tetr, 0, 0);
        DrawText("NEXT", next_tetr->position.x * TILE_SIZE, next_tetr->position.y * TILE_SIZE - TILE_SIZE, 16, BLACK);

        EndDrawing();
}

int main(int argc, char **argv)
{
    current_state = MENU_STATE;

    const int stage_offset_x = WINDOW_WIDTH / 2 - STAGE_WIDTH / 2 * TILE_SIZE;          //better to use /2 when using int cause are faster than using *0.5, float operation are slower
    const int stage_offset_y = WINDOW_HEIGHT / 2 - STAGE_HEIGHT / 2 * TILE_SIZE;

    time_t unix_time;
    time(&unix_time);
    
    SetRandomSeed(unix_time);

    tetromino current_tetr;
    current_tetr.position.x = STAGE_WIDTH / 2; 
    current_tetr.position.y = 0; 
    current_tetr.rotation = 0;
    current_tetr.type = GetRandomValue(0,6);
    current_tetr.color = GetRandomValue(0,6);
    
    tetromino next_tetr;
    next_tetr.position.x = 25;
    next_tetr.position.y = 11;
    next_tetr.rotation = 0;
    next_tetr.type = GetRandomValue(0,6);
    next_tetr.color = GetRandomValue(0,6);

    float fall_down_timer = WAIT_FOR_FALLING;
    float stop_falling_timer = STOP_FALLING_TIMER;

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
            update(&current_tetr, &next_tetr, &fall_down_timer, block_fall_sound);
            break;

            case FADING_STATE:
            fading(&stop_falling_timer);
            break;
        }
        
        draw(&current_tetr, &next_tetr, stage_offset_x, stage_offset_y, stop_falling_timer);
    }

    environment_unload_music(*background_music);
    environment_unload_sound(*block_fall_sound);
    environment_close();

    return 0;
}