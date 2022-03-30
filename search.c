#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NROWS 11
#define NCOLS 11
#define START_R (NROWS/2)
#define START_C (NCOLS/2)


#define NORTH 'n'
#define SOUTH 's'
#define EAST  'e'
#define WEST  'w'
#define QUIT  'q'
#define BLANK 'b'
#define ERROR 'r'

/*
 *Syed Mehdi
 *CS 211
 *Spring 2022
 *Windows 11 using Ubuntu
 *
 *
 */

/**
 * starter code for the 'search' program/game.
 *
 * The given code takes care of two of the tasks in the program:
 *
 *      - reading and interpreting a user command via the read_cmd
 *          function.  Read the banner comment and examine the example
 *          usage of the function in main for details.
 *
 *      - handling optional command line arguments which allow a 
 *          the user (tester) to specify explicitly the location of
 *          the pot-o-gold instead of that location being randomized
 *          as in the default mode.
 *
 */

/**
 * func:  read_cmd
 * desc:  (attempts to) read a single line from standard input, and 
 *          returns one of the following:
 *
 *          NORTH : if the first non-whitespace character is either
 *                  'n' or 'N'
 *          SOUTH : if the first non-whitespace character is either
 *                  's' or 'S'
 *          EAST  : if the first non-whitespace character is either
 *                  'e' or 'E'
 *          WEST  : if the first non-whitespace character is either
 *                  'w' or 'W'
 *          QUIT  : if the first non-whitespace character is either
 *                  'q' or 'Q' OR an input line cannot be read (this
 *                  happens if EOF is read terminating the input; from 
 *                  the terminal, this happens if the user types ctrl-D 
 *                  (in UNIX at least))
 *          BLANK : if the user entered a blank/empty line
 *          ERROR : if the user entered an invalid command
 *
 */

char read_cmd() {

    char buf[128];

    // this happens when fgets reads 'EOF'.  This happens
    //   when the user types CTRL-D
    if(fgets(buf, 128, stdin) == NULL)
        return 'q';

    int n = strlen(buf);

    int i=0;

    while(i<n && isspace(buf[i]))
        i++;

    if(i==n)
        return BLANK;  // entire line is whitespace (incl newline)
    char c = buf[i];

    switch(c) {
        case 'n':
        case 'N': return NORTH;
        case 's':
        case 'S': return SOUTH;
        case 'e':
        case 'E': return EAST;
        case 'w':
        case 'W': return WEST;
        case 'q':
        case 'Q': return QUIT;
        default: 
                  return ERROR;

    }
}

/**
 * func: inrange
 * desc: simple predicate function determining whether a 
 *          given coordinate (r,c) is within the boundaries
 *          of the "board" (if yes, returns true; if no,
 *          returns false).
 */
int inrange(int r, int c) {
    if(r < 0 || c < 0 || r >= NROWS || c >= NCOLS) 
        return 0;
    else
        return 1;
}

int main(int argc, char *argv[]) {
    int g_row, g_col;
    int randomize = 1;
    int moves = 0;
    int p_row = START_R;
    int p_col = START_C;

    /*for(int i=0; i<argc; i++) {
        printf(" argv[%i] : '%s'\n", i, argv[i]);
    }*/
    if(argc == 3){
        int r1 = sscanf(argv[1], "%i", &g_row);  // row coord of gold
        int r2 = sscanf(argv[2], "%i", &g_col);  // row coord of gold
        if(r1==0 || r2==0 || !inrange(g_row, g_col) ||
                (g_row == START_R && g_col == START_C))
            printf("bad cmd-line args: using random location for gold\n");
        else
            randomize = 0;
    }
    else if(argc != 1) 
            printf("bad cmd-line args: using random location for gold\n");

    if(randomize) {

        // your code or function call here to establish randomized location
        // for the pot-o-gold under requirements of handout
	srand(time(NULL));
	g_row = rand()%11;
	g_col = rand()%11;
	while ((g_row == START_R) && (g_col == START_C)){
	       g_row = rand()%11;
	       g_col = rand()%11;
	}	       
    }

    //fprintf(stderr, "pot-o-gold location: (%d, %d)\n", g_row, g_col);

    int done = 0;

    // demo loop...
    /*
    while(!done) {
        printf("> ");
        char c = read_cmd();
	
        fprintf(stderr, "DEMO:  read_cmd() returned '%c'\n", c);

        if(c=='q') 
            done = 1;
		
    }*/
    while(!done){
	printf("Direction: ");
	char c = read_cmd();
	int old_d, new_d;
	//calculates distance from gold
	old_d = abs(g_row-p_row) + abs(g_col-p_col);
	switch(c){
		case 'q'://if the user quits
			done = 1;
			printf("QUITTING\n");
			break;
		case 'n':
            		if (inrange(p_row-1,p_col)){//checks if move is valid
                		p_row--;
			}
            		else{
                		printf("\tOUCH\n");
			}
			moves++;//incrments move counter
			break;
        	case 's':
            		if (inrange(p_row+1,p_col)){
               	 		p_row++;
				
			}
            		else{
                		printf("\tOUCH\n");
			}
			moves++;
			break;
		case 'w':
			if (inrange(p_row, p_col-1)){
				p_col--;
			}
			else{
				printf("\tOUCH\n");
			}
			moves++;
			break;
		case 'e':
			if (inrange(p_row, p_col+1)){
				p_col++;
			}
			else{
				printf("\tOUCH\n");
			}
			moves++;
			break;
		default:
			printf("Invalid input. Try again.\n");
			continue;

			
	}//end of switch case


	//calculates new distance from gold
	new_d = abs(g_row-p_row)+abs(g_col-p_col);
	if (new_d == 0){//if the new distance is 0 away from the gold
		printf("\tHOORAY!\n\nTotal Moves: %i\nGoodbye!\n", moves);
		done = 1;
	}
	else if (old_d > new_d){//if the new distance is closer than before
		printf("\tGETTING WARMER!\n");
		continue;
	}
	else if (old_d < new_d){//if the new distance is further than before
		printf("\tGETTING COLDER!\n");
		continue;
	}

    }//end of loop

}//end of main()
