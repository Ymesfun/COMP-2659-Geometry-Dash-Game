#include "effects.h"
#include "constant.h"
#include "psg.h"



/*******************************************************************************
    PURPOSE: Plays the "death" sound given a player death asynchronous event.
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void play_death(){
    /*Experiment:*/
    enable_channel(CH_C,off,on);
    set_noise(8);
    set_envelope(HIT_SOUND,HIT_SHAPE);
    set_volume(CH_C,ENV_ENABLE);
    set_tone(CH_C,EFFECTS_TONE);
    enable_channel(CH_C,1,0);
}

/*******************************************************************************
    PURPOSE: Plays the jump sound given a player jump asynchronous event.
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void play_jump(){
    set_envelope(JUMP_SOUND,JUMP_SHAPE);
    set_volume(CH_C,ENV_ENABLE);
    set_tone(CH_C,EFFECTS_TONE);
    enable_channel(CH_C,1,0);

}

/*******************************************************************************
    PURPOSE: Plays a happy chiptune sound based on a player goal async event. Unimplemented.
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void play_goal(){

}