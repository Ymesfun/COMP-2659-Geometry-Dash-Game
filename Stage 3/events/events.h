#ifndef EVENTS_H
#define EVENTS_H

#include "constant.h"
#include "model.h"

typedef enum {
   COLLISION_NONE = 0,
   SAFE_COLLISION = 1,
   COLLISION_HAZARD = 2,
   WIN_COLLISION = 3
} event;

void update_game_model(Model *Model);

#endif