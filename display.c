#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include <avr/io.h>
#include <avr/cpufunc.h> 
#include "sound_player.h"

int display_maze(int a[60], int step){
	int display= (step-1)*4;
	//Replace with each led code
	if(a[display] == -1){
		PORTC.OUTCLR = 1<<4;
	} else {
		PORTC.OUTSET = 1<<4;
	}
	if(a[display + 1] == -1){
		PORTC.OUTCLR = 1<<5;
	} else {
		PORTC.OUTSET = 1<<5;
	}
	if(a[display + 2] == -1){
		PORTC.OUTCLR = 1<<6;
	} else {
		PORTC.OUTSET = 1<<6;
	}
	if(a[display + 3] == -1){
		PORTC.OUTCLR = 1<<7;
	} else {
		PORTC.OUTSET = 1<<7;
	}
	return(0);
}
int display_solution(int a[60], int step, int sol[15]){
	int solve=sol[step-1];
	int temp;
	for(int n=0;n<solve; n++){
		temp=(step-1)*4;
		for(int i = 0; i < 4; i++){
			//printf("\nValue:%d", a[temp+i]);
			if(a[temp+i] != -1){
				if(sol[a[temp+i]-1] == solve-1-n){
					PORTC.OUTCLR = 0xF0;
                    PORTC.OUTSET = 1<<(4+i);
                    switch(i){
                        case 0:
                            play_sound(button_1);
                        case 1:
                            play_sound(button_2);
                        case 2:
                            play_sound(button_3);
                        case 3:
                            play_sound(button_4);
                    }
                    while(!done_playing());
                    
					step=a[temp+i];
				}
				if(a[temp+i]==0){
                    PORTC.OUTCLR = 0xF0;
					PORTC.OUTSET = 1<<(4+i);
                    
                    switch(i){
                        case 0:
                            play_sound(button_1);
                        case 1:
                            play_sound(button_2);
                        case 2:
                            play_sound(button_3);
                        case 3:
                            play_sound(button_4);
                    }
                    while(!done_playing());
                    
                    
				}
			}
		}
		//printf("\nStep:%d",step);
	}
	return(0);
}
