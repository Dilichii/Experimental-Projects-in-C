#include <stdlib.h>
#include "memcheck.h"
#include "linked_list.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>



/**
 * This function takes a string and outputs the usage statement 
 * with the error message. 
 * Returns void
 */
void output_usage(char *p_name);

node *quicksort(node *list);

int main(int argc, char *argv[]) {
    int count = 0;
    int index = 0;
    bool q_true = false;
    node *list;        /* pointer to the list */
    node *temp;        /* temporary pointer to node */
    node *sorted;
    list = NULL;


    /* Prints usage when no arguments given */
    if (argc == 1) {
        output_usage(argv[0]);
    }

    /* Checks if -b or -q flags are given 
     * If so, changes boolean
     */
    for (index = 1; index < argc; index++) {
        if (strcmp(argv[index], "-q") == 0) {
            q_true = true;
        } else {
            temp = create_node(atoi(argv[index]), list);
            list = temp;
            count++;
        }
    }

    /* checks if no integers are given and if so prints error */
    if (count == 0) {
        output_usage(argv[0]);
    }

    sorted = quicksort(list);    

    
    
    if(q_true) {
        printf("HUHHHHH");
        printf("\n");
        printf("\n");
        print_list(sorted);
    }

    print_memory_leaks();

    return 0;
}

node *quicksort(node *list) {
    node *curr;
    node *newNode = NULL;
    node *greaterThan = NULL;
    node *greaterThan_end;
    node *lesserThan = NULL;
    node *lesserThan_end;
    node *sortedList;
    node *gSort;
    node *lSort;
    node *firstSaved;
    
    if(list == NULL || list->next == NULL) {
        return copy_list(list);
    } 
    firstSaved = copy_list(list);

    
    for(curr = list; curr->next != NULL; curr = curr->next) {
        if(curr->data >= firstSaved->data) {
            newNode = create_node(curr->data, NULL);
            if(greaterThan == NULL) {
                greaterThan = newNode;
                greaterThan_end = newNode;
            } else {
                greaterThan_end->next = newNode;
                greaterThan_end = newNode;
            }
        } else {
            newNode = create_node(curr->data, NULL);
            if(lesserThan == NULL) {
                lesserThan = newNode;
                lesserThan_end = newNode;
            } else {
                lesserThan_end->next = newNode;
                lesserThan_end = newNode;
            }
        }
        if(newNode != NULL) {
            free_list(newNode);
        }
        
    }
    
    
    gSort = quicksort(greaterThan);
    if(greaterThan != NULL) {
        free_list(greaterThan);
    }
    greaterThan = gSort;

    lSort = quicksort(lesserThan);
    if(lesserThan != NULL) {
        free_list(lesserThan);
    }    
    lesserThan = lSort;
    
    if(lSort != NULL) {
        sortedList = append_lists(lSort, firstSaved);
        sortedList = append_lists(sortedList, gSort);
        
    } else {
        sortedList = append_lists(firstSaved, gSort);
    }
    
    return sortedList; 
}
 
void output_usage(char *p_name) {
    fprintf(stderr, 
            "usage: %s [-q] num1 [num2 ... ] \n",
            p_name);
    exit(1);
}