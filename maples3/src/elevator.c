/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: elevator.c
 * Description of the program: Functions for running the elevator thread
 */

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "elevator.h"

elevator lift;
sem_t add_stop_mutex;
sem_t get_floor_mutex;

void init_elevator(options opts) {
	elevator new;
	new.dir = UP;
	new.num_floors = opts.num_floors;
	new.max_wander_time = opts.max_wander_time;
	new.stops = (int *) malloc(sizeof(int)*new.num_floors);

	sem_init(&add_stop_mutex, 0, 1);
	sem_init(&get_floor_mutex, 0, 1);

	lift = new;
}

void add_stop(int floor) {
	sem_wait(&add_stop_mutex);
	lift.stops[floor] += 1;
	sem_post(&add_stop_mutex);
}

int get_floor() {
	sem_wait(&get_floor_mutex);
	int ret = lift.current_floor;
	sem_post(&get_floor_mutex);

    return ret;
}

void print_waiting() {
	printf("\t\t\t\t\t\tElevator: Number of people at each floor:\n");
	printf("\t\t\t\t\t\tFloor\tPeople\n");
	sem_wait(&add_stop_mutex);
	for (int i = lift.num_floors; i > 0; i--)
        printf("\t\t\t\t\t\t%d\t%d\n", i, lift.stops[i-1]);
    sem_post(&add_stop_mutex);
}

void move_floor() {
	sleep(1);
	sem_wait(&get_floor_mutex);
    if (lift.dir == UP)
    	lift.current_floor++;
    else
    	lift.current_floor--;
    sem_post(&get_floor_mutex);

	if (get_floor() == lift.num_floors) {
		printf("\t\t\t\t\t\tElevator: At floor %d, heading to 0\n", lift.num_floors);
		lift.dir = DOWN;
	} else if (get_floor() == 0) {
		printf("\t\t\t\t\t\tElevator: At floor 0, heading to %d\n", lift.num_floors);
        print_waiting();
		lift.dir = UP;
	}
}

void *run_elevator() {
    int done = 0;
    time_t last_stop = time(0);
	while(!done) {
		sem_wait(&add_stop_mutex);
        if (lift.stops[get_floor()]){
        	printf("\t\t\t\t\t\tElevator: Stopping at floor %d\n", get_floor());
            sleep(1);
        	lift.stops[get_floor()] = 0;
        	last_stop = time(0);
        }
        sem_post(&add_stop_mutex);
        if ((time(0)-last_stop) > lift.max_wander_time) {
        	printf("\t\t\t\t\t\tElevator: Exiting the system\n");	
        	done = 1;
        } else
            move_floor();
	}

	return NULL;
}