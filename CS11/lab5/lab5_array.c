#include <stdlib.h>
#include "memcheck.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/* Takes an array of integers and its length and returns 
    an array of integers newly updated with applied 
    automaton rules
    */
int *update(int *array, int numCells);

/* Takes an array of integers and its length and runs through
    the array. If the value of the array is 1 it prints a * 
    if the value of the array is 0 it prints a .
    */
void print(int *array, int numCells);

/* Takes an int array and frees its memory
*/
void freeVariables(int *array);

int main(int argc, char *argv[])
{
    /* Declares the mainArray and the varibles needed to
        initialize and loop through it.
    */
    int *array;
    int numGen = -1;
    int numCells = -1;
    int i;

    /* Creates a random seed */
    srand(time(NULL));

    /* Scans in user input for array parameters and 
        checks its validity. Returns an error message 
        if valid response not given
    */
    printf("Number of cells: ");
    scanf("%d", &numCells);
    if(numCells < 0) {
        fprintf(stderr, "Not an accepted argument.\n");
        exit(1);
    }

    printf("Number of generations: ");
    scanf("%d", &numGen);
    if(numGen < 0) {
        fprintf(stderr, "Not an accepted argument.\n");
        exit(1);
    }

    /* Initializes array based on user input */
    array = (int *)calloc(numCells, sizeof(int));

    /* Check that the calloc call succeeded. */
    if (array == NULL) {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }
    
    /* Fills array */
    array[0] = 0;
    array[numCells - 1] = 0;

    for(i = 1; i < numCells - 1; i++) {
        array[i] = rand() % (1 - 0 + 1) + 0;
    }

    /* Prints automaton */
    print(array, numCells); 
    for(i = 0; i < numGen; i++) {
        update(array, numCells);
    }
    
    /* Frees final variables and checks for memory leaks */
    freeVariables(array);
    print_memory_leaks();

    return 0;
}

void freeVariables(int *array) {
    free(array);
}

int *update(int *array, int numCells) {
    /* initializes neewArray on the vairable to 
        loop through it 
    */
    int i;
    int *newArray = (int *)calloc(numCells, sizeof(int));

    newArray[0] = 0;
    newArray[numCells - 1] = 0;

    /* Applies automaton rules to the newArray */
    for(i = 1; i < numCells - 1; i++) {
        if(array[i] == 0) {
            if(array[i - 1] == 1 && array[i + 1] == 1) {
                newArray[i] = 0;
            } else if(array[i - 1] == 1 || array[i + 1] == 1) {
                newArray[i] = 1;
            } else {
                newArray[i] = 0;
            }
        } else {
            newArray[i] = 0;
        }
    }

    /* Prints newArray, stores it, and frees memory */
    print(newArray, numCells);
    memcpy(array, newArray, numCells * sizeof(int));
    freeVariables(newArray);

    /* Returns orginal modified array */
    return(array);
}

void print(int *array, int numCells) {
    int i;

    /* Runs through the array. If the value of the array
        is 1 it prints a * if the value of the array is 0
        it prints a . 
    */
    for(i = 0; i < numCells; i++) {
        if(array[i]) {
            printf("*");
        } else {
            printf(".");
        }
    }

    printf("\n");
}