/*Author: Syed Shaban and Syed Mehdi
UIC, CS 211 Program 3: Spring 2022
DescriptionL Balloon pop game made with ASCII art*/ 
#define MAX_ROWS 40
#define MAX_COLS 40

#define None '.'    // "air"
#define Red  '^'
#define Blue '='
#define Green 'o'
#define Yellow '+'

// file:  bpgame.c

#include <stdlib.h>
#include <stdio.h>
#include "bpgame.h"
#include <time.h>


/** TYPEDEFS / STRUCTs HERE ***/
struct bpgame {
	char **board;
	int **visitation;
	int score;
	int rowNum;
	int colNum;
	int moveNumber;
	int *scoreStack;
	char ***boardStack;
   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....


};
typedef struct bpgame BPGame;




BPGame * bp_create(int nrows, int ncols){
	int i, j;
	BPGame *pGame;
	srand(time(NULL));
	pGame = malloc((sizeof(char**)*2) + ((sizeof(int) * 4)) + sizeof(char***) + sizeof(int *));
	pGame->score = 0;
	if(nrows > MAX_ROWS || nrows < 0){
		fprintf(stderr, "Error, please choose row within limits.");
		return NULL;
	}
	if(ncols > MAX_COLS || ncols < 0){
		fprintf(stderr, "Error, please choose row within limits.");
                return NULL;
	}
	pGame->boardStack = (char***)malloc(sizeof(char**) * 999);
	for(i = 0; i < 999; i++){
		pGame->boardStack[i] = (char**)malloc(sizeof(char*) * nrows + 1);
		for(j = 0; j < nrows + 1; j++){
			pGame->boardStack[i][j] = (char *)malloc(sizeof(char) * ncols + 1);
		}
	}
	pGame->scoreStack = (int*)malloc(sizeof(int)*999);
	pGame->moveNumber = 0;
	pGame->rowNum = nrows;
	pGame->colNum = ncols;
	pGame->board = (char**)malloc((nrows + 1) * sizeof(char*));
	for (int allocateNum = 0; allocateNum < nrows+1; allocateNum++){
		pGame->board[allocateNum] = (char*)malloc((ncols+1) * sizeof(char));
	}
	pGame->visitation = (int **)malloc((nrows+1) * sizeof(int*));
        for (int allocateNum1 = 0; allocateNum1 < nrows+1; allocateNum1++){
                pGame->visitation[allocateNum1] = (int*)malloc((ncols+1) * sizeof(int));
        }
	int randomVal;
	for (i = 0; i < nrows; i++){
		for (j = 0; j < ncols; j++){
			randomVal = (rand() % 4);
			switch(randomVal){
				case 0:
					pGame->board[i][j] = Red;
					break;
				case 1:
					pGame->board[i][j] = Blue;
					break;
				case 2:
                                        pGame->board[i][j] = Green;
					break;
				case 3:
                                        pGame->board[i][j] = Yellow;
					break;
			}

		}
	}
	for (i = 0; i < nrows; i++){
		for (j = 0; j < ncols; j++){
			pGame->visitation[i][j] = 0;
		}
	}
	pGame->scoreStack[pGame->moveNumber] = 0;
	for(i = 0; i < nrows; i++){
		for(j = 0; j < ncols; j++){
			pGame->boardStack[pGame->moveNumber][i][j] = pGame->board[i][j];
		}
	}
	return pGame;
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows,int ncols){
	int i, j;
	if(nrows > MAX_ROWS || nrows < 0){
                fprintf(stderr, "Error, please choose row within limits.");
                return NULL;
        }
        if(ncols > MAX_COLS || ncols < 0){
                fprintf(stderr, "Error, please choose row within limits.");
                return NULL;
        }
	
	for(i = 0; i < nrows; i++){
		for(j = 0; j < ncols; j++){
			if(mtx[i][j] != None && mtx[i][j] != Red && mtx[i][j] != Blue && mtx[i][j] != Green && mtx[i][j] !=  Yellow){
				fprintf(stderr, "Error, matrix must have valid characters inside.");
				return NULL;
			}
		}
	}
	BPGame *pGame = bp_create(nrows, ncols);

	for (i = 0; i < nrows; i++){
		for (j = 0; j < ncols; j++){
			pGame->board[i][j] = mtx[i][j];
		}
	}
	for(i = 0; i < nrows; i++){
                for(j = 0; j < ncols; j++){
                        pGame->boardStack[0][i][j] = pGame->board[i][j];
                }
        }
	return pGame;
}



void bp_destroy(BPGame *b){
	for(int i = 0; i < b->rowNum+1; i++){
		free(b->board[i]);
	}
	free(b->board);
	for(int i = 0; i < b->rowNum+1; i++){
		free(b->visitation[i]);
	}
	free(b->visitation);
	for(int i = 0; i < 999; i++){
		for(int j = 0; j < b->rowNum+1; j++){
			free(b->boardStack[i][j]);
		}
		free(b->boardStack[i]);
	}
	free(b->boardStack);
	free(b->scoreStack);
	free(b);
	return;
}
void bp_display(BPGame * b){
	int nrows = b->rowNum;
	int ncols = b->colNum;
	int curCol, curRow;
	int numDashes = (ncols*2)+1;
	printf("Score: %i\n", b->score);
	printf("   +");
	for(int i = 0; i < numDashes; i++){
		printf("-");
	}
	printf("+\n");
	for(curRow = 0; curRow < nrows; curRow++){
		printf("%2i |", curRow);
		for(curCol = 0; curCol < ncols; curCol++){
			printf(" %c", b->board[curRow][curCol]);
		}
		printf(" |\n");
	}
	//dashes
	printf("   +");
        for(int x = 0; x < numDashes; x++){
                printf("-");
        }
        printf("+\n     ");
	//first digit of the columns
	for(int y = 0; y < ncols; y++){
		printf("%i ", y/10);
	}
	printf("\n     ");
	//second digit of the columns
	for(int z = 0; z < ncols; z++){
		printf("%i ", z%10);
	}
	printf("\n\n");
	return;
}
void bp_display_STD(BPGame *b) {
    for (int i = 0; i < b->rowNum; i++) {
        for (int j = 0; j < b->colNum; j++) {
            printf("%c", (b->board)[i][j]);
        }
        printf("\n");
    }
}
int _isLonely(BPGame *b, int r, int c, char balloonClr){
	if(balloonClr != None){
	if(r < MAX_ROWS-1 && b->board[r+1][c] == balloonClr){
		if(b->visitation[r+1][c] != 1){	
			return 0;
		}
	}
	if(r > 0 && b->board[r-1][c] == balloonClr){
		if(b->visitation[r-1][c] != 1){
			return 0;
		}
	}
	if(c < MAX_COLS-1 && b->board[r][c+1] == balloonClr){
		if(b->visitation[r][c+1] != 1){
                        return 0;
                }
	}
	if(c > 0 && b->board[r][c-1] == balloonClr){
		if(b->visitation[r][c-1] != 1){
                        return 0;
                }
	}
	}
	return 1;
}

void _bp_pop(BPGame *b, int r, int c){
	char balloonClr;
        balloonClr = b->board[r][c];
	int popCount = 0;
	int origPopped = 0;
	int finalPopped = 0;
	b->visitation[r][c] = 1;
	if(_isLonely(b, r, c, balloonClr)){
		return;
        }
        else{
                if(r > 0 && b->board[r-1][c] == balloonClr){
			if(b->visitation[r-1][c] != 1){
				_bp_pop(b, r-1, c);
			}
                }
                if(c < MAX_COLS-1 && b->board[r][c+1] == balloonClr){
                        if(b->visitation[r][c+1] != 1){
                                _bp_pop(b, r, c+1);
			}
		}
                if(r < MAX_ROWS-1 && b->board[r+1][c] == balloonClr){
                        if(b->visitation[r+1][c] != 1){
                                _bp_pop(b, r+1, c);
			}
		}
                if(c > 0 && b->board[r][c-1] == balloonClr){
                        if(b->visitation[r][c-1] != 1){
                                _bp_pop(b, r, c-1);
			}
		}
        }
}
int bp_pop(BPGame *b, int r, int c){
	int i, j;
	int finalPopped = 0;

	_bp_pop(b, r, c);
	for(i = 0; i < b->rowNum; i++){
                for(j = 0; j < b->colNum; j++){
                        if(b->visitation[i][j] == 1){
				finalPopped++;
			}
                }
        }
	if(finalPopped > 1){
		for(i = 0; i < b->rowNum; i++){
                	for(j = 0; j < b->colNum; j++){
                        	if(b->visitation[i][j] == 1){
                                	b->board[i][j] = None;
                        	}
                	}
        	}
	}
	else{
		finalPopped = 0;
	}
	for(i = 0; i < b->rowNum; i++){
		for(j = 0; j < b->colNum; j++){
			b->visitation[i][j] = 0;
		}
	}
	b->score+= finalPopped*(finalPopped -1);
	if(finalPopped != 0){
		b->moveNumber++;
		b->scoreStack[b->moveNumber] = b->score;
        	for(i = 0; i < b->rowNum; i++){
                	for(j = 0; j < b->colNum; j++){
                        	b->boardStack[b->moveNumber][i][j] = b->board[i][j];
                	}
        	}	
	}
	return finalPopped;

}
int bp_is_compact(BPGame * b){
	int j, i;
	for(j = 0; j < b->colNum; j++){
		for(i = 0; i < b->rowNum; i++){
			if(b->board[i][j] == None){
				while(i+1 != b->rowNum){
					if(b->board[i+1][j] != None){
						return 0;
					}
					i++;	
				}
			}
		}
	}
	return 1;
}

