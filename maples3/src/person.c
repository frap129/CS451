/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 5th, 2019
 * Name of this file: person.c
 * Description of the program: Function for running the person threads
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "person.h"
#include "utils.h"
#include "elevator.h"
#include "node.h"

/*
    Function Name: run_person
    Input to the method: A pointer to person (cast from void *)
    Output(Return value): NULL (void *)
    Brief description of the task: Handle the movement of a person
 */
void *run_person(void *arg) {
    // Initialize local variables
    int floor = 0;
    person *me = (person *)arg;
    node *next_stop;
#ifndef EXTRA_CREDIT    
    // Run the person loop for each input pair
    while(!is_empty(me->schedule)) {
        // Update stop
        next_stop = dequeue(me->schedule);

        // Verify that the next floor is a different floor
        if (floor != next_stop->floor) {
#else // EXTRA_CREDIT
    int wait = 0;

    // Run the person loop for each input pair, ignore waits
    while(!is_empty(me->schedule) || wait) {

        // Update stop if we're not waiting
        if (!wait)
            next_stop = dequeue(me->schedule);

        /* Verify that the next floor is a different floor and that the
           elevator is going the correct direction */
        if (floor != next_stop->floor &&
            ((floor < next_stop->floor && get_direction() == UP)
            || (floor > next_stop->floor && get_direction() == DOWN))) {
            wait = 0;
#endif // EXTRA_CREDIT

            // Call the elevator to the currrent floor
            printf("Person %d: Waiting for elevator on floor %d\n", me->id, 
                floor);
            call_elevator(floor);
            while(get_floor() != floor) /* do nothing */;

            // Get on the elevator and go to the next floor
            floor = next_stop->floor;
            printf("Person %d: Pressed the button for floor %d\n", me->id,
                floor);
            add_stop(floor);
            while(get_floor() != floor) /* do nothing */;

            // Get off once the doors are open
            while(!get_doors()) /* do nothing */;
            printf("Person %d: Getting off at floor %d\n", me->id, floor);

#ifdef EXTRA_CREDIT
        } else if (floor != next_stop->floor && !wait) {
            /* If the floor is different but direction is incorrect, wait
               until direction is correct.*/
            printf("Person %d: Elevator going wrong direction, waiting a " 
                "cycle\n", me->id);
            wait = 1;

        } else if (!wait) {
#else // !EXTRA_CREDIT
        } else {
#endif // EXTRA_CREDIT

            /* If the next floor is the same as the current, skip the
               elevator steps */
            printf("Person %d: Already on floor %d\n", me->id, floor);    
        }

#ifdef EXTRA_CREDIT
        // Skip wander if waiting for a cycle
        if (!wait) {
#endif // EXTRA_CREDIT

        // Wander for the requsted time
        printf("Person %d: Wandering for %d seconds\n", me->id,
            next_stop->time);    
        sleep(next_stop->time);
        free(next_stop);
#ifdef EXTRA_CREDIT
        }
#endif // EXTRA_CREDIT
    }

    // When the loop is done, clean up and exit
    printf("Person %d: Leaving the building\n", me->id);    
    free_queue(me->schedule);
    pthread_exit(NULL);
    return NULL;
}