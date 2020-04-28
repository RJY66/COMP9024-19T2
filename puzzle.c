//Main function of boardADT
//Check validation and solvability of boards
//Written by Junyu Ren
//Date 26/06/2019
#include "boardADT.h"

/**
 * main method
 * @param no parameter here is ok
 * @return solvable or unsolvable or invalid input
 */
int main(void) {
    // define and read the start and goal line from stdin
    char *start_line;
    start_line = malloc(SIZE * sizeof(char));
    char *goal_line;
    goal_line = malloc(SIZE * sizeof(char));
    fgets(start_line, SIZE, stdin);
    fgets(goal_line, SIZE, stdin);
    //standard output 2 lines with one space between 2 numbers or a number and 'b'
    fprintf(stdout,"%s","start:");
    printline(start_line);
    fprintf(stdout,"%s","goal:");
    printline(goal_line);
    // create start board and goal board
    Board start_board = init_board(start_line);
    Board end_board = init_board(goal_line);

    // check whether boards are valid
    if (getsize(end_board)==0||getsize(start_board)==0||getlength(end_board)==0||getlength(start_board)==0||getsize(end_board)!=getsize(start_board)||getlength(end_board)!=getlength(start_board)||check_valid(start_board)!= true||check_valid(end_board)== false) {
        fprintf(stdout,"%s\n","Invalid input!");
        exit(EXIT_FAILURE);
    }
    else {
        // check boards solvable
        if (check_solvable(start_board, end_board) == true){
            fprintf(stdout,"%s\n","solvable");
        }
        if (check_solvable(start_board,end_board) == false){
            fprintf(stdout,"%s\n","unsolvable");
        }
    }
    // release memories
    free_memory_board(start_board);
    free_memory_board(end_board);
    free(start_line);
    free(goal_line);
    exit(EXIT_SUCCESS);
    return 0;
}
