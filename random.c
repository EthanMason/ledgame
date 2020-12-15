#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
#include "random.h"
#include <avr/io.h>


int random_num(int max){
	//So each random call is different
	srand(TCA1.SINGLE.CNT);
	//usleep(100000);
	return (rand()%max);
}


int random_gen(int a[60], int b[15]){
	int r;
	int check=1;
	//Valid bit locations
	int frame[32]={0,5,8,9,14,16,18,21,22,24,25,26,31,32,35,37,39,40,41,43,46,47,48,50,51,53,54,55,56,57,58,59};
	int used[8]={-1,-1,-1,-1,-1,-1,-1,-1};
	int unused[6]={0};
	//Comparative array to the frame
	int used_frame[32]={[0 ... 31] = -1 };
	//Solution length is always 9
	b[14]=9;
	//Solution path creation
	for(int i=0; i<8;i++){
		do{
			check=0;
			r=random_num(16+i);
			//printf("%d Test number %d\n", r, i);
			for(int n=0; n<8; n++){
				//Checks to see if random number points to a  state which is already used
				if(used[n]==((frame[r]/4)+1)){
					check=1;
					//printf("Conflict %d %d \n", used[n], (frame[r/4]));
				}
			}
		}while(check);

		//printf("Location %d\n", frame[r]);
		
		//Sets used locations in both value and frame
		used[i]=((frame[r]/4)+1);
		used_frame[r]=frame[r];
		//If first time through set exit to maze otherwise set value of bit to state value
		if(i==0){
			a[frame[r]]=0;
		}else{
			a[frame[r]]=used[i-1];
		}

		//printf("Number %d\n", used[i]);

		//Sets solution distance from goal
		b[(frame[r]/4)]=i+1;
	}
	//Sets unused array to all states not covered by the 9 length solution
	r=0;
	for(int n=1; n<15; n++){
			check=0;
			//Cycles through each value 1 through 15 and checks to see if their state has been used
			for(int m=0; m<8; m++){
				if(used[m]==n){
					check=1;
				}
			}
			// If not then sets unused to that value and itterate
			if(check == 0){
				unused[r]=n;
				r++;
			}
	}

	//Make sure each unused node points to a node that is found in the solution
	for(int i=0; i<6; i++){
		check=0;
		//Checks to see if array location is valid
		for(int n=0; n<4; n++){
			for(int m=0; m<32; m++){
				//Checks to see if value is in the frame and we havent already added a value to it
				if((((unused[i]-1)*4)+n)==frame[m] && check==0){
					check=1;
					// Limits depth of non solution path randomness
					r=random_num(3)+5;
					//printf("Random Number: %d\n", r);
				
					//sets values and updates frames and used and new solution depths
					a[frame[m]]=used[r];
					used_frame[m]=frame[m];
					b[unused[i]-1]=r+2;
				}
			}
		}
	}
	//Fills in all unused spaces in the frame with a rotating set of lower depth values
	check=0;
	for(int i=0; i<32; i++){
		if(used_frame[i]==-1){
			if(check==6){
				check=0;
			}
			//Make sure non of the nodes point at themselves
			if((unused[check]-1)==(frame[i]/4)){
				check++;
			}
			if (check==6){
				check=0;
			}
			a[frame[i]]=unused[check];
			check++;
		}
	}
	//Sets one of the values of the starting point to 9 layers deep so that a starting solution can be found
	r=random_num(4)+28;
	a[frame[r]]=used[7];
	/******Output Testing**********
	printf("\n\nUsed Nodes\n");
	for(int i=0; i<8; i++){
		printf("%d  ", used[i] );
	}
	printf("\n\nUnused Nodes\n");
	for(int i=0; i<6; i++){
		printf("%d ",unused[i]);
	}
 	******************************
	printf("\n\nSolution set\n");
	for(int i=0; i<15; i++){
		printf("%d  ", b[i]);
	}
	***************************
	printf("\n\nUsed Frames\n");
	for(int i=0; i<32; i++){
		printf("%d ",used_frame[i]);
	}
	*******************************
	printf("\n\n Game array \n");
	for(int i=0; i<60; i++){
		printf("%d ", a[i]);
		if((i+1)%4==0) printf("\n");
	}
	*******************************/	
	return(0);
}
