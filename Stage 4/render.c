/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: render.c
 SUMMARY: handles game rendering.
*************************************
******************************************/

#include <osbind.h>
#include "render.h"


/*******************************************************************************
    PURPOSE: Main Render function that draws the screen
    INPUT:   - const Model *model, the model of the world
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render(Model *model, unsigned long *base){ /* TODO - replace unsigned long base with UINT32 constant from constants.h*/
    clear_screen();
    drawline(0,640,GROUND_BASE); /*draw ground*/
    render_spikes(model, base);
    render_blocks(model, base);
    render_player(&model->Player, base);
    render_goal(&model->Goal, base);
    /* render portal*/ 
}

/*******************************************************************************
    PURPOSE: Helper render function that draws the spikes
    INPUT:   - const Model *model, the model that holds the spikes array
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render_spikes(Model *model, unsigned long *base){
    int i;
    for(i = 0; i<model->Spikecount; i++){
        /* example: check if spike in bounds here... e.g.*/
        /*if(in_bounds(model.Spikes[i].x && model.spikes.y))... render, else ignore*/
        plot_bitmap_32(base, model->Spikes[i].x, model->Spikes[i].y, ground_spike);
    }
}
/*******************************************************************************
    PURPOSE: Helper render function that draws the blocks
    INPUT:   - const Model *model, the model that holds the block array
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render_blocks(Model *model, unsigned long *base){
    int i = 0;
    for(i = 0; i<model->Blockcount; i++){
        /*read above in render_all_spikes*/
        plot_bitmap_32(base, model->Blocks[i].x, model->Blocks[i].y, ground_block);
    }
}

/*******************************************************************************
    PURPOSE: Helper render function that draws the player
    INPUT:   - const Player *player, the player object
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render_player(Player *player, unsigned long *base){
    plot_bitmap_32(base, player->entity.x, player->entity.y, square);
}

void render_goal(GameObject *object, unsigned long *base){
    plot_bitmap_32(base, object->x, object->y, portal_bitmap);
}
