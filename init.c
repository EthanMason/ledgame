/* 
 * File:   init.c
 * Author: ethan
 *
 * Created on September 17, 2020, 4:32 PM
 */
#include <avr/io.h>

void intialize() {
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
    
    //global interrupt enable
    CPU_SREG |= 0x80;  
    
    
    
    
}

