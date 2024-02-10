#ifndef PHYSICS_H
#define PHYSICS_H

/// @brief Check collision between tetraminos and grid
/// @param tetr_start_x 
/// @param tetr_start_y 
/// @param tetr 
/// @return 
int checkCollision(const int tetr_start_x, const int tetr_start_y, const int* tetr);

/// @brief Simulate gravity on blocks when the line under them is deleted
/// @param start_line_y 
void linesFall(int start_line_y);

#endif  //PHYSICS_H