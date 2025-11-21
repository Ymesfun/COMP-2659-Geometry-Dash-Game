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
    for(i=0;i<Model->blockcount;i++){
        if(platform_collision(Model->player,Model->blocks[i])){ // and block is on screen call screen region check 
            player_death(Model->player);
        } else{
            player_on_platform(Model->player,Model->blocks[i]); // and block is on screen call screen region check 
        }
    }
    for(i = 0;i<Model->spikecount;i++){
        if(object_collisioncheck(Model->player, Model->spikes[i])){ // and block is on screen call screen region check 
            player_death(Model->player);
        }
    }
    if(object_collisioncheck(Model->player,Model->goal)){
        portal(Model->player);
        player_idle(&Model->Player);
        // change state to frozen
        return; /*May not be the best choice, finalize how you may escape after hitting the portal.*/
    }
    player_move(Model->player);
    for(i = 0;i<Model->spikecount;i++){
        object_move(Model->spikes[i]);    
    }
    for(i=0;i<Model->blockcount;i++){
        object_move(Model->blocks[i]);
    }
}
