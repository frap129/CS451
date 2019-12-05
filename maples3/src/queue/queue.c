/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 5th, 2019
 * Name of this file: queue.c
 * Description of the program: A basic queue implementation
 */
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "queue.h"

/*
    Function Name: init_queue
    Input to the method: None
    Output(Return value): pointer to a queue
    Brief description of the task: Creates an empty queue
 */
queue *init_queue() {
    queue *new = (queue*) malloc(sizeof (queue));
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}

/*
    Function Name: free_queue
    Input to the method: Pointer to a queue
    Output(Return value): None (void)
    Brief description of the task: Frees pointers in a queue
 */
void free_queue(queue *this) {
    node *item;

    while (!is_empty(this)) {
        item = dequeue(this);
        free(item);
    }

    free(this);
}

/*
    Function Name: enqueue
    Input to the method: Queue pointer, floor(int), time(int) 
    Output(Return value): None (void)
    Brief description of the task: Create a node and add to queue's tail
 */
void enqueue(queue *this, int floor, int time) {
    node *item = init_node();
    item->floor = floor;
    item->time = time;

    if (this->head == NULL)
        this->head = item;
    else
        this->tail->next = item;

    this->tail = item;
    this->size++;
}

/*
    Function Name: dequeue
    Input to the method: Queue pointer
    Output(Return value): Node pointer that was at HEAD
    Brief description of the task: Remove a node from head and return it
 */
node *dequeue(queue *this) {
    node *item = NULL;

    if (this->head != NULL) {
        item = this->head;
        this->head = item->next;
        this->size--;
    }

    return item;
}

/*
    Function Name: is_empty
    Input to the method: Queue pointer 
    Output(Return value): 1 if queue empty, 0 otherwise
    Brief description of the task: Create a node and add to queue
 */
int is_empty(queue *this) {
    return (this->size == 0);
}