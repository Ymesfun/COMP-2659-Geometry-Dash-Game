/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: render.c
 SUMMARY: handles game rendering.
*******************************************************************************/
#include <osbind.h>
#include "render.h"
#include "model.h"
static int state = 0; /*Using state design seems best for this.*/


void reg_clear(Model *model){
    int i;
    /* erase player */
    screen_region_clear_32(model->Player.entity.prev_y, model->Player.entity.prev_x);
    model->Player.entity.prev_x = model->Player.entity.x;
    model->Player.entity.prev_y = model->Player.entity.y;
    /* erase blocks */
    for(i=0; i<model->Blockcount; i++){
        if(prev_bounded(model->Blocks[i].prev_x,model->Blocks[i].prev_y)){
            screen_region_clear_32(model->Blocks[i].prev_y, model->Blocks[i].prev_x);
        }
        if(model->Blocks[i].movestate == true){
            model->Blocks[i].prev_x = model->Blocks[i].x;
            model->Blocks[i].prev_y = model->Blocks[i].y;
        }        
    }

    /* erase spikes */
    for(i=0; i<model->Spikecount; i++){
        if(prev_bounded(model->Spikes[i].prev_x,model->Spikes[i].prev_y)){
            screen_region_clear_32(model->Spikes[i].prev_y, model->Spikes[i].prev_x);
        }
        if(model->Spikes[i].movestate == true){
            model->Spikes[i].prev_x = model->Spikes[i].x;
            model->Spikes[i].prev_y = model->Spikes[i].y;
        }  
    }
    /* erase hanging spikes */
    for(i=0; i<model->Hangingspikecount; i++){
        if(prev_bounded(model->HangingSpike[i].prev_x,model->HangingSpike[i].prev_y)){
            screen_region_clear_32(model->HangingSpike[i].prev_y, model->HangingSpike[i].prev_x);
        }
        if(model->HangingSpike[i].movestate == true){
            model->HangingSpike[i].prev_x = model->HangingSpike[i].x;
            model->HangingSpike[i].prev_y = model->HangingSpike[i].y;
        }  
    }
    /* erase platforms */
    for(i=0; i<model->Platformcount; i++){
        if(prev_bounded(model->platforms[i].prev_x,model->platforms[i].prev_y)){
            screen_region_clear_32(model->platforms[i].prev_y, model->platforms[i].prev_x);
        }
        if(model->platforms[i].movestate == true){
            model->platforms[i].prev_x = model->platforms[i].x;
            model->platforms[i].prev_y = model->platforms[i].y;
        }  
    }
    /* erase goal */
    if(prev_bounded(model->Goal.prev_x,model->Goal.prev_y)){
        screen_region_clear_32(model->Goal.prev_y, model->Goal.prev_x);
    }
    if(model->Goal.movestate == true){
        model->Goal.prev_x = model->Goal.x;
        model->Goal.prev_y = model->Goal.y;
    }
}

/*******************************************************************************
    PURPOSE: Main Render function that draws the screen
    INPUT:   - const Model *model, the model of the world
              - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render(Model *model, unsigned long *base){ /* TODO - replace unsigned long base with UINT32 constant from constants.h*/
    if(state == 0){
        clear_screen();
    }else{
        reg_clear(model);
    }
    if(state < 1){
        drawline(0,640,GROUND_BASE); /*draw ground*/
        state ++;
    }
    render_player(&model->Player, base);
    render_spikes(model, base);
    render_blocks(model, base);
    if(model->Goal.render){
        render_goal(&model->Goal, base);
    }
    /* Commented out to prevent bugs
    render_hanging_spike(model, base);
    render_platform(model, base);
    */ 
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
        if(model->Spikes[i].render){
        plot_bitmap_32(base, model->Spikes[i].x, model->Spikes[i].y, ground_spike);
        }
    }
}

void render_hanging_spike(Model *model, unsigned long *base){
    int i;
    for(i = 0; i<model->Hangingspikecount; i++){
        /* example: check if spike in bounds here... e.g.*/
        /*if(in_bounds(model.Spikes[i].x && model.spikes.y))... render, else ignore*/
        if(model->HangingSpike[i].render){
            plot_bitmap_32(base, model->HangingSpike[i].x, model->HangingSpike[i].y, hanging_spike);
        }
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
        if(model->Blocks[i].render){
            plot_bitmap_32(base, model->Blocks[i].x, model->Blocks[i].y, ground_block);
        }
    }
}
    
void render_platform(Model *model, unsigned long *base){
    int i = 0;
    for(i = 0; i<model->Platformcount; i++){
        /*read above in render_all_spikes*/
            if(model->platforms[i].render){
            plot_bitmap_32(base, model->platforms[i].x, model->platforms[i].y, platform_bitmap);
            } 
        }
    }
        
/*******************************************************************************
    PURPOSE: Helper render function that draws the player
    INPUT:   - const Player *player, the player object
            - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render_player(Player *player, unsigned long *base){
        /*if(player->alive){*/
        plot_bitmap_32(base, player->entity.x, player->entity.y, square);
    }

void render_goal(GameObject *object, unsigned long *base){
    plot_bitmap_32(base, object->x, object->y, portal_bitmap);
}

