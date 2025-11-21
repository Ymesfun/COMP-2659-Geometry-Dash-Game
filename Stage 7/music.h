#ifndef MUSIC_H
#define MUSIC_H
#include "constant.h"


typedef struct{
    int tuning;
    UINT16 length;
} note;

void start_music();

void update_music(UINT32 time_elapsed);

#endif