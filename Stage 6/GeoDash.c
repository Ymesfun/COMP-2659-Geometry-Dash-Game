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
#include <stdio.h>
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
void initialize_first_stage(Model *model);
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT32* orig_buffer, UINT8 back_buffer_array[]);

int main() {
    bool user_quit;
    Model model;   
    UINT8 allocated_buffer[32260];
    bool is_curr_buffer_front = true;
    char ch = '\0'; 
    unsigned long time_then, time_now, time_elapsed;
    UINT32 *back_buffer, *front_buffer;
    UINT32* orig_buffer = (UINT32*)Physbase();
    user_quit = false;
   

    initialize_first_stage(&model);
    time_then = get_time();
    set_buffers(&back_buffer, &front_buffer, orig_buffer, allocated_buffer);

    
    while (!user_quit) {
       ch = input_read();
        if (ch == JUMP_KEY) { /* spacebar*/
            model.Player.jump_pressed = true;
        }
        time_now = get_time();
        time_elapsed = time_now - time_then;

        if ( time_elapsed > 1) {
            if(model.Player.jump_pressed){
                player_jump(&model.Player);
                model.Player.jump_pressed = false;
            }
            update_game_model(&model);
            render(&model, orig_buffer);

            if(is_curr_buffer_front == true) {
				render(&model, back_buffer);
				Setscreen(-1,(UINT32)back_buffer,-1);
				is_curr_buffer_front = false;
            }   
			else {
				render(&model, front_buffer);
				Setscreen(-1,(UINT32)front_buffer,-1);
				is_curr_buffer_front = true;
			}
				
			Vsync();        

            if (!model.Player.alive || model.Player.goal) {
                break;
            }
            time_then = time_now;
        }
    }
    printf("Player status. jump = %d, jump dy = %d : Block Render Status: %d\n",model.Player.jump_pressed, model.Player.entity.dy,model.Blocks[0].render);
    
    Setscreen(-1, (UINT32)orig_buffer, -1);
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
	unsigned long  *timer = (unsigned long *)CLOCK_ADDR; /*address of a long word that is auto incremented 70 times per second */
	
	old_ssp = Super(0); /* enter privileged mode */
	time_now = *timer;
	Super(old_ssp); /* exit privileged mode */
	
	return time_now;

}

void initialize_first_stage(Model *model){
    int i, x, y;
    model->Blockcount = 2;
    model->Spikecount = 2;
    initialize_player_obj(&model->Player, 50, FLOOR,0);
    for(i = 0; i<model->Spikecount; i++){
        x = 180 + i * 180;       
        y = FLOOR;              
        initialize_spike_gameobj(&model->Spikes[i], x, y, 7);
    }
    for(i = 0; i<model->Blockcount; i++){
        x = 212 + i * 180;       
        y = FLOOR;              
        initialize_block_gameobj(&model->Blocks[i], x, y, 7);
    }
        initialize_goal_gameobj(&model->Goal,700,FLOOR,7);

}


void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT32* orig_buffer, UINT8 back_buffer_array[]) {

    UINT32 address;
    UINT8 *temp = back_buffer_array;

    while(1) {
        address = (UINT32) temp;
        address &= 0xff;
        if(address == 0) {
            break;
        }
        temp++;
    }

    *back_buffer =	(UINT32*)temp;
    *front_buffer = orig_buffer;
}


void initialize_first_frame(Model *model){
    model->Spikecount = NUM_SPIKES;
    model->Blockcount = NUM_BLOCKS;
    model->Hangingspikecount = NUM_HANGING_SPIKES;
    model->Platformcount = NUM_PLATFORMS;

    initialize_player_obj(&model->Player, 50, FLOOR,0);
    initialize_spike_gameobj(&model->Spikes[0],100+150,FLOOR,5);
    initialize_block_gameobj(&model->Blocks[0],132+150,FLOOR,5);
    initialize_block_gameobj(&model->Blocks[1],164+214,FLOOR,5);
    initialize_spike_gameobj(&model->Spikes[1],164+214+64,FLOOR,5);
    initialize_goal_gameobj(&model->Goal,320+125+100,FLOOR,5);
    /*initialize_platform_gameobj(&model->platforms[0],500,230,5);*/
   /* initialize_hanging_spike_gameobj(&model->HangingSpike[0],370,275,5); */
    

}