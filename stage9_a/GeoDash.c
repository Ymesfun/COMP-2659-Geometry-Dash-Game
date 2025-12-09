/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 30, 2025

 FILE: GeoDash.c
 SUMMARY: Contains the main game loop with integrated menu system
*******************************************************************************/

#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "render.h"
#include "bitmaps.h"
#include "Gosplash.h"
#include "w_splash.h"
#include "m_splash.h"
#include "events.h"
#include "model.h"
#include "GeoDash.h"
#include "kbd_ISR.h"


/* Function prototypes */
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT32* orig_buffer, UINT8 back_buffer_array[]);
void initialize_first_stage(Model *model);
PlayerState main_menu(UINT32 *base);
PlayerState winner_menu(UINT32 *base);
PlayerState play_again_menu(UINT32 *base);
PlayerState menu_state_machine(PlayerState state, UINT32 *base, UINT32 *back_buffer);
void run_game(Model *model, UINT32 *back_buffer, UINT32 *front_buffer);
void reg_clear(Model *model, UINT32 *base);

UINT8 allocated_buffer[32260];



/*******************************************************************************
    PURPOSE: Main function with menu system integration
*******************************************************************************/
int main() {
    Model model;
    UINT32 *back_buffer, *front_buffer;
    UINT32* orig_buffer = Physbase();
    PlayerState current_state = STATE_START;

    install_ikbd_isr();
    set_buffers(&back_buffer, &front_buffer, orig_buffer, allocated_buffer);
    
    /* Main program loop - handles menu navigation */
    while (current_state != STATE_QUIT) {
        current_state = menu_state_machine(current_state, front_buffer, back_buffer);
        cleeeeer_screen(front_buffer);
        cleeeeer_screen(back_buffer);
        if (current_state == STATE_IDLE) {
            /* Initialize and run the game */
            initialize_first_stage(&model);
            run_game(&model, back_buffer, front_buffer);
            
            /* Determine next state based on game outcome */
            if (model.Player.goal) {
                current_state = STATE_WINNER;
            } else if (!model.Player.alive) {
                current_state = STATE_DEAD;
            }
        }
    }
    /* restores ISR */
    restore_ikbd_isr();

    Setscreen(-1, orig_buffer, -1);
    return 0;
}

/*******************************************************************************
    PURPOSE: Main game loop function
*******************************************************************************/
void run_game(Model *model, UINT32 *back_buffer, UINT32 *front_buffer) {
    bool curr_front = true;
    unsigned long time_then, time_now, time_elapsed;
   
    /* STATIC RENDERS */
    render_progress_bar(model, back_buffer);
    render_bitmap(model, back_buffer);
    plot_bitmap(back_buffer, 0, 335, ground_background, 640, 65); 
    
    render_progress_bar(model, front_buffer);
    render_bitmap(model, front_buffer);
    plot_bitmap(front_buffer, 0, 335, ground_background, 640, 65);

    
    time_then = get_time();
    
    while (model->Player.alive && !model->Player.goal) {
        int ch;
        ch = KBD_scancode_var & 0x7F; /* Converts the full scan code with MAKE and BREAK to just make*/
        KBD_scancode_var = 0;  
        
        if (ch == SPACE_SCANCODE) {
            model->Player.jump_pressed = true;
        }
        
        time_now = get_time();
        time_elapsed = time_now - time_then;
        
        if (time_elapsed > 0) {
            if (model->Player.jump_pressed) {
                player_jump(&model->Player);
                model->Player.jump_pressed = false;
            }
            update_game_model(model);
            time_then = time_now;
            
            if (curr_front == true) {
                render(model, back_buffer);
                Setscreen(-1, back_buffer, -1);
                curr_front = false;
            } else {
                render(model, front_buffer);
                Setscreen(-1, front_buffer, -1);
                curr_front = true;
            }
            
            Vsync();
        }
    }
}

/*******************************************************************************
    PURPOSE: Main menu screen
    OUTPUT: Returns next state (STATE_IDLE to play, or exits program)
*******************************************************************************/
PlayerState main_menu(UINT32 *base) {
    char ch;
    char dxx;
    char dyy;
    

    draw_splash_screen(splash_mainmenu);
    Vsync();
    
    while (1) {
    

        ch = KBD_scancode_var;
        ch = KBD_scancode_var & 0x7F; /* Converts the full scan code with MAKE and BREAK to just make*/
        KBD_scancode_var = 0;

        
        if (ch == ESC_SCANCODE) {
            return STATE_QUIT;
        } else if (ch == KEY_1_SCANCODE) {
            cleeeeer_screen(base);

            
            return STATE_IDLE;
        }
    }
}

