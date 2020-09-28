/* 
 * File:   main.c
 * Author: ethan
 *
 * Created on September 17, 2020, 3:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*
 * 
 */
int temp = 0;


int main(int argc, char** argv) {
    intialize();
    

    while(1);
    
    
    return (EXIT_SUCCESS);
}

ISR(TCA0_OVF_vect)
{
    DAC0.DATAH += temp++;
    TCA0.SINGLE.INTFLAGS |= 1;
    return;
}
