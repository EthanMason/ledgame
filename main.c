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
#include "sound_player.h"
/*
 * 
 */



char temp = 0;
int data = 0;

int main(int argc, char** argv) {
    intialize();
    intialize_player();
    play_sound(0,0);
    while(1);
    
    
    return (EXIT_SUCCESS);
}

