/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 6th, 2019
 * Name of this file: elevator.h
 * Description of the program: Header for elevator.c
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <pthread.h>

typedef int direction;
#define UP 1
#define DOWN 0

struct elevator_data {
    pthread_t thread;
    direction dir;
    int current_floor;
    int *stops;
    int *waiting;
    int doors_open;
};

// Typedef struct so it can be used like an object
typedef struct elevator_data elevator;

// Functions provided by elevator.c
void init_elevator(options *opts);
void add_stop(int floor);
void call_elevator(int floor);
int get_floor();
int get_doors();
void *run_elevator(void *arg);
#ifdef EXTRA_CREDIT
direction get_direction();
#endif // EXTRA_CREDIT

#endif // ELEVATOR_H