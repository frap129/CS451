/*
 * Author: Joseph Maples
 * Assignment Number: 4
 * Date of Submission: TBD
 * Name of this file: list.c
 * Description of the program:
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
    empty->length = size - 1;
    empty->prev = NULL;
    empty->next = NULL;

    // Initialize a list struct
    list *new = (list*) malloc(sizeof (list));
    new->head = empty;
    new->tail = empty;
    new->size = 1;
    return new;
}

/*
    Function Name: free_list
    Input to the method: Pointer to a list
    Output(Return value): None (void)
    Brief description of the task: Frees pointers in a list
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
    Function Name: insert
    Input to the method: list pointer, size(int), proc(int), fit(int)
    Output(Return value): Boolean (true: space, false: no space)
    Brief description of the task: Create a block and add to first free block
 */
BOOL insert(list *this, LLU size, int proc, int fit) {
    // TODO
}

void rm_block(list *this, block *rm) {
    // Remove from block links
    if (rm->next != NULL)
        rm->next->prev = rm->prev;
    if (rm->prev != NULL)
        rm->prev->next = rm->next;

    // Make sure the block isn't head or tail
    if (this->head == rm)
        this->head = rm->next;
    if (this->tail == rm)
        this->tail = rm->prev;

    // clean up
    this->size--;
    free(rm);
}

/*
    Function Name: release
    Input to the method: list pointer, process number
    Output(Return value): None (void)
    Brief description of the task: Find a node and remove it
 */
void release(list *this, int proc) {
    // Find the block to release
    block *check = this->head;
    while (check->proc != proc)
        check = check->next;

    // Reallocate the space
    if (check->prev->proc == FREE) {
        check->prev->length += check->length;
        rm_block(this, check);
    } else if (check->next->proc == FREE) {
        check->length += check->next->length;
        rm_block(this, check->next);
    } else {
        check->proc = FREE;
    }
}

void compact(list *this) {

}

void stat(list *this) {
    block *read = this->head;
    do {
        if (read->proc != FREE)
            printf("Address [%llu:%llu] Process P%d\n",
                read->start, read->length, read->proc);
        else
            printf("Address [%llu:%llu] Unused\n",
                read->start, read->length);
        read = read->next;
    } while (read != NULL);
}
