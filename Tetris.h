#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define STAGE_WIDTH 12              //we can use define for const
#define STAGE_HEIGHT 22
#define TILE_SIZE 16
#define TETRAMINO_SIZE 4
#define POINTS_FOR_LINES 100
#define POINTS_POS_X 256
#define POINTS_POS_Y 10
#define ENDLESS_POINT 1000
#define STOP_FALLING_TIMER 1

int checkCollision(const int tetr_start_x, const int tetr_start_y, const int* tetr);