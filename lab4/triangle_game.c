/* This function gets an initial board from the user 
    represented as a one dimensional array of integers.
    Then finds out if there are a set of moves which lead
    to a single peg left on the board. If no such set of 
    moves exist, a message is printed. If at least one set 
    of moves exist, the board positions that the moves go 
    through is printed in reverse order */

#include <stdio.h>
#include <stdbool.h>
#include "triangle_routines.h"

#define NMOVES 36

int moves[NMOVES][3] =
{
    {0, 1, 3},
    {3, 1, 0},
    {1, 3, 6},
    {6, 3, 1},
    {3, 6, 10},
    {10, 6, 3},
    {0, 2, 5},
    {5, 2, 0},
    {2, 5, 9},
    {9, 5, 2},
    {5, 9, 14},
    {14, 9, 5},
    {2, 4, 7},
    {7, 4, 2},
    {4, 7, 11},
    {11, 7, 4},
    {1, 4, 8},
    {8, 4, 1},
    {4, 8, 13},
    {13, 8, 4},
    {3, 7, 12},
    {12, 7, 3},
    {5, 8, 12},
    {12, 8, 5},
    {3, 4, 5},
    {5, 4, 3},
    {6, 7, 8},
    {8, 7, 6},
    {7, 8, 9},
    {9, 8, 7},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12},
};

/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
void make_move(int board[], int move[]);

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]);

/*
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order.
 */
int solve(int board[]);


int main(void)
{
    int board[BOARD_SIZE];
    triangle_input(board);

    printf("Here is the board you entered:\n");
    triangle_print(board);

    if(solve(board)) {
        triangle_print(board);
    } else {
        printf("This board is unsolvable.\n");
    }

    return 0;
}

int npegs(int board[]) {
    int i;
    int numPegs = 0;

    /* Counts all pegs in the board */
    for(i = 0; i < BOARD_SIZE; i++) {
        if(board[i] != 0) {
            numPegs += 1;
        }
    }
    return numPegs;
}

int valid_move(int board[], int move[]) {
    bool initialPegged = false;
    bool middlePegged = false;
    bool finalEmpty = false;

    /* Checks if move starting position is empty */
    if(board[move[0]] == 1) {
        initialPegged = true;
    }

    /* Checks if move middle position is empty */
    if(board[move[1]] == 1) {
        middlePegged = true;
    }

    /* Checks if move ending position is empty */
    if(board[move[2]] == 0) {
        finalEmpty = true;
    }

    /* Returns 1 if move is valid else returns 0 */
    return (initialPegged && middlePegged && finalEmpty);
}

void make_move(int board[], int move[]) {
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}

void unmake_move(int board[], int move[]) {
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;

}

int solve(int board[]) {
    int i;
    int solved = 0;

    /* Checks if the boards is already solved */
    if(npegs(board) == 1) {
        return 1;
    }

    /* Runs through every possible move and calls solve recursively */
    for(i = 0; i < NMOVES; i++) {
        if(valid_move(board, moves[i])) {
            make_move(board, moves[i]);
            solved = solve(board);

            if(solved == 1) {
                triangle_print(board);
                unmake_move(board, moves[i]);
                return 1;
            }
            unmake_move(board, moves[i]);
        }
    }

    return 0;

}
