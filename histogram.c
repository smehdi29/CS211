/*Syed Mehdi
 * CS 211
 * Spring 2022
 * Windows 11 using Ubuntu
 * Program creats an ASCII Histogram based on user input for 4 variables
 * */

#include <stdio.h>
#include <stdlib.h>

//function takes in input and determines if it is the max value
void input(int *var, int *maxVal){
	int returnVal;
	returnVal = scanf("%i", var);
	//validates input
	if( returnVal == 0 || *var < 0 ){
		printf("INVALID INPUT");
		exit(0);//terminates
	}
	if (*var > *maxVal){
		*maxVal = *var;
	}
	//printf("\n");

}//end of input()


int main(){

	//input
	int a;
	int b;
	int c;
	int d;
	int maxVal = 0;
	printf("A: ");
	input(&a, &maxVal);
	printf("B: ");
	input(&b, &maxVal);
	printf("C: ");
	input(&c, &maxVal);
	printf("D: ");
	input(&d, &maxVal);
	//end of inputs
	//
	//histogram
	//loop starts from the top and goes row by row
	for (int i = maxVal; i > 0; i--){
		printf(" ");
		if(a == i){
			printf("X ");
			a--;
		}
		else{
			printf("  ");
		}
		if(b == i){
			printf("X ");
			b--;
		}
		else{
			printf("  ");
		}
		if(c == i){
			printf("X ");
			c--;
		}
		else{
			printf("  ");
		}
		if(d == i){
			printf("X ");
			d--;
		}
		else{
			printf("  ");
		}
		printf("\n");

	}
	printf("---------\n A B C D\n");


	return 0;
}
