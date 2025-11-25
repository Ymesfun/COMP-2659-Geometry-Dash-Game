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
static int ground = 0; /*Draw the ground twice*/

/*******************************************************************************
    PURPOSE: Main clear function that clears both buffers. A bit too aggressive,
             defaulting to full clear for full submission.
              - Model - memory address of our model
    OUTPUT:  - N/A
*******************************************************************************/
void reg_clear(Model *model){
    int i;
    /* erase player */
    screen_region_clear_32(model->Player.entity.prev_y[state], model->Player.entity.prev_x[state]);
    model->Player.entity.prev_x[state] = model->Player.entity.x;
    model->Player.entity.prev_y[state] = model->Player.entity.y;

    /* erase blocks */
    for(i=0; i<model->Blockcount; i++){
        if(!(model->Blocks[i].prev_x[state] == model->Blocks[i].x && model->Blocks[i].prev_y[state] == model->Blocks[i].y && model->Blocks[i].render == false)){
            if(prev_bounded(model->Blocks[i].prev_x[state],model->Blocks[i].prev_y[state])){
                screen_region_clear_32(model->Blocks[i].prev_y[state], model->Blocks[i].prev_x[state]);
            }
        model->Blocks[i].prev_x[state] = model->Blocks[i].x;
        model->Blocks[i].prev_y[state] = model->Blocks[i].y;
        }
    }

    /* erase spikes */
    for(i=0; i<model->Spikecount; i++){
        if(!(model->Spikes[i].prev_x[state] == model->Spikes[i].x && model->Spikes[i].prev_y[state] == model->Spikes[i].y && model->Spikes[i].render == false)){
            if(prev_bounded(model->Spikes[i].prev_x[state],model->Spikes[i].prev_y[state])){
                screen_region_clear_32(model->Spikes[i].prev_y[state], model->Spikes[i].prev_x[state]);
            }
            model->Spikes[i].prev_x[state] = model->Spikes[i].x;
            model->Spikes[i].prev_y[state] = model->Spikes[i].y;
        }
    }
    if(!(model->Goal.prev_x[state] == model->Goal.x && model->Goal.prev_y[state] == model->Goal.y && model->Goal.render == false)){
        if(prev_bounded(model->Goal.prev_x[state],model->Goal.prev_y[state])){
            screen_region_clear_32(model->Goal.prev_y[state], model->Goal.prev_x[state]);
        }
    }
    model->Goal.prev_x[state] = model->Goal.x;
    model->Goal.prev_y[state] = model->Goal.y;
    state = (state+1)&1; /*Instead of (state+1)%2, we can just and to find if were at index 0/1*/
}

/*******************************************************************************
    PURPOSE: Main Render function that draws the screen
    INPUT:   - const Model *model, the model of the world
              - UINT32*base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render(Model *model, UINT32 *base){
    /* This partial clear would be better, but it clears so fast things are invisbile.
    if(ground < 1){
        clear_screen();
    }else{
        reg_clear(model);
    }
    if(ground < ){
        drawline(0,640,GROUND_BASE); 
        ground ++;
    }
    */
    clear_screen();
    drawline(0,640,GROUND_BASE);
    /*Use partial clearing when it works better.*/
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
                - UINT32*base, the pointer to the frame buffer
        OUTPUT:  - N/A
    *******************************************************************************/
void render_spikes(Model *model, UINT32 *base){
    int i;
    for(i = 0; i<model->Spikecount; i++){
        /* example: check if spike in bounds here... e.g.*/
        /*if(in_bounds(model.Spikes[i].x && model.spikes.y))... render, else ignore*/
        if(model->Spikes[i].render){
        plot_bitmap_32(base, model->Spikes[i].x, model->Spikes[i].y, ground_spike);
        }
    }
}

void render_hanging_spike(Model *model, UINT32*base){
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
                - UINT32*base, the pointer to the frame buffer
        OUTPUT:  - N/A
    *******************************************************************************/
void render_blocks(Model *model, UINT32*base){
    int i = 0;
    for(i = 0; i<model->Blockcount; i++){
        /*read above in render_all_spikes*/
        if(model->Blocks[i].render){
            plot_bitmap_32(base, model->Blocks[i].x, model->Blocks[i].y, ground_block);
        }
    }
}
    
void render_platform(Model *model, UINT32*base){
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
            - UINT32*base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void render_player(Player *player, UINT32*base){
        /*if(player->alive){*/
        plot_bitmap_32(base, player->entity.x, player->entity.y, square);
    }

void render_goal(GameObject *object, UINT32*base){
    plot_bitmap_32(base, object->x, object->y, portal_bitmap);
}

