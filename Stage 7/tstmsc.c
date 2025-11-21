#include "music.h"
#include "psg.h"
void main(){
    volatile int i;
    int time = 0;
    start_music();
    for(i = 0; i<6;i++){
        for(time = 0;time<7;time++){
            update_music(time);
        }

    }
    stop_sound(); /*May have to be careful with this obj*/

}