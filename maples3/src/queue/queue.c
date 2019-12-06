/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 6th, 2019
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
    // Initialize a queue struct
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

    // Dequeue and free all remaining nodes
    while (!is_empty(this)) {
        item = dequeue(this);
        free(item);
    }

    // Free the queue pointer
    free(this);
}

/*
    Function Name: enqueue
    Input to the method: Queue pointer, floor(int), time(int) 
    Output(Return value): None (void)
    Brief description of the task: Create a node and add to queue's tail
 */
void enqueue(queue *this, int floor, int time) {
    // Create a node with the given values
    node *item = init_node();
    item->floor = floor;
    item->time = time;

    // If the queue is empty, set to head. If not, append to tail
    if (this->head == NULL)
        this->head = item;
    else
        this->tail->next = item;

    // Update tail and size
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

    // If the queue is not empty, remove an item from head
    if (this->head != NULL) {
        item = this->head;
        this->head = item->next;
        this->size--;
    }

    // Return the dequeued node
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