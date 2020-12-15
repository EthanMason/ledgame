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
#include <avr/cpufunc.h> 
/*
 * 
 */



char temp = 0;
int data = 0;

int main(int argc, char** argv) {
    intialize();
    intialize_player();
    while(1){
        int position = 15;
        int maze[60] = {[0 ... 59] = -1 };
        int solution[15];
        int c;
        
       
        _Bool button_pressed = 0; 
        do{
            for(int i = 0; i < 2; i++){
                    if((PORTE.IN >> i)&1){
                    int c = i + 1;
                    button_pressed = 1;
                    for(volatile unsigned int q = 0; q < 0xFF; q++){
                                _NOP ();
                    }
                    if(c = 1){
                        premade(maze, solution);
                    }
                    else{
                        random_gen(maze, solution);
                    }
                    break;            
                }
            }
        }while(!button_pressed);
        
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
    
    }
    //
    //PORTC.OUTSET = PORTE.IN << 4;
    //PORTC.OUTCLR = ~(PORTE.IN<<4);
    //
    return (EXIT_SUCCESS);
}

