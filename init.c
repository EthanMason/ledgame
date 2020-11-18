/* 
 * File:   init.c
 * Author: ethan
 *
 * Created on September 17, 2020, 4:32 PM
 */
#include <avr/io.h>
#include "sound_player.h"

void intialize() {
    //configure chip select port a7
    PORTA.DIRSET = 1<<7;
    PORTA.OUTSET = 1<<7;
    CPU_SREG &= ~0x80;
    //opamp intialization
    //setting timebase
    //1u/(1/4Mhz) - 1 = 
    OPAMP.TIMEBASE = 3;
    //set opamp to unity gain and input to unity gain to be the DAC
    OPAMP.OP0INMUX = OPAMP_MUXNEG_OUT_gc | OPAMP_MUXPOS_DAC_gc ;
    //set opamp in always on and sets output driver to normal
    OPAMP.OP0CTRLA = OPAMP_OUTMODE_NORMAL_gc | OPAMP_ALWAYSON_bm;
    //enables OPAMP
    OPAMP.CTRLA = 0x1;
    
    
    
    
    //while(!(OPAMP.OP0STATUS & 1));
    //do we need settle timer? who knows documentation
    //just says depends on multitude of factors. can be added
    //later if device doesn't have proper functionality
    //see page 533 of the documentation for more info
    //pd2
    
    //dac0 intialization
    //sets up VREF to VDD and turns on AlwaysOn
    
    DAC0.CTRLA = DAC_OUTEN_bm | DAC_ENABLE_bm;
    //sets intial value
    DAC0.DATAH = 1;
    //enables dac
    DAC0.CTRLA |= 0x81; 
   
    
    
    //clock init
    //1/4Mhz*top=(1/8000)
    //top = 46
    TCA0.SINGLE.PER = 500;
    //enables overflow interrupt
    TCA0.SINGLE.INTCTRL |= 0x1;
    //sets clock divider to 64 enables clock
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_RUNSTDBY_bm | TCA_SINGLE_ENABLE_bm;
    
    //configure output pins for spi
    //PA4 MOSI
    //PA5 MISO
    //PA6 SCK
    //SPI overrides dirset for input pins but not output pins.
    PORTA.DIRSET = 1<<4 | 1<<6;
    //set to master mode and set prescale to 4 so 1Mhz baud rate on the spi
    SPI0.CTRLA |= 1<<5 | 0<<1;
    //set into buffer mode and disable slave select
    SPI0.CTRLB |= 1<<2 | 1<<7;
    
    SPI0.INTCTRL |= 1<<7 | 1<<5 | 1;
    
    SPI0.CTRLA |= 1;
    
    
    

       
    
}

