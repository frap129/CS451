/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 5th, 2019
 * Name of this file: elevator.c
 * Description of the program: Functions for running the elevator thread
 */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "person.h"
#include "utils.h"
#include "elevator.h"

elevator lift;
sem_t add_stop_mutex;
sem_t get_floor_mutex;
sem_t direction_mutex;

void init_elevator(options *opts) {
    elevator new;
    new.dir = UP;
    new.current_floor = 0;
    new.stops = (int *) malloc(sizeof(int)*opts->num_floors);
    for (int i = 0; i < opts->num_floors; i++)
        new.stops[i] = 0;

    sem_init(&add_stop_mutex, 0, 1);
    sem_init(&get_floor_mutex, 0, 1);
    sem_init(&direction_mutex, 0, 1);

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

#ifdef EXTRA_CREDIT
direction get_direction() {
    sem_wait(&direction_mutex);
    direction ret = lift.dir;
    sem_post(&direction_mutex);

    return ret;
}
#endif // EXTRA_CREDIT

void print_waiting(int num_floors) {
    printf("\t\t\t\t\t\tElevator: People waiting at each floor:\n");
    printf("\t\t\t\t\t\tFloor\tPeople\n");
    sem_wait(&add_stop_mutex);
    for (int i = 0; i < num_floors; i++)
        printf("\t\t\t\t\t\t%d\t%d\n", i, lift.stops[i]);
    sem_post(&add_stop_mutex);
}

void move_floor(int num_floors) {
    sleep(1);
    sem_wait(&get_floor_mutex);
    sem_wait(&direction_mutex);

    if (lift.dir == UP)
        lift.current_floor++;
    else
        lift.current_floor--;
    sem_post(&direction_mutex);
    sem_post(&get_floor_mutex);

    if (get_floor() == (num_floors-1)) {
        printf("\t\t\t\t\t\tElevator: At floor %d, heading to 0\n", num_floors-1);
        sem_wait(&direction_mutex);
        lift.dir = DOWN;
        sem_post(&direction_mutex);
    } else if (get_floor() == 0) {
        printf("\t\t\t\t\t\tElevator: At floor 0, heading to %d\n", num_floors-1);
        print_waiting(num_floors);
        sem_wait(&direction_mutex);
        lift.dir = UP;
        sem_post(&direction_mutex);

    }
}

void *run_elevator(void *arg) {
    options *opts = (options *) arg;
    int done = 0;
    time_t last_stop = time(0);
    while(!done) {
        sem_wait(&add_stop_mutex);
        if (lift.stops[get_floor()] > 0){
            printf("\t\t\t\t\t\tElevator: Stopping at floor %d\n", get_floor());
            sleep(1);
            lift.stops[get_floor()] = 0;
            last_stop = time(0);
        }
        sem_post(&add_stop_mutex);
        if ((time(0)-last_stop) > opts->max_wander_time) {
            printf("\t\t\t\t\t\tElevator: Exiting the system\n");    
            done = 1;
        } else
            move_floor(opts->num_floors);
    }

    return NULL;
}