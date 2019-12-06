/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 5th, 2019
 * Name of this file: node.c
 * Description of the program: A node for the queue implimentation
 */
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

/*
    Function Name: init_node
    Input to the method: None
    Output(Return value): Pointer to a node
    Brief description of the task: Initialize a node struct
 */
node *init_node() {
	// Initialize a node struct
	node *new = (node *) malloc(sizeof (node));
    new->next = NULL;
    new->floor = 0;
    new->time = 0;
	return new;
}