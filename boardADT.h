//Header file of boardADT
//The interfaces of functions
//Written by Junyu Ren
//Date 26/06/2019

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define SIZE 1024

/**
 * define struct pointer
 */
typedef struct struct_board *Board;
/**
 * initialize a board based on input
   @return a new board
 */
Board init_board(char*);
/**
 * check whether a board is valid
   @return bool value true or false
 */
bool check_valid(Board);
/**
 * check whether a valid board is solvable
   @return bool value true or false
 */
bool check_solvable(Board start_board,Board goal_board);
/**
 * calculate disorder numbers
   @return the number of disorder elements
 */
int calc_disorder(Board);
/**
 * get the length of board
   @return board length
 */
int getlength(Board);
/**
 * get the size of board
   @return board size
 */
int getsize(Board);
/**
 * release memories
 * no return
 */
void free_memory_board(Board);
/**
 * standard output style
 * no return
 */
void printline(char*);
