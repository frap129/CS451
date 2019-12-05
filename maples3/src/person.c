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
    int floor = 0;
    person *me = (person *)arg;
#ifdef EXTRA_CREDIT
    int wait = 0;
#endif // EXTRA_CREDIT

    for(int i = 0; i < me->num_pairs; i++) {
        node *next_stop = dequeue(me->schedule);
#ifdef EXTRA_CREDIT
        if (floor != next_stop->floor &&
            ((floor < next_stop->floor && get_direction() == UP)
            || (floor > next_stop->floor && get_direction() == DOWN))) {
            wait = 0;
#else
        if (floor != next_stop->floor) {
#endif // EXTRA_CREDIT
            printf("Person %d: Waiting for elevator on floor %d\n", me->id, floor);
            call_elevator(floor);
            while(get_floor() != floor) /* do nothing */;
            floor = next_stop->floor;
            printf("Person %d: Pressed the button for floor %d\n", me->id, floor);
            add_stop(floor);
            while(get_floor() != floor) /* do nothing */;
            printf("Person %d: Getting off at floor %d\n", me->id, floor);
#ifdef EXTRA_CREDIT
        } else if (floor != next_stop->floor) {
                printf("Person %d: Elevator going wrong direction, waiting a cycle\n", me->id);
                wait = 0;
#endif // EXTRA_CREDIT
        } else {
            printf("Person %d: Already on floor %d\n", me->id, floor);    
        }
#ifdef EXTRA_CREDIT
        if (!wait) {
#endif // EXTRA_CREDIT
        printf("Person %d: Wandering for %d seconds\n", me->id, next_stop->time);    
        sleep(next_stop->time);
        free(next_stop);
#ifdef EXTRA_CREDIT
        }
#endif // EXTRA_CREDIT
    }
    printf("Person %d: Leaving the building\n", me->id);    
    free_queue(me->schedule);
    pthread_exit(NULL);
    return NULL;
}