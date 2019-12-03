/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: elevator.h
 * Description of the program: Header for elevator.c
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <pthread.h>
#include "queue.h"
#include "utils.h"

typedef int direction;
#define UP 1
#define DOWN 0

struct elevator_data {
	pthread_t thread;
    direction dir;
    int num_floors;
	int current_floor;
	queue *stops;
};

// Typedef struct so it can be used like an object
typedef struct elevator_data elevator;

// Functions provided by elevator.c
void init_elevator(options opts);
void *run_elevator();

#endif // ELEVATOR_H