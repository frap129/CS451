/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: elevator.c
 * Description of the program: Functions for running the elevator thread
 */

#include <stdio.h>
#include <semaphore.h>
#include "elevator.h"

elevator lift;
sem_t add_stop_mutex;
sem_t get_floor_mutex;

void init_elevator(options opts) {
	elevator new;
	new.dir = UP;
	new.num_floors = opts.num_floors;
	new.stops = init_queue();

	sem_init(&add_stop_mutex, 0, 1);
	sem_init(&get_floor_mutex, 0, 1);

	lift = new;
}

void add_stop(int floor) {
	sem_wait(&add_stop_mutex);
	enqueue_f(lift.stops, floor);
	sem_post(&add_stop_mutex);
}

int get_floor() {
	sem_wait(&get_floor_mutex);
	int ret = lift.current_floor;
	sem_post(&get_floot_mutex);

    return ret;
}

void *run_elevator() {
	return;
}