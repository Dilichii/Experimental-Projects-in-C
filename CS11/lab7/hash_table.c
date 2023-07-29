/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *     Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int i = 0;
    int count = 0;
    while(s[i] != '\0') {
        count += s[i];
        i++;
    }

    return (count % NSLOTS);
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *sent = (node *)malloc(sizeof(node));
    sent->key = key;
    sent->value = value;
    sent->next = NULL;

    return sent;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *nextNode;

    while(list != NULL) {
        nextNode = list;
        list = list->next;
        free(nextNode->key);
        free(nextNode);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    hash_table *table = (hash_table *)malloc(sizeof(hash_table));
    node **arr = (node **)calloc(NSLOTS, sizeof(node *));
    table->slot = arr;
    return table;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    for(i = 0; i < NSLOTS; i++) {
        if(ht->slot[i] == NULL) {
            continue;
        }
        free_list(ht->slot[i]);
    }
    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    node *curNode;
    int numRep = hash(key);
    curNode = ht->slot[numRep];

    while(curNode != NULL) {
        if(strcmp(curNode->key, key) == 0) {
            return curNode->value;
        }
        curNode = curNode->next;
    }
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    node *curNode;
    int numRep = hash(key);
    
    if(get_value(ht, key) == 0) {
        curNode = create_node(key, value);
        curNode->next = ht->slot[numRep];
        ht->slot[numRep] = curNode;
        return;
    }

    curNode = ht->slot[numRep];
    while(strcmp(curNode->key, key) != 0) {
        curNode = curNode->next;
    }
    curNode->value = value;
    free(key);
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node *curr;

    for(i = 0; i < NSLOTS; i++) {
        curr = ht->slot[i];
        if(curr != NULL) {
            while(curr != NULL) {
                printf("%s %d\n", curr->key, curr->value);
                curr = curr->next;
            }
        }
    }
}


