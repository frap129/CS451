/*
 * Author: Joseph Maples
 * Assignment Number: 4
 * Date of Submission: December 18th, 2019
 * Name of this file: list.c
 * Description of the program: A LinkedList-based analogy for memory allocation
 */
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/*
    Function Name: init_list
    Input to the method: size (int)
    Output(Return value): pointer to a list
    Brief description of the task: Creates an empty list
 */
list *init_list(LLU size) {
    // Initialize a block of free memory
    block *empty = (block*) malloc(sizeof (block));
    empty->proc = FREE;
    empty->start = 0;
    empty->length = size;
    empty->prev = NULL;
    empty->next = NULL;

    // Initialize a list struct
    list *new = (list*) malloc(sizeof (list));
    new->head = empty;
    new->tail = empty;
    return new;
}

/*
    Function Name: free_list
    Input to the method: Pointer to a list
    Output(Return value): None (void)
    Brief description of the task: Frees all pointers in a list
 */
void free_list(list *this) {
    /*
        Free all blocks in the list, one at a time
    */
    block *tmp, *rm = this->head;
    do {
        tmp = rm->next;
        free(rm);
        rm = tmp;
    } while (tmp != NULL);

    // Free the list
    free(this);
}

/*
    Function Name: find_fit
    Input to the method: list (list *), input size (long long unsigned int),
                         and fit (int)
    Output(Return value): pointer to a block
    Brief description of the task: Finds the best place to insert the new
                                   block based on size and fit.
 */
block *find_fit(list *this, LLU size, int fit) {
    block *cur = this->head;
    block *best = NULL;

    // Loop over every block in the list
    do {
        // Check if there is enough free space in the current block
        if (cur->proc == FREE && cur->length >= size) {
            // Break out early if using first fit
            if (fit == FIRST) {
                best = cur;
                break;
            }

            // Check if the block is better, worse, or the first fit.
            if (best == NULL || (cur->length < best->length && fit == BEST) ||
                (cur->length > best->length && fit == WORST))
                best = cur;
        }

        // Move to the next block
        cur = cur->next;
    } while (cur != NULL);

    // Return the best bock
    return best;
}

/*
    Function Name: insert
    Input to the method: list pointer, size(int), proc(int), fit(int)
    Output(Return value): Boolean (true: space, false: no space)
    Brief description of the task: Create a block and insert based on fit.
 */
BOOL insert(list *this, LLU size, int proc, int fit) {
    // Create a new block to insert
    block *new = (block*) malloc(sizeof(block));
    new->length = size;
    new->proc = proc;

    // Find the best block based on size and fit
    block *best = find_fit(this, size, fit);

    // If no fit could be found, return error
    if (best == NULL)
        return FALSE;

    /*
        Insert the new block and shrink the free space by the size of the new block.
    */
    new->start = best->start;
    new->prev = best->prev;
    new->next = best;
    best->start += size;
    best->length -= size;
    if (best->prev != NULL)
        best->prev->next = new;
    best->prev = new;
    if (best == this->head)
        this->head = new;

    return TRUE;
}

/*
    Function Name: rm_block
    Input to the method: Pointer to a list, pointer to a block
    Output(Return value): None (void)
    Brief description of the task: Completely remove a block from the list.
 */
void rm_block(list *this, block *rm) {
    // Remove from block links
    if (rm->next != NULL)
        rm->next->prev = rm->prev;
    if (rm->prev != NULL)
        rm->prev->next = rm->next;

    // Update head or tail if needed
    if (this->head == rm)
        this->head = rm->next;
    if (this->tail == rm)
        this->tail = rm->prev;

    // clean up
    free(rm);
}

/*
    Function Name: release
    Input to the method: list pointer, process number
    Output(Return value): None (void)
    Brief description of the task: Find a node and "free" its memory.
 */
void release(list *this, int proc) {
    // Find the block to release
    block *check = this->head;
    while (check != NULL && check->proc != proc)
        check = check->next;

    /*
        Check if any neighboring blocks are free so we can just increase their size rather than creating 2 adjacent free blocks. If no neigbors are free, just set the current block to free. This action is in a loop incase newly-moved neighbors are also free.
    */

    while (1) {
        if (check->prev != NULL && check->prev->proc == FREE) {
            check->prev->length += check->length;
            check = check->prev;
        } else if (check->next != NULL && check->next->proc == FREE) {
            check->length += check->next->length;
        } else {
            check->proc = FREE;
            break;
        }
        rm_block(this, check->next);
    }
}

/*
    Function Name: compact
    Input to the method: Pointer to a list
    Output(Return value): None (void)
    Brief description of the task: compacts unused memory into a single block.
 */
void compact(list *this) {
    block *cur = this->head;
    LLU free = 0;

    // Exit if we only have one block of memory
    if (cur->next == NULL && cur->prev == NULL)
        return;

    /*
        Remove all free blocks and keep a running total of their length. Subtract this length from the start of all proceeding blocks.
    */
    do {
        block *next = cur->next;
        if (cur->proc == FREE) {
            free += cur->length;
            rm_block(this, cur);
        } else
            cur->start -= free;


        // Move to the next block
        cur = next;
    } while (cur != NULL);

    /*
        Append a new block of free memory with the total length of all of the free blocks that were removed previously.
    */
    cur = this->tail;
    block *new = (block*) malloc(sizeof(block));
    new->proc = FREE;
    new->start = cur->start + cur->length;
    new->length = free;
    new->prev = cur;
    new->next = NULL;
    cur->next = new;
    this->tail = new;
}

/*
    Function Name: stat
    Input to the method: Pointer to a list
    Output(Return value): None (void)
    Brief description of the task: Print info on all blocks in the list.
 */
void stat(list *this) {
    // Initialize block to store current read in
    block *read = this->head;

    // Loop over each block
    do {
        // Calculate last bit
        LLU end = read->length + read->start - 1;

        // Print the correct statement
        if (read->proc != FREE)
            printf("Address [%llu:%llu] Process P%d\n",
                read->start, end, read->proc);
        else if (read->length > 0)
            printf("Address [%llu:%llu] Unused\n", read->start, end);

        // Move to next block
        read = read->next;
    } while (read != NULL);
}
