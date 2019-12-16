/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 6th, 2019
 * Name of this file: list.h
 * Description of the program: Header for list.c
 */
#ifndef LIST_H
#define LIST_H

// Macro Constants
#define LLU		long long unsigned int
#define BOOL	int // For booleans
#define TRUE	1 // For booleans
#define FALSE	0 // For booleans
#define FREE	-1 // for int proc in block

// Fit type
#define FIRST	0
#define BEST	1
#define WORST	2

// Struct for block data
struct block_data {
	int proc;
	LLU start;
	LLU length;
    struct block_data *next;
    struct block_data *prev;
};
// Typedef struct so it can be used like an object
typedef struct block_data block;

// Struct for queue data
struct list_data {
    block *head;
    block *tail;
    int size;
};
// Typedef struct so it can be used like an object
typedef struct list_data list;

// Functions provided by list.c
list *init_list(LLU size);
void free_list(list *this);
BOOL insert(list *this, LLU size, int proc, int fit);
void release(list *this, int proc);
void compact(list *this);
void stat(list *this);

#endif // QUEUE_H