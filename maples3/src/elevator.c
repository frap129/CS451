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

// Globals and semaphores
elevator lift;
sem_t add_stop_mutex;
sem_t waiting_mutex;
sem_t get_floor_mutex;
sem_t direction_mutex;
sem_t doors_mutex;

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
    lift.doors_open = 0;
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
    sem_init(&doors_mutex, 0, 1);
}

/*
    Function Name: add_stop
    Input to the method: Floor to add a stop on (int)
    Output(Return value): None (void)
    Brief description of the task: Request a stop at a floor
 */
void add_stop(int floor) {
    // Wait, increment, post
    sem_wait(&add_stop_mutex);
    lift.stops[floor]++;
    sem_post(&add_stop_mutex);
}

/*
    Function Name: call_elevator
    Input to the method: Floor to add a stop on (int)
    Output(Return value): None (void)
    Brief description of the task: Request pickup from elevator
 */
void call_elevator(int floor) {
    // Wait, increment, post
    sem_wait(&waiting_mutex);
    lift.waiting[floor]++;
    sem_post(&waiting_mutex);

    // Add a stop as well
    add_stop(floor);
}


/*
    Function Name: get_floor
    Input to the method: None
    Output(Return value): lift.current_floor (int)
    Brief description of the task: Safely return lift.current_floor
 */
int get_floor() {
    // Wait, read, post
    sem_wait(&get_floor_mutex);
    int ret = lift.current_floor;
    sem_post(&get_floor_mutex);

    return ret;
}

/*
    Function Name: get_doors
    Input to the method: None
    Output(Return value): lift.doors_open (bool-style int)
    Brief description of the task: Safely return lift.doors_open
 */
int get_doors() {
    // Wait, read, post
    sem_wait(&doors_mutex);
    int ret = lift.doors_open;
    sem_post(&doors_mutex);

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
    // Wait, read, post
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
    // Print the table header
    printf("\t\t\t\t\t\tElevator: People waiting at each floor:\n");
    printf("\t\t\t\t\t\tFloor\tPeople\n");

    // Loop over each floor and print
    sem_wait(&waiting_mutex);
    for (int i = 0; i < num_floors; i++)
        printf("\t\t\t\t\t\t%d\t%d\n", i, lift.waiting[i]);
    sem_post(&waiting_mutex);
}

/*
    Function Name: move_floor
    Input to the method: Number of floors (int)
    Output(Return value): None (void)
    Brief description of the task: Handle changing floors
 */
void move_floor(int num_floors) {
    // Sleep to simulate movement
    sleep(1);

    // Change floor based on direction
    sem_wait(&get_floor_mutex);
    sem_wait(&direction_mutex);
    if (lift.dir == UP)
        lift.current_floor++;
    else
        lift.current_floor--;
    sem_post(&direction_mutex);
    sem_post(&get_floor_mutex);

    // Check if we've checked the top/bottom, print, and change direction
    if (get_floor() == (num_floors-1)) {
        printf("\t\t\t\t\t\tElevator: At floor %d, heading to 0\n",
            num_floors-1);
        sem_wait(&direction_mutex);
        lift.dir = DOWN;
        sem_post(&direction_mutex);
    } else if (get_floor() == 0) {
        printf("\t\t\t\t\t\tElevator: At floor 0, heading to %d\n",
            num_floors-1);
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
    // Initialize local variables
    options *opts = (options *) arg;
    int done = 0;
    time_t last_stop = time(0);

    // Loop until done is changed to 1
    while(!done) {
        // Check if there are any stops on this floor
        sem_wait(&add_stop_mutex);
        if (lift.stops[get_floor()] > 0){
            // Print that we have to stop
            printf("\t\t\t\t\t\tElevator: Stopping at floor %d\n",
                get_floor());

            // Open the doors
            sem_wait(&doors_mutex);
            lift.doors_open = 1;
            sem_post(&doors_mutex);

            // Clear stops and update last_stop time
            lift.stops[get_floor()] = 0;
            sleep(1);
            last_stop = time(0);

            // Close the doors
            sem_wait(&doors_mutex);
            lift.doors_open = 0;
            sem_post(&doors_mutex);
        }

        // Clear waiting count
        sem_post(&add_stop_mutex);
        sem_wait(&waiting_mutex);
        lift.waiting[get_floor()] = 0;
        sem_post(&waiting_mutex);

        /* Check if we've picked anyone up in the last max_wander_time
           seconds. If we haven't, exit. If we have, move floors */ 
        if ((time(0)-last_stop) > opts->max_wander_time) {
            printf("\t\t\t\t\t\tElevator: Exiting the system\n");    
            done = 1;
        } else
            move_floor(opts->num_floors);
    }

    // Cleanup once the loop ends
    free(opts);
    free(lift.stops);
    return NULL;
}