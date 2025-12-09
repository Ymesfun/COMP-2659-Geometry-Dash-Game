#include "music.h"
#include "psg.h"
#include "constant.h"

static int state;
static UINT32 ticks;
static const note melody[] ={
    {f_period,7},
    {g_period,7},
    {f_period,7},
    {a_period,7}
};
static const int melody_len = sizeof(melody)/sizeof(melody[0]);

/*******************************************************************************
    PURPOSE: Starts playing the music sheet from the "melody" array. If array is empty, error
             handling aborts playing. Note struct in music.h. Functions like a state machine,
             resetting when n>melody_len
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void start_music(){
    state = 0;
    ticks = 0;
    if (melody_len>0){
        const note *note = &melody[0];
        if(note->tuning == 0){
            set_volume(CH_A,0);
        }else{
            set_tone(CH_A,note->tuning);
            set_volume(CH_A,12);
            enable_channel(CH_A,1,0);
        }
        ticks = note->length;
    }
}

/*******************************************************************************
    PURPOSE: Continues playing the music sheet from the "melody" array. If array is empty, 
             or time has not elapsed, error handling aborts playing. Note struct exists in 
             music.h, functions like a state diagram.
    INPUT:   - UINT32 time_elapsed - time passed based on system clock
    OUTPUT:  - N/A
*******************************************************************************/
void update_music(UINT32 time_elapsed){
    note note;
    if(time_elapsed == 0 || melody_len == 0){
        return;
    }
    while(time_elapsed>0){
        if(ticks>time_elapsed){
            ticks-= time_elapsed;
            break;
        }else{
            time_elapsed-= ticks;
            state = (state+1)%melody_len;
            note = melody[state];
            if(note.tuning>0){
                set_volume(CH_A,off);
                enable_channel(CH_A,off,off);
            }else{
                set_tone(CH_A,note.tuning);
                set_volume(CH_A,10);
                enable_channel(CH_A,on,off);
            }
            ticks = note.length;
        }

    }
}
