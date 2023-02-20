/*
 * Author: Michael Oliver 
 * Date: 2/11/2023
 * Last Edit: 2/11/2023
 * KU ID: 3016991
 * Purpose: EECS 348 Lab exercise -- also to learn about recursion in C 
 * Key take away: Recursion works simular to python with basic recursion -- however it does seem that it is a lot easier to run into call stack overflow -- also arrays are confusing in C(might be a good idea to make a reliable class that can mimic linked_lists from EECS_268) 
 */


#include <stdio.h>	// libaries to include
#include <stdbool.h>	

#define MAX_SCORE 100		

int results[MAX_SCORE][5];	
int results_count;

bool is_dup(int TD_con, int TD_FG, int TD, int FG, int SF) { 	// is_dup checks for duplicate results -- without it in the output we would have tons of repeats -- it uses a for in loop and checks with a if statement
    for (int i = 0; i < results_count; i++) {			// however I believe that this is a duct tape fix because say we had a really high score we wanted to test for I know thousands of entries thousands of times would be tested; meaning mem issues? 
        if (results[i][0] == TD_con && results[i][1] == TD_FG && results[i][2] == TD && results[i][3] == FG && results[i][4] == SF) {	// I will add that I saw online I could use function called malloc() and free() but I felt uncomfortable using either because I don't understand pointers (read up on later)  
            return true;
        }
    }
    return false; // false result good -- means we have no duplicates 
}


void print_combo(int score, int TD_con, int TD_FG, int TD, int FG, int SF) { // print_combo is a recursive function that prints once it hits it's only base case of the score = 0
    if (score == 0) {					// base case
        if (!is_dup(TD_con, TD_FG, TD, FG, SF)) {
            results[results_count][0] = TD_con;
            results[results_count][1] = TD_FG;
	    results[results_count][2] = TD;
            results[results_count][3] = FG;
	    results[results_count][4] = SF;
            results_count++;
            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", TD_con, TD_FG, TD, FG, SF);
        }
        return; // backtrack -- or take a step back 
    }

    if (score >= 2) {						// recursive calls 
        print_combo(score - 2, TD_con, TD_FG, TD, FG, SF + 1);	// first check safety
    }
    if (score >= 3) {
        print_combo(score - 3, TD_con, TD_FG, TD, FG + 1, SF);	// then field goal
    }
    if (score >= 6) {
        print_combo(score - 6, TD_con, TD_FG, TD + 1, FG, SF);  // then touchdown 
    }
    if (score >= 7) {
        print_combo(score - 7, TD_con, TD_FG + 1, TD, FG, SF);	// then touchdown with field goal
    }
     if (score >= 8) {
        print_combo(score - 8, TD_con + 1, TD_FG, TD, FG, SF);	// lastly touchdown w/ conversion
    }
}

int main() {	// main - or driver
    int score;	
    printf("Enter the score: "); // get user input
    scanf("%d", &score);
    if (score < 2){
	    return 1;		// kill program because we can't successfully get a result
   	}
    print_combo(score, 0, 0, 0, 0, 0); // print combo takes in the starting score and then all zeros since we want to test all possiblities 
    return 0; // congrats made it to the end 
}
