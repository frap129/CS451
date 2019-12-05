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
sem_t waiting_mutex;
sem_t get_floor_mutex;
sem_t direction_mutex;

/*
    Function Name: init_elevator
    Input to the method: A pointer to options
    Output(Return value): None (void)
    Brief description of the task: Initialize the elevator globals
 */
void init_elevator(options *opts) {

    // Initialize the lift global
    lift.dir = UP;
    lift.current_floor = 0;
    lift.stops = (int *) malloc(sizeof(int)*opts->num_floors);
    lift.waiting = (int *) malloc(sizeof(int)*opts->num_floors);
    for (int i = 0; i < opts->num_floors; i++) {
        lift.stops[i] = 0;
        lift.waiting[i] = 0;
    }

    // Initialize semaphores
    sem_init(&add_stop_mutex, 0, 1);
    sem_init(&waiting_mutex, 0, 1);
    sem_init(&get_floor_mutex, 0, 1);
    sem_init(&direction_mutex, 0, 1);
}

/*
    Function Name: add_stop
    Input to the method: Floor to add a stop on (int)
    Output(Return value): None (void)
    Brief description of the task: Request a stop at a floor
 */
void add_stop(int floor) {
    sem_wait(&add_stop_mutex);
    lift.stops[floor] += 1;
    sem_post(&add_stop_mutex);
}

/*
    Function Name: call_elevator
    Input to the method: Floor to add a stop on (int)
    Output(Return value): None (void)
    Brief description of the task: Request pickup from elevator
 */
void call_elevator(int floor) {
    sem_wait(&waiting_mutex);
    lift.waiting[floor] += 1;
    sem_post(&waiting_mutex);
    add_stop(floor);
}


/*
    Function Name: get_floor
    Input to the method: None
    Output(Return value): lift.current_floor (int)
    Brief description of the task: Safely return lift.current_floor
 */
int get_floor() {
    sem_wait(&get_floor_mutex);
    int ret = lift.current_floor;
    sem_post(&get_floor_mutex);

    return ret;
}

#ifdef EXTRA_CREDIT
/*
    Function Name: get_direction
    Input to the method: None
    Output(Return value): lift.dir (int)
    Brief description of the task: Safely return direction of elevator
 */
direction get_direction() {
    sem_wait(&direction_mutex);
    direction ret = lift.dir;
    sem_post(&direction_mutex);

    return ret;
}
#endif // EXTRA_CREDIT


/*
    Function Name: print_waiting
    Input to the method: Number of floors (int)
    Output(Return value): None (void)
    Brief description of the task: Print people waiting at each floor
 */
void print_waiting(int num_floors) {
    printf("\t\t\t\t\t\tElevator: People waiting at each floor:\n");
    printf("\t\t\t\t\t\tFloor\tPeople\n");
    sem_wait(&waiting_mutex);
    for (int i = 0; i < num_floors; i++)
        printf("\t\t\t\t\t\t%d\t%d\n", i, lift.waiting[i]);
    sem_post(&waiting_mutex);
}

/*
    Function Name: get_floor
    Input to the method: Number of floors (int)
    Output(Return value): None (void)
    Brief description of the task: Handle changing floors
 */
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

/*
    Function Name: run_elevator
    Input to the method: A pointer to options (cast from void*)
    Output(Return value): NULL (void *)
    Brief description of the task: Handle elevator stops
 */
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
            sem_wait(&waiting_mutex);
            lift.waiting[get_floor()] = 0;
            sem_post(&waiting_mutex);
            last_stop = time(0);
        }
        sem_post(&add_stop_mutex);
        if ((time(0)-last_stop) > opts->max_wander_time) {
            printf("\t\t\t\t\t\tElevator: Exiting the system\n");    
            done = 1;
        } else
            move_floor(opts->num_floors);
    }

    free(opts);
    free(lift.stops);
    return NULL;
}