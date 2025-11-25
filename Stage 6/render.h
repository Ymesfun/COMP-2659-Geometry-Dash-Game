#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "model.h"
#include "bitmaps.h"
#include "constant.h"


#define GROUND_BASE 338

void render(Model *model, UINT32 *base);
void render_spikes(Model *model, UINT32 *base);
void render_player(Player *player, UINT32 *base);
void render_blocks(Model *model, UINT32 *base);
void render_goal(GameObject *object, UINT32 *base);
void render_platform(Model *model, UINT32 *base);
void render_hanging_spike(Model *model, UINT32 *base);

#endif