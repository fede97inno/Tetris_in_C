#include "environment.h"

void environment_init(const char* title)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title);
    InitAudioDevice();

    SetTargetFPS(60);
}

Music* environment_init_music(const char* path, bool looping)
{
    Music* music = (Music*)malloc(sizeof(Music));

    if (!music)
    {
        TraceLog(LOG_INFO, "Error in allocating memory for Music");
    }
    
    *music = LoadMusicStream(path);
    
    if (looping)
    {
        music->looping = 1;
    }
    
    return music;
}

Sound* environment_init_sound(const char* path)
{
    Sound* sound = (Sound*)malloc(sizeof(Sound));

    if (!sound)
    {
        TraceLog(LOG_INFO, "Error in allocating memory for Sound");
    }
    
    *sound = LoadSound(path);
    return sound;
}

void environment_unload_music(Music music)
{
    UnloadMusicStream(music);
}

void environment_unload_sound(Sound sound)
{
    UnloadSound(sound);
}

void environment_close()
{
    CloseAudioDevice();
    CloseWindow();
}