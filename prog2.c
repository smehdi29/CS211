
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "prog2.h"



/**
* 
*  Function "stubs" for Assignment 2 exercises.
*
*  See prog2.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char** alloc_square_mtx(int n) {
    int i;

    char** arr = (char**)malloc(n*sizeof(char*));
    for (i =0; i < n; i++) {
        arr[i] = malloc(n*sizeof(char));
    }


    return arr; // placeholder

}

void free_square_mtx(char **m, int n) {
    int i;
    for(i = 0; i < n; i++){
        free(m[i]);
    }
    free(m);
}

void pop_mtx_alpha(char **m, int n){
    srand(time(NULL));
    int i,j;
    for(i = 0; i < n; i++){
        for (j = 0; j<n;j++){
            m[i][j] = 97+rand()%26;
        }
    }
}


	


void display_mtx(char **m, int n){
	int i,j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("%c ", m[i][j]);
		}
		printf("\n");

	}

}

void swap_rows(char **m, int n, int r1, int r2){
	if ((r1 < n)&&(r2 < n)) {
        char *temp = m[r1];
        m[r1] = m[r2];
        m[r2] = temp;
    }
}

void swap_cols(char **m, int n, int c1, int c2){
	int i,j;
	char temp;
    if ((c1 < n)&&(c2 < n)){
        for (i = 0; i < n; i++) {
            temp = m[i][c1];
            m[i][c1] = m[i][c2];
            m[i][c2] = temp;
        }
    }
}



//function I made to copy a matrix to use in rotate_right()
void copyMtx(char **to, char**from, int n){
    int i,j;
    for (i = 0; i<n; i++){
        for (j = 0; j< n; j++){
            to[i][j] = from[i][j];
        }
    }
    free_square_mtx(from, n);
}


void rotate_right(char **m, int n){
	int i,j;
	char** new = alloc_square_mtx(n);
	for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            new[j][i] = m[(n - 1) - i][j];
        }

    }
    copyMtx(m,new,n);


}


void floating_boulders(char **m, int n, int nb){

    //incase the array is already filled
    /*free_square_mtx(m,n);
    m = alloc_square_mtx(n);
     */
    //checks amount of boulders
    if(nb > n*n)
        nb = n*n;
    else if(nb < 0)
        nb = 0;
    int i,j,k;
    int randrow,randcol;

    for (i = 0; i<nb; i++){
        randrow = rand()%n;
        randcol = rand()%n;
        while(m[randrow][randcol] == '#'){
            randrow = rand()%n;
            randcol = rand()%n;

        }
        m[randrow][randcol] = '#';
    }
    for(j = 0; j<n;j++){
        for(k = 0; k<n; k++){
            if(m[j][k] != '#')
                m[j][k] = '.';
        }
    }
}


void mountains(char **m, int n){
    int indicator;
    int i,j;
    for(int i = n-1; i >= 0; i--){
        for(int j = 0; j < n; j++){
            indicator = rand()%2;
            if (i == n-1) {
                if (indicator == 0) {
                    m[i][j] = '.';
                } else {
                    m[i][j] = '#';
                }
            }
            else{
                if(m[i+1][j] == '.') {
                    m[i][j] = '.';
                }else{
                    if (indicator == 0) {
                        m[i][j] = '.';
                    } else {
                        m[i][j] = '#';
                    }

                }

            }

        }
    }

}



void sink(char **m, int n){
    int i,j;

    for(i = n-1; i > 0; i--) {
        swap_rows(m,n,i,i-1);
    }
    for(j = 0; j < n; j++){
        m[0][j] = '.';
    }
}


void gravity(char **m, int n){
	int col, row;
	col = 0;
	row = n-1;
	int i;
	char temp;
	int swapcounter = 0;
	for(col = 0; col < n; col++){
		for(row = n-1; row>0; row--){
			if(m[row][col] == '.'){
				swapcounter = 0;
				while((m[row][col] == '.')&&(swapcounter<n*n)){
					for(i = row; i > 0; i--){//downshifts column
						temp = m[i][col];
						m[i][col] = m[i-1][col];
						m[i-1][col] = temp;
					}
					swapcounter++;//this is eventually to put the loop to a stop(there cannot be more swaps than matrix column/row size)		
				}
			}		
		}
	}
}//end of gravity
		





/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/




void str_trim(char *s) {
	int i,j;
	i = 0;
	j = 0;
	int k,m;
	int index = 0;
	
	while(s[j] != '\0'){
		j++;
	}//gets length

	while(isspace(s[i])){
		i++;
	}//takes us to the first non space character
	while(isspace(s[j])){
		j--;
	}//takes us to the last non space character	char *new = malloc(sizeof(char)*(j-i));
	char* new = malloc(sizeof(char)*(j-i+1));
	for(k = i; k < j-i; k++){
		new[index] = s[k];
		index++;
	}//the new string is the old string trimmed
	
	new[index] = '\0';//sentinel  
       	
	for(m = 0; m< j-i; m++){
		s[m]=new[m];
	
	}//the new string is copied onto the old one	
	//printf("%s", new);
	
	s[j-i] = '\0';//end of string

	
	free(new);

}
		
int str_search(char *s, char *pattern) {
	int i,j,k;
	int pattern_size = strlen(pattern);
	char substr[pattern_size];
	// 0 = true 1 = false 
	int match = 0;
	for( i = 0; i < (strlen(s) - pattern_size); i++){
		match = 0;
		for (j = 0; j < pattern_size; j++){
			substr[j] = s[j+i];
		}
		for(k = 0; k < pattern_size; k++){
			if(substr[k] == pattern[k]){
				match = 0;//true
			}
			else{
				match = 1;//false
				break;
			}
		
		}
		if (match == 0)//if the pattern is a match
			return i;//return index

	}
	return -1;//returns when there is no match
}





#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main(){
	//test driver 
    int i,j;
    int n = 10;
    char** twod = alloc_square_mtx(n);
    pop_mtx_alpha(twod, n);
    printf("Original Matrix\n");
    display_mtx(twod, n);
    printf("Swapped Rows\n");
    swap_rows(twod, n, 0,2);
    printf("Rotated Right\n");
    rotate_right(twod,n);
    display_mtx(twod,n);
    printf("Rotated Right Again\n");
    rotate_right(twod,n);
    display_mtx(twod,n);
    printf("Boulders\n");
    floating_boulders(twod,n,50);
    display_mtx(twod,n);
    printf("Gravity\n");
    gravity(twod,n);
    display_mtx(twod,n);
    printf("Columns Swap\n");
    swap_cols(twod, n, 1, 2);
    display_mtx(twod,n);
    printf("Mountains\n");
    mountains(twod,n);
    display_mtx(twod,n);
    printf("Sink\n");
    sink(twod, n);
    display_mtx(twod,n);

//string function tests
    char string[] = "     I D K     ";
    printf("Original string:%s\n", string);
    str_trim(string);
    printf("Trimmed String:%s\n",string);
    char pattern[] = "di";
    char pattern1[] = "ab";
    char pattern2[] = "cba";
    char tester[] = "cidiaabcadi";
    printf("Search string: %s\n", tester);
    printf("Pattern 1: %s\n" , pattern);
    printf("Found at: %i\n", str_search(tester,pattern));
    printf("Pattern 2: %s\n", pattern1);
    printf("Found at: %i\n", str_search(tester, pattern1));
    printf("Pattern 3: %s\n", pattern2);
    printf("Found at: %i\n", str_search(tester, pattern2));

    free_square_mtx(twod,n);//frees matrix




  // test driver


}


#endif        // DO NOT REMOVE THIS LINE!!!





 
