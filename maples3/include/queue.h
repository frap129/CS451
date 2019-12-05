/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 5th, 2019
 * Name of this file: queue.h
 * Description of the program: Header for queue.c
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

// Struct for queue data
struct queue_data {
    node *head;
    node *tail;
    int size;
};

// Typedef struct so it can be used like an object
typedef struct queue_data queue;

// Functions provided by queue.c
queue *init_queue();
void free_queue(queue *this);
int enqueue(queue *this, int floor, int time);
node *dequeue(queue *this);
int is_empty(queue *this);

#endif // QUEUE_H