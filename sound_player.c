#include "init.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
//NEEDS TO BE EVEN 
#define BUFFER_SIZE 5000


static int increment_command = 0;
static char data_buffer[BUFFER_SIZE];
static int position_buff = 0;
static int position_dac = 0;
static long long currmemloc = 0;


void intialize_player(){
    for(int i = 0; i < BUFFER_SIZE; i++){
        data_buffer[i] = 128;        
    }
}

void play_sound(long long address_input, long long size){
        currmemloc = address_input;
        CPU_SREG &= ~0x80;
        PORTA.OUTSET = 1<<7;
        while(!(SPI0.INTFLAGS & (1<<5)));
        PORTA.OUTCLR = 1<<7;
        SPI0.DATA = 0x03;
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>>16);
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>8);
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
    DAC0.DATAH = data_buffer[position_dac++];
    if(position_dac >= BUFFER_SIZE){
        position_dac = 0;
        CPU_SREG &= ~0x80;
        SPI0.CTRLA |= 0x1;
        //documentation doesnt say what happens if you disable the spi bus
        //so i just do this check just in case. 
        while(!(SPI0.INTFLAGS & (1<<5)));
        PORTA.OUTCLR = 1<<7;
        SPI0.DATA = 0x03;        
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>>16);
        while(!(SPI0.INTFLAGS & (1<<5)));
        SPI0.DATA = (unsigned char) (currmemloc>8);
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
        //no way to do this automatically??? wasted clock cycles sad!
        SPI0.DATA = 0;     
    }
    //recieve complete flag
    if(SPI0.INTFLAGS & (1 << 7)){
        currmemloc += 2;
        data_buffer[++position_buff] = SPI0.DATA;
        data_buffer[++position_buff] = SPI0.DATA;
        if(position_buff >= BUFFER_SIZE){
            SPI0.CTRLA &= (~0x1);
            position_buff = 0;
            PORTA.OUTSET = 1<<7;
        }
    }
}