/*******************************************************************************
    PURPOSE: Winner screen
    OUTPUT: Returns STATE_START to return to main menu
*******************************************************************************/
PlayerState winner_menu(UINT32 *base) {
    int ch;
    

    draw_splash_screen(splash_winner);
    Vsync();
    
    while (1) {
        ch = KBD_scancode_var;
        ch = KBD_scancode_var & 0x7F; /* Converts the full scan code with MAKE and BREAK to just make*/
        KBD_scancode_var = 0;

        if (ch == KEY_1_SCANCODE) {
            return STATE_START;
        } else if (ch == ESC_SCANCODE) { 
            return STATE_QUIT;
        }
    }
}

/*******************************************************************************
    PURPOSE: Game over screen
    OUTPUT: Returns STATE_IDLE to retry or STATE_START for main menu
*******************************************************************************/
PlayerState play_again_menu(UINT32 *base) {
    int ch;
    
    /*clr_screen(base); */
    cleeeeer_screen(base);
    draw_splash_screen(splash_gameover);
    Vsync();
    
    while (1) {
        ch = KBD_scancode_var;
        ch = KBD_scancode_var & 0x7F; /* Converts the full scan code with MAKE and BREAK to just make*/
        KBD_scancode_var = 0;

        if (ch == KEY_1_SCANCODE) {
            cleeeeer_screen(base);
            return STATE_IDLE;  /* Play again */
        } else if (ch == KEY_2_SCANCODE) {
            cleeeeer_screen(base);
            return STATE_START;  /* Main menu */
        } else if (ch == ESC_SCANCODE) {
            return STATE_QUIT;
        }
    }
    
}

/*******************************************************************************
    PURPOSE: State machine to handle menu navigation
    OUTPUT: Returns the next state based on current state
*******************************************************************************/
PlayerState menu_state_machine(PlayerState state, UINT32 *base, UINT32 *back_buffer) {


    switch (state) {
        case STATE_DEAD:
            return play_again_menu(base);
        case STATE_WINNER:
            return winner_menu(base);
        case STATE_START:
            return main_menu(base);
        default:
            return state;
    }
}

/*******************************************************************************
    PURPOSE: Gets current system time
    OUTPUT: Time in clock ticks
*******************************************************************************/
UINT32 get_time() {
    UINT32 time_now;
    UINT32 old_ssp;
    UINT32 *timer = (UINT32 *)0x462;
    
    old_ssp = Super(0);
    time_now = *timer;
    Super(old_ssp);
    
    return time_now;
}

/*******************************************************************************
    PURPOSE: Initializes back and front buffer pointers for double buffering
*******************************************************************************/
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT32* orig_buffer, UINT8 back_buffer_array[]) {
    UINT32 address;
    UINT8 *temp = back_buffer_array;
    
    while (1) {
        address = (UINT32) temp;
        address &= 0xff;
        if (address == 0) {
            break;
        }
        temp++;
    }
    
    *back_buffer = (UINT32*)temp;
    *front_buffer = orig_buffer;
}

/*******************************************************************************
    PURPOSE: Initialize game objects for first stage
*******************************************************************************/
void initialize_first_stage(Model *model) {
    int i, x, y;
    model->Blockcount = 4;
    model->Spikecount = 4;
    model->Hangingspikecount = 1;
    model->crystalcount = 1;
    model->Platformcount = 1;
   
    initialize_player_obj(&model->Player, 50, FLOOR, 0);
    initialize_goal_gameobj(&model->Goal, 1000, FLOOR, 7);
    
    
    for (i = 0; i < model->Spikecount; i++) {
        x = 465 + i * 180;
        y = FLOOR;
        initialize_spike_gameobj(&model->Spikes[i], x, y, 7);
    }
    
    for (i = 0; i < model->Blockcount; i++) {
        x = 512 + i * 180;
        y = FLOOR;
        initialize_block_gameobj(&model->Blocks[i], x, y, 7);
    }

     for (i = 0; i < model->Hangingspikecount; i++) {
        x = 600 + i * 180;
        y = 190;
        initialize_hanging_spike_gameobj(&model->HangingSpike[i], x, y, 7);
    }   

     for (i = 0; i < model->crystalcount; i++) {
        x = 650 + i * 180;
        y = FLOOR + 10;
        initialize_spike_gameobj(&model->crystalspike[i], x, y, 7);
    }

    
    for (i = 0; i < model->Platformcount; i++) {
        x = 570 + i * 180;
        y = 300;
        initialize_platform_gameobj(&model->platforms[i], x, y, 7);
    }

     
}
