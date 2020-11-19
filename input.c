#include <stdio.h>
#include "input.h"
#include <avr/io.h>
#include <avr/cpufunc.h> 

int input(int a[60], int pos){
	int c;
    _Bool button_pressed = 0; 
    do{
        for(int i = 0; i < 4; i++){
            if((PORTE.IN >> i)&1){
                c = i + 1;
                button_pressed = 1;
                for(volatile unsigned int q = 0; q < 0xFF; q++){
                            _NOP ();
                }
                break;            
            }
        }
        if((PORTB.IN >> 5)&1){
            c = 5;
            button_pressed = 1;
            for(volatile unsigned int q = 0; q < 0xFF; q++){
                            _NOP ();
            }
        }
    }while(!button_pressed);
            
	if(c==5){
		return(c);
	}
	if(a[((pos-1)*4)+c-1]== -1){
		return(-1);
	}
	return(c);


}
