/*******************************************************************************
 AUTHORS: Yacob Mesfun, Lorenzo Primiterra
 COURSE: COMP2659-002
 INSTRUCTOR: Steve Kalmar
 DATE: November 10, 2025

 FILE: psg.c
 SUMMARY: Contains the low level functions that write to the YM2149 music chip. Functions
 have in-built error checking to prevent crashing the system by writing into protected memory. 
*******************************************************************************/

#include "psg.h"
#include <osbind.h>

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg(int reg, UINT8 val){
    if(reg < 0 || reg > 15){
        return;
    } else if(val < 0 || val > 255){
        return; /*Both returns unnecessary, but they provide a better visual flow as to what the code is doing*/
    }else{

    long old_ssp = Super(0);
	*PSG_reg_select = reg;
    *PSG_reg_write = val;
    Super(old_ssp);
    return;
    }
}

/*******************************************************************************
    PURPOSE: Reads the value in the given register. This is done by selecting the register,
             and then reading the reg_select to get the value at that register.
    INPUT:   - int reg - our register that we want to get the value at.
    OUTPUT:  - 8 bit value at any given register
*******************************************************************************/
UINT8 read_psg(int reg){
    if(reg >= 0 && reg <16){
        long old_ssp = Super(0);
        *PSG_reg_select = reg;
        Super(old_ssp);
        return *PSG_reg_select;
    }
}

/*******************************************************************************
    PURPOSE: Sets the tone in the YM2149 sound chip, given a channel and a 12-bit tuning value.
             Error handling for illegal inputs exists, so any inputs outside of the given range
             will not modify the sound chip.
    INPUT:   - int channel - This checks for the range 0-2. Given those values, your
                             channel is multiplied by 2 and set for that. So, 
                             A = 0, B = 1, C = 2
             - int tuning - This takes in a 12 bit value and puts it into the YM2149 sound chip.
    OUTPUT:  - N/A
*******************************************************************************/
void set_tone(int channel,int tuning){
    UINT8 fine;
    UINT8 coarse;
    if(channel >= 0 && channel < 3 && tuning >= 0 && tuning <= 4095){
        fine = (UINT8)(tuning & 0xFF); /*Summary: We grab the first 8 bits by anding with FF.*/
        coarse = (UINT8)((tuning>>8)&0xF); /*Summary: Shift 8 bits to the right, get 4 remaining bits*/
        write_psg(channel<<1,fine); /*Instead of figuring out if things are fine/coarse aligned, use bit shifts.*/
        write_psg((channel<<1)+1, coarse);
    }
}

/*******************************************************************************
    PURPOSE: Sets the volume in the YM2149 sound chip, given a channel and a 5-bit volume value.
             Error handling for illegal inputs exists, so any inputs outside of the given range
    INPUT:   - int channel - This checks for the range 0-2. Given those values, your
                             channel value is really channel+8, and the corresponding register  
                             values are: A = 0, B = 1, C = 2
             - int volume - This takes in a 5 bit value and puts it into the YM2149 sound chip.
    OUTPUT:  - N/A
*******************************************************************************/
void set_volume(int channel, int volume){
    if(channel >= 0 && channel <= 2 && volume >= 0 && volume < 32){
        write_psg(channel+8,(UINT8)(volume & 0x1F));
    }
}


/*******************************************************************************
    PURPOSE: Enables or disables a given channel in the YM2149 sound chip, given a
             channel, whether the tone should be on or the noise should be on.
             Has error handling built in.
    INPUT:   - int channel - This checks for the range 0-2. Given those values, your
                             corresponding values are: A = 0, B = 1, C = 2
             - int tone_on - Enables if tone bit = 1, disables if tone bit = 0
             - int noise_on - enables if noise bit = 1, disables if noise bit = 0
    OUTPUT:  - N/A
*******************************************************************************/
void enable_channel(int channel, int tone_on, int noise_on){
    if(channel >= 0 && channel <3 && tone_on<2 && tone_on >=0 && noise_on <2 && noise_on >=0){
        UINT8 low_order;
        UINT8 high_order;
        UINT8 mix = read_psg(MIXER);
        low_order = 1 << channel; /*Used to address the low and high order bits of channel.*/
        high_order = 1<<(channel+3);
        if(tone_on){
            mix  &= ~low_order;
        }else{
            mix |= low_order;
        }
        if(noise_on){
            mix &= ~high_order;
        }else{
            mix |= high_order;
        }
        write_psg(MIXER,mix);
    }
}

/*******************************************************************************
    PURPOSE: Sets the noise for the YM2149 sound chip given a 5 bit frequency value.
    INPUT:   - UINT8 freq - Sets the noise freq value
    OUTPUT:  - N/A
*******************************************************************************/
void set_noise(int freq) {
    if(freq>= 0 && freq<32){
        write_psg(NOISE,(UINT8)freq);
    }
}

/*******************************************************************************
    PURPOSE: Sets the envelope in the YM2149 given a shape and a sustain value. Has
             built in error handling.
    INPUT:   - int shape - the shape of the envelope, 4 bit. bit representations are:
                           CONT-ATT-ALT-HOLD
             - unsigned int sustain - Rough and fine frequency of our envelope.
                                      Low order bits are fine frequency, high order
                                      bits are rough frequency.
    OUTPUT:  - N/A
*******************************************************************************/
void set_envelope(int shape, unsigned int sustain){
    if(shape < 16 && shape >= 0){
        write_psg(ENVELOPE_FINEFREQ, (UINT8) (sustain));
        write_psg(ENVELOPE_ROUGHFREQ, (UINT8) sustain>>8);
        write_psg(ENVELOPE_SHAPE, (UINT8) (shape & 0x0F));
    }

}

/*******************************************************************************
    PURPOSE: Stops all sound output from the YM2149 sound chip.
    INPUT:   - N/A
    OUTPUT:  - N/A
*******************************************************************************/
void stop_sound(){
    write_psg(A_VOL,0);
    write_psg(B_VOL,0);
    write_psg(C_VOL,0);
    write_psg(MIXER,0xFF);
}