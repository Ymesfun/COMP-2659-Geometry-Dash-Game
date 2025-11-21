#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "model.h"
#include "bitmaps.h"


#define GROUND_BASE 338

void render(Model *model, unsigned long *base);
void render_spikes(Model *model, unsigned long *base);
void render_player(Player *player, unsigned long *base);
void render_blocks(Model *model, unsigned long *base);
void render_goal(GameObject *object, unsigned long *base);
void render_platform(Model *model, unsigned long *base);
void render_hanging_spike(Model *model, unsigned long *base);

#endif