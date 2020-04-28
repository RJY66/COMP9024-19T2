//Detailed implementation of each function
//Written by Junyu Ren
//Date 26/06/2019

#include "boardADT.h"
/**
 * define struct of board
 */
struct struct_board {
    int *elements;
    int length;
    int board_size;
};

/**
 * initialize new board based on input
 * @param stdin line
 * @return board
 */
Board init_board(char *line) {
    Board board;
    board = malloc(sizeof(struct struct_board));
    // check whether board is null
    if (board != NULL) {
        board->length = 0;
        board->board_size = 0;
        board->elements = NULL;
        // check whether line is null
        if (line != NULL) {
            // split elements
            char *split_num_str;
            split_num_str = strtok(line," \t");
            board->elements = malloc(sizeof(int)*SIZE);
            while (split_num_str != NULL) {
                // check blank
                if (strcmp("b",split_num_str) == 0) {
                    // set b=0 for convenience
                    *(board->elements + board->length) = 0;
                }
                if (strcmp("b",split_num_str) != 0) {
                    // convert char to int
                    *(board->elements + board->length) = atoi(split_num_str);
                }
                split_num_str = strtok(NULL," \t");
                board->length = board->length + 1;
            }
        }
        // set board size
        board->board_size = (int) sqrt(board->length);
    }
    return board;
}

/**
 * check the whether board is valid
 * @param board
 * @return true or false
 */
bool check_valid(Board board) {
    // check whether length is square of size
    if (board->length != pow(board->board_size,2)) {
        return false;
    }
    // check input null
    if (board->board_size == 0||board->length == 0||board->elements == NULL||board == NULL) {
        return false;
    }

    // check whether all the numbers exist and no duplication
    for (int i = 0; i < board->length; i++) {
        int flag = 0;
        for (int j = 0; j < board->length; j++) {
            // if exist
            if (*(board->elements + j) == i) {
                flag = 1;
                break;
            }
        }
        // if not exist
        if (flag == 0){
            return false;
        }
    }
    return true;
}

/**
 * check solvability of boards
 * @param start_board,end_board
 * @return true for solvable,false for unsolvable
 */
bool check_solvable(Board start_board, Board end_board) {
    //both odd or both even is solvable,else is unsolvable
   int sumcount = calc_disorder(end_board) + calc_disorder(start_board);
   if (sumcount % 2 == 0){
    return true;
   }
   return false;
}

/**
 * calculate all the disorder numbers
 * @param board
 * @return return count
 */
int calc_disorder(Board board) {
    int count = 0;
    // check null
    if (board != NULL) {
        for (int i = 0; i < board->length; i++) {
            // if blank
            if (*(board->elements + i) == 0) {
                if (board->board_size % 2 == 0)
                    count += i / board->board_size + 1;
            }
            else {
                // calculate all the disorder count
                for (int j = i + 1; j < board->length; j++)
                    if (*(board->elements + j) != 0) {
                        if(*(board->elements + j) < *(board->elements + i)){
                            count++;
                        }
                    }
                 }
        }
    }
    return count;
}

/**
 * get length of board
 * @return board length
 */
int getlength(Board board) {
    if (board == NULL) {
        return 0;
    }
    else {
        return board->length;
    }
}

/**
 * get size of board
 * @return board size
 */
int getsize(Board board){
    if (board==NULL){
        return 0;
    }
    else{
        return board->board_size;
    }
}

/**
 * release memories
 * no return
 */
void free_memory_board(Board board) {
    if (board != NULL) {
        if (board->elements != NULL) {
            free(board->elements);
        }
        free(board);
    }
    else{
        return;
    }
}

/**
 * standard output of lines
 * no return
 */
void printline(char *line){
    char *temp=malloc(SIZE*sizeof(char));
    //copy lines and deal with them
    strcpy(temp,line);
    char *temp_split=strtok(temp," \t");
    while(temp_split!=NULL){
        fprintf(stdout," %s",temp_split);
        temp_split=strtok(NULL," \t");
    }
    free(temp);
}
