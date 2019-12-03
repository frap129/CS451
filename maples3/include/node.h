#ifndef NODE_H
#define NODE_H

// Struct for queue data
struct wander_data {
    struct wander_data *next;
	int floor; // Used for person/elevator
	int time; // Used for person
};


// Typedef struct so it can be used like an object
typedef struct wander_data node;

// Functions provided by node.h
node *init_node();

#endif // QUEUE_H