/*
Syed Mehdi
CS 211
Spring 2022
Windows 11 using Ubuntu
*/


#include <stdio.h>
#include <stdlib.h>


int main(){
	int input;
	int returnVal;
	int spaces;
	printf("Enter number of stairs: ");
	//calls for input and stores return value
	returnVal = scanf("%i", &input);
	//validates input
	if (input < 0 || returnVal == 0){
		printf("INVALID INPUT");
		exit(0);//terminate
	}
	else{
		//up stairs
		printf("up:\n\n");
		if (input != 0){//if there should be any stairs
			spaces =  input-1;//spaces in the first row 
			while(spaces > -1){//while there are spaces left
				for(int i = 0; i < spaces; i++){
					printf(" ");
				}
				for (int j = 0; j < (input-spaces);j++){
					printf("X");
				}
				printf("\n");
				spaces--;//one less space in the next row
			}
		}
		//down stairs
		printf("\ndown:\n\n");
		if (input != 0){
			spaces = input-1;
			while(spaces > -1){
				for (int k = 0; k < (input-spaces);k++){
					printf("X");
				}
				printf("\n");
				spaces--;
			}
		}
		//up-down stairs
		printf("\nup-down:\n\n");
		if (input != 0){
			spaces = input - 1;
			int row = 1; 
			while(row <= input){
				for(int l = 0; l < spaces; l++){
					printf(" ");
				}
				spaces--;
				for (int m = 0; m < (row*2-1);m++){
					printf("X");
				}
				printf("\n");
				row++;
				


			}

		}		

	}




	return 0;
}
