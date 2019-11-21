#ifndef NODE_H
#define NODE_H

// Struct for queue data
struct node_data {
    struct node_data *next;
    int data;
};

// Typedef struct so it can be used like an object
typedef struct node_data node;

#endif // QUEUE_H