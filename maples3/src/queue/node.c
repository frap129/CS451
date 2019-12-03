#include <stdlib.h>
#include <stdio.h>
#include "node.h"

node *init_node() {
	node *new = (node *) malloc(sizeof (node));
    new->next = NULL;
    new->floor = 0;
    new->time = 0;
	return new;
}