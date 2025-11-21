/*******************************************************************************
 AUTHORS: Yaccob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: October 15, 2025

 FILE: rndtst.c
 SUMMARY: Tests renderings abilites via some test drawings.
*************************************
******************************************/

#include "rndtst.h"
#include "render.h"
#include <osbind.h>

/* call render functions here after initializing model*/
int main(){
    unsigned long * base = (unsigned long*)Physbase(); /*change to UINT32*/
    Model model;
    initialize_first_frame(&model);
    render(&model, base);
    return 0;
}

void initialize_first_frame(Model *model){
    model->Spikecount = num_spikes;
    model->Blockcount = num_blocks;
    initialize_player_obj(&model->Player, 50, GROUND_BASE-32,0);
    initialize_spike_gameobj(&model->Spikes[0],100,GROUND_BASE-32,0);
    initialize_block_gameobj(&model->Blocks[0],132,GROUND_BASE-32,0);
    initialize_block_gameobj(&model->Blocks[1],164,GROUND_BASE-32,0);
    initialize_spike_gameobj(&model->Spikes[1],164,GROUND_BASE-64,0);
    initialize_goal_gameobj(&model->Goal,320,GROUND_BASE-32,0);



    
}