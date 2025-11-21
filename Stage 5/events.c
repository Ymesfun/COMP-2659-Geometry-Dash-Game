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
void update_game_model(Model *Model){ 
    int i;
    i = i+i;
    for(i=0;i<Model->Blockcount;i++){
        if(platform_collision(&Model->Player,&Model->Blocks[i]) == true){ /*should eventually not check unrendered objects*/
            player_death(&Model->Player);
        } else{
            player_on_platform(&Model->Player,&Model->Blocks[i]); 
            
        }
    }
    for(i = 0;i<Model->Spikecount;i++){
        if(object_collisioncheck(&Model->Player, &Model->Spikes[i]) == true){ 
            player_death(&Model->Player);
        }
    }

    for(i = 0;i<Model->Hangingspikecount;i++){
        if(object_collisioncheck(&Model->Player, &Model->HangingSpike[i]) == true){ 
            player_death(&Model->Player);
        }
    }
    if(object_collisioncheck(&Model->Player,&Model->Goal) == true){
        portal(&Model->Player);
        player_idle(&Model->Player);
        return;
    }
    player_move(&Model->Player);
    for(i = 0;i<Model->Spikecount;i++){
        object_move(&Model->Spikes[i]);    
    }
    for(i=0;i<Model->Blockcount;i++){
        object_move(&Model->Blocks[i]);
    }
    for(i=0;i<Model->Platformcount;i++){
        object_move(&Model->platforms[i]);
     
    object_move(&Model->Goal);
    }
}