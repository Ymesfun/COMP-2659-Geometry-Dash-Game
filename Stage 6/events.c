/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: events.c
 SUMMARY: Handles game events and transitions.
*************************************
******************************************/



#include "events.h"
#include "model.h"


/*******************************************************************************
    PURPOSE: Moves the game world (Model, to be specific) by one tick/instance when called.
    INPUT:   - Model: memory address of the Mode holding the game world/elements
    OUTPUT:  - N/A
*******************************************************************************/
void update_game_model(Model *Model) { 
    Player *player = &Model->Player;
    int i;

    if (handle_platform_collisions(player, Model->Blocks, Model->Blockcount)) {
        if (!player->alive) return; 
    }

    for (i = 0; i < Model->Spikecount; i++) {
        if (object_collisioncheck(player, &Model->Spikes[i])) {
            player_death(player);
            return;
        }
    }
    if (object_collisioncheck(player, &Model->Goal)) {
        portal(player);
        player_idle(player);
        return;
    }

    player_move(player);

    for (i = 0; i < Model->Spikecount; i++){
        if(Model->Spikes[i].movestate){
            object_move(&Model->Spikes[i]);
        }
    }

    for (i = 0; i < Model->Blockcount; i++){
        if(Model->Blocks[i].movestate){
            object_move(&Model->Blocks[i]);
        }
    }
    /* Commented out to minimize what we would need to bugfix
    for (i = 0; i < Model->Platformcount; i++){
        if(Model->platforms[i].movestate){
            object_move(&Model->platforms[i]);
        }
    }
        */
    if(Model->Goal.movestate){
        object_move(&Model->Goal);
    }
}