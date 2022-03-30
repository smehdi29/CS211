/*Syed Mehdi
 * CS 211
 * Spring 2022
 * Windows 11 using Ubuntu
 * Program to determine the amount of ones in any given number in binary form.
 * */

#include <stdio.h>
#include <stdlib.h>

int main(){
	

	int input;
	int returnVal;
	//to store binary digits
	int bdigits[20];
	int index = 0;
	//to count the amount of ones
	int counter = 0;
	printf("Enter a non-negative number: ");
	returnVal = scanf("%i", &input);
	//validates input
	if (returnVal == 0 || input < 0){
		printf("\nINVALID INPUT");
		exit(0);
	}
	else{
		int original = input;//original number
		while(input > 0){
			//counts how many ones are there in binary form
			bdigits[index] = input%2;
			if(bdigits[index] == 1){
				counter++;
			}
			input = input/2;
			index++;	
		}
		//final output
		printf("%i has %i ones in binary", original, counter);

	}


	return 0;
}
