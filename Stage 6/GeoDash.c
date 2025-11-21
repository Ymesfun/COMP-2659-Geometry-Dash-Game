/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 30, 2025

 FILE: GeoDash.c
 SUMMARY: Contains the main game loop where the games function calls are synched with the clocl
  and key input (asynch) is incorperated for game functionality.
*******************************************************************************/


#include <osbind.h>

#include "raster.h"
#include "render.h"
#include "bitmaps.h"
#include "events.h"
#include "model.h"
#include "GeoDash.h"
#include "input.h"

/*******************************************************************************
    PURPOSE: Main Render function that draws the screen
    INPUT:   - const Model *model, the model of the world
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
void initialize_first_frame(Model *model);


int main() {
    bool user_quit;
    Model  model;   
    
    char ch = '\0'; 
    unsigned long time_then, time_now, time_elapsed;
    unsigned long * base = (unsigned long*)Physbase();
    user_quit = false;
   

    initialize_first_frame(&model);
    time_then = get_time();

    
    while (!user_quit && model.Player.alive) {
       ch = input_read();
        if (ch == JUMP_KEY) { /* spacebar*/
            model.Player.jump_pressed = true;
        }
        else {
            model.Player.jump_pressed = false;  
        }   

        time_now = get_time();
        time_elapsed = time_now - time_then;

        if ( time_elapsed > 0) {
            if(model.Player.jump_pressed){
                player_jump(&model.Player);
            }
            update_game_model(&model);
            if (within_bounds){
            render(&model, base);
            }

           if (!model.Player.alive && model.Player.state == STATE_DEAD) {
                break;
            }
            time_then = time_now;
        }
    }

    return 0;
}

/*******************************************************************************
    PURPOSE: Main Render function that draws the screen
    INPUT:   - const Model *model, the model of the world
             - unsigned long *base, the pointer to the frame buffer
    OUTPUT:  - N/A
*******************************************************************************/
unsigned long get_time(){
	unsigned long  time_now;
	unsigned long  old_ssp;
	unsigned long  *timer = (unsigned long *)0x462; /*address of a long word that is auto incremented 70 times per second */
	
	old_ssp = Super(0); /* enter privileged mode */
	time_now = *timer;
	Super(old_ssp); /* exit privileged mode */
	
	return time_now;

}


void initialize_first_frame(Model *model){
    model->Spikecount = num_spikes;
    model->Blockcount = num_blocks;
    model->Hangingspikecount = num_hanging_spikes;
    model->Platformcount = num_platforms;

    initialize_player_obj(&model->Player, 50, FLOOR,0);
    initialize_spike_gameobj(&model->Spikes[0],100+50,FLOOR,5);
    initialize_block_gameobj(&model->Blocks[0],132+50,FLOOR,5);
    initialize_block_gameobj(&model->Blocks[1],164+50,FLOOR,5);
    initialize_spike_gameobj(&model->Spikes[1],164+50,FLOOR-32,5);
    initialize_goal_gameobj(&model->Goal,320+25,FLOOR,5);
    initialize_platform_gameobj(&model->platforms[0],355,230,5);
   /* initialize_hanging_spike_gameobj(&model->HangingSpike[0],370,275,5); */
    

}
