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
#include "display.h"
#include "input.h"
#include "premade.h"
/*
 * 
 */



char temp = 0;
int data = 0;

int main(int argc, char** argv) {
    intialize();
    intialize_player();
    play_sound(0,0);
    while(1){
        int position = 15;
        int maze[60] = {[0 ... 59] = -1 };
        int solution[15];
        int c;
        
        premade(maze, solution);
        
        while(position!=0){
            display_maze(maze, position);
            c=input(maze, position);
            if(c == 5){
            	display_solution(maze, position, solution);
            	c=-1;
            }
            if(c!= -1){
                position=maze[((position-1)*4)+c-1];
            }
        }
        PORTC.OUTSET = PORTE.IN << 4;
        PORTC.OUTCLR = ~(PORTE.IN<<4);
    
    }
    //
    //PORTC.OUTSET = PORTE.IN << 4;
    //PORTC.OUTCLR = ~(PORTE.IN<<4);
    //
    return (EXIT_SUCCESS);
}

