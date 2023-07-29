#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define ARG_LIMIT 32

/**
 * This function takes a string and outputs the usage statement 
 * with the error message. 
 * Returns void
 */
void output_usage(char *p_name);

/**
 * Takes an int array and the int size and sorts the array 
 * from minimum to largest usinging selection sort.
 * Returns void
 */
void selection_sort(int *array, int size);

/* 
 *  Takes an int array and the int size and sorts the array 
 * from minimum to largest usinging bubble sort.
 * Returns void
 * */
void bubble_sort(int *array, int size);

int main(int argc, char *argv[]) {
    /* Intializes all necessary initial variables */
    int main_array[ARG_LIMIT];
    int count = 0;
    int index = 0;
    bool b_true = false;
    bool q_true = false;

    /* Prints usage when no arguments given */
    if (argc == 1) {
        output_usage(argv[0]);
    }

    /* Checks if -b or -q flags are given 
     * If so, changes boolean
     */
    for (index = 1; index < argc; index++) {
        if (strcmp(argv[index], "-b") == 0) {
            b_true = true;
        } else if (strcmp(argv[index], "-q") == 0) {
            q_true = true;
        } else {
            if (count == ARG_LIMIT) {
                output_usage(argv[0]);
            }
            main_array[count] = atoi(argv[index]);
            count++;
        }
    }

    /* checks if no integers are given and if so prints error */
    if (count == 0) {
        output_usage(argv[0]);
    }

    /* Prints required sorting algroithm based on flag boolean */
    if (!b_true) {
        selection_sort(main_array, count);
    } else {
        bubble_sort(main_array, count);
    }

    /* Decides if output is printed */
    if (!q_true) {
        for (index = 0; index < count; index++) {
            printf("%d\n", main_array[index]);
        }
    } 
    
    return 0;
}


void output_usage(char *p_name) {
    fprintf(stderr, 
            "usage: %s [-b] [-q] num1 [num2 ... ] (maximum 32 integers)\n",
            p_name);
    exit(1);
}


void sort_checker(int *array, int size) {
    int index = 0;
    for (index = 1; index < size; index++)
    {
        assert(array[index] >= array[index - 1]);
    }
}


void selection_sort(int *array, int size) {
    /* Intializes all necessary initial variables */
    int start = 0;
    int index = 0;
    int smallest = 0;
    int temp = 0;

    /** Runs loop on all array members and corrects each index 
    */
    for (start = 0; start < size; start++) {
        smallest = start;

        for (index = start + 1; index < size; index++) {
            if (array[index] < array[smallest]) {
                smallest = index;
            }
        }
        temp = array[start];
        array[start] = array[smallest];
        array[smallest] = temp;
    }

    sort_checker(array, size);
}


void bubble_sort(int *array, int size) {
    /* Intializes all necessary initial variables */
    int start = 0;
    int index = 0;
    int temp = 0;

    for (start = 0; start < size - 1; start++) {
        for (index = 0; index < size - start - 1; index++) {
            if (array[index] > array[index + 1]) {
                temp = array[index];
                array[index] = array[index + 1];
                array[index + 1] = temp;
            }
        }
    }

    sort_checker(array, size);
}