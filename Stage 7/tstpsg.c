#include "psg.h"
#include <stdio.h>
#include <osbind.h>

void main(){
    printf("First, illegal inputs:");
    set_tone(3,0);
    set_tone(2,2500);
    
    volatile int i;
    set_tone(CH_A, 300);
    set_volume(CH_A,10);
    enable_channel(CH_A,on,off);
    for(i = 0; i<50000 ;i++){

    }
    set_noise(6);
    set_envelope(0x09, 3500);
    set_volume(2,0x10);
    enable_channel(CH_C,on,on);
    for(i = 0; i<50000; i++){

    }
    stop_sound();
}