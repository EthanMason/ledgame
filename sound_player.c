#include "init.h"
#include "sound_player.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
//NEEDS TO BE EVEN 
#define BUFFER_SIZE 5000

//end of current sound getting played 
static long long curr_loc = 0;
static long long end_loc = 0;
static enum sounds curr_sound;
static _Bool done = 1;
//value to see if sound will be repeated
_Bool repeated = 0;
//data buffer to hold samples before being played
static char data_buffer[BUFFER_SIZE];
static int position_buff = 0;
static int position_dac = 0;
static long long currmemloc = 0;

_Bool done_playing(){
    return done;
}

void intialize_player(){
    for(int i = 0; i < BUFFER_SIZE; i++){
        data_buffer[i] = 128;        
    }
}

void play_sound(enum sounds play){
    long long address_input = 0;
    switch (play)
    {
        case start_up:
            address_input = 0;
            end_loc = 6704;
            repeated = 0;
            break;
        case generating:
            address_input = 6704;
            end_loc = 17575;
            repeated = 0;
            break;
        case music:
            address_input = 50250;
            end_loc = 532428;    
            repeated = 1;
            break;
        case button_1:
            address_input = 17575;
            end_loc = 25305;   
            repeated = 0;
            break;
        case button_2:
            address_input = 25305;
            end_loc = 33098;     
            repeated = 0;
            break;
        case button_3:
            address_input = 33098;
            end_loc = 42036;  
            repeated = 0;
            break;
        case button_4:
            address_input = 42036;
            end_loc = 50250;
            repeated = 0;
            break;
        default:
            
            break;
    }
    
    
    
    
        done = 0;
        curr_sound = play;
        curr_loc = address_input;
        currmemloc = address_input;
        CPU_SREG &= ~0x80;
        PORTA.OUTSET = 1<<7;
        while(!(SPI0.INTFLAGS & (1<<5)));
        PORTA.OUTCLR = 1<<7;
        SPI0.DATA = 0x03;
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>>16);
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>>8);
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) currmemloc;
        position_buff = 0;
        position_dac = 0;
        SPI0.INTCTRL |=  1;
        TCA0.SINGLE.INTFLAGS |= 1;
        CPU_SREG |= 0x80;
}


ISR(TCA0_OVF_vect){
   // temp = temp + 30;
    //outputs current data buffer to dac
    DAC0.DATAH = data_buffer[position_dac++];
    curr_loc++;
    //checks to see if end of buffer if it is restart communciation
    if(curr_loc >= end_loc && !repeated){
        TCA0.SINGLE.INTFLAGS |= 1;
        done = 1;
        return;
    }
    else if (curr_loc >= end_loc && repeated){
        play_sound(curr_sound);
        TCA0.SINGLE.INTFLAGS |= 1;
        return;
    }
    if(position_dac >= BUFFER_SIZE){
        position_dac = 0;
        CPU_SREG &= ~0x80;
        SPI0.CTRLA |= 0x1;
        //documentation doesnt say what happens if you disable the spi bus
        //so i just do this check just in case. 
        while(!(SPI0.INTFLAGS & (1<<5)));
        PORTA.OUTCLR = 1<<7;
        //data read command byte
        SPI0.DATA = 0x03;       
        //send data bytes 8 at a time for a total of 24
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>>16);
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>>8);
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) currmemloc;
       
        CPU_SREG |= 0x80;
    }
    TCA0.SINGLE.INTFLAGS |= 1;
    return;
}

ISR(SPI0_INT_vect){
    
    //check data empty flag
    if (SPI0.INTFLAGS & (1<<5)){
        //outputs dnc values for output
        SPI0.DATA = 0;     
    }
    //recieve complete flag
    if(SPI0.INTFLAGS & (1 << 7)){
        //receives 2 samples and increment by 2 
        //doubled buffered so thats why +2
        currmemloc += 2;
        data_buffer[++position_buff] = SPI0.DATA;
        data_buffer[++position_buff] = SPI0.DATA;
        //checks to see if end of buffer it is disable spi communication
        //gets restarted once player reaches end of buffer
        if(position_buff >= BUFFER_SIZE){
            SPI0.CTRLA &= (~0x1);
            position_buff = 0;
            PORTA.OUTSET = 1<<7;
        }
    }
}





