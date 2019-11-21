 
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

queue *init_queue() {
	queue *new = (queue*) malloc(sizeof (queue));
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
	return new;
}

void free_queue(queue *this) {
    node *item;

    while (!is_empty(this)) {
    	item = dequeue(this);
    	free(item);
    }

    free(this);
}

int enqueue(queue *this, node *item) {
	if (this->head == NULL) {
		this->head = item;
		this->tail = item;
	} else {
		this->tail->next = item;
		this->tail = item;
	}

	this->size++;

	return 0;
}

node *dequeue(queue *this) {
    node *item = NULL;

    if (this->head != NULL) {
        item = this->head;
    	this->head = item->next;
    	this->size--;
    }

    return item;
}

int is_empty(queue *this) {
	return (this->size == 0);
}