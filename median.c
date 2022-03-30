/*Syed Mehdi
 * CS 211
 * Spring 2022
 * Windows 11 using Ubuntu
 * Program to determine median of 3 user input numbers
 * */
#include <stdio.h>
#include <stdlib.h>


//function to swap integers
void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;

}//end of swap()


//function to sort array (using bubble sort)
void sort(int array[], int size){	
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size-i; j++){
			if (array[j] > array[j+1]){
				swap(&array[j], &array[j+1]);
			}
		}

	}	
	
		
	 
}//end of sort()


int main(){
	//size of array
	const int SIZE = 3;
	//array to store inputs
	int inputs[SIZE];
	int i = 0;
	int returnVal;
	int userInput;

	while (i<SIZE){
		printf("Enter an integer: ");
		returnVal = scanf("%i", &userInput);
		//validates input
		if (returnVal == 0){
			printf("INVALID INPUT\n");
			exit(0);
		}
		//printf("\n");
		inputs[i] = userInput;
		i++;

			

	}
	//sorts array in order
	sort(inputs, SIZE);
	//ouputs median	
	printf("\nmedian: %i\n", inputs[1]);
	

	return 0;



}