int bp_score(BPGame *b){
	int score = b->score;
	return score;
}

int bp_get_balloon(BPGame *b, int r, int c){
	if (r < 0 || r > 40 || c < 0 || c > 40){
		return -1;
	}
	if(b->board[r][c] == Red)
		return Red;
	else if(b->board[r][c] == Blue)
		return Blue;
	else if(b->board[r][c] == Green)
		return Green;
	else if (b->board[r][c] == Yellow)
		return Yellow;
	else{
		return -1;
	}
	return -1;
}

int bp_can_pop(BPGame *b){
	char balloonClr;
	for (int i = 0; i < b->rowNum; i++){
		for(int j = 0; j < b->colNum; j++){
			balloonClr = b->board[i][j];
			if(!(_isLonely(b,i,j, balloonClr))){
				return 1;
			}
		}
	}
	return 0;
}
void swapChars(char *from, char *to){
	char temp = *from;
	*from = *to;
	*to = temp;
}
void bp_float_one_step(BPGame *b){
	int i, j;
	int isNum = 0;
	int bottomRow = b->rowNum - 1;
	
	for(j = 0; j < b->colNum; j++){
		bottomRow = b->rowNum - 1;
		while(bottomRow > 0 && b->board[bottomRow][j] == None){
			bottomRow--;
		}

		for(i = bottomRow; i >= 0; i--){
			if(b->board[i][j] == None){
				int currRow = i;
				for(int k = currRow; k < bottomRow; k++){
					swapChars(&(b->board[k][j]), &(b->board[k+1][j]));//swap air with one below
				}
				isNum = 1;
				break;
			}
		}
		

	}
	if(isNum == 1){
	b->scoreStack[b->moveNumber] = b->score;
        for(i = 0; i < b->rowNum; i++){
                for(j = 0; j < b->colNum; j++){
                        b->boardStack[b->moveNumber][i][j] = b->board[i][j];
                }
        }
	}
	 
}

int bp_undo(BPGame * b){
 	if(b->moveNumber <= 0){
		return 0;
	}

	for(int i = 0; i < b->rowNum; i++){
		for(int j = 0; j < b->colNum; j++){
			b->board[i][j] = b->boardStack[b->moveNumber-1][i][j];
		}
	}
	b->score = b->scoreStack[b->moveNumber-1];
	b->moveNumber--;
	return 1;
}

//main function for testing
/*
int main(int argc, char *argv[]){
	int rows, cols;
	int rowInput, colInput;
	BPGame *pGame;
	//if (argc > 1){
	//	if((sscanf(argv[1], "%i", &rows) == 1) && (sscanf(argv[2], "%i", &cols) == 1)){
	//		if(((rows <= MAX_ROWS) && (cols <= MAX_COLS)))
	//			pGame = bp_create(argv[1], argv[2]);
	//	}
	//}
	//else{
	pGame = bp_create(12, 12);
	//}
	bp_display_STD(pGame);
	//scanf("Enter a row and column: %d %d", &rowInput, &colInput);
	bp_pop(pGame, 1, 1);
	while(!(bp_is_compact(pGame))){
		bp_display_STD(pGame);
		bp_float_one_step(pGame);
	}
	bp_float_one_step(pGame);
	bp_display_STD(pGame);
	bp_destroy(pGame);
	return 1;
}
*/
/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

