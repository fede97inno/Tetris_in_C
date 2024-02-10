#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

void environment_init(const char* title);
Music* environment_init_music(const char* path, bool looping);
Sound* environment_init_sound(const char* path);
void environment_unload_sound(Sound sound);
void environment_unload_music(Music music);
void environment_close();

#endif  // ENVIRONMENT_H