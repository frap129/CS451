/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: person.c
 * Description of the program: Functions for running the person threads
 */

#include <stdio.h>
#include <unistd.h>
#include "person.h"
#include "utils.h"
#include "elevator.h"
#include "node.h"

void *run_person(void *arg) {
    int floor = 0;
    person *me = (person *)arg;

    for(int i = 0; i < me->num_pairs; i++) {
        node *next_stop = dequeue(me->schedule);
        if (floor != next_stop->floor) {
            printf("Person %d: Waiting for elevator on floor %d\n", me->id, floor);
            add_stop(floor);
            while(get_floor() != floor) /* do nothing */;
            floor = next_stop->floor;
            printf("Person %d: Waiting for elevator to reach floor %d\n", me->id, floor);
            add_stop(floor);
            while(get_floor() != floor) /* do nothing */;
            printf("Person %d: Getting off at floor %d\n", me->id, floor);
        } else {
            printf("Person %d: Already on floor %d\n", me->id, floor);    
        }
        printf("Person %d: Wandering for %d seconds\n", me->id, next_stop->time);    
        sleep(next_stop->time);
    }
    printf("Person %d: Leaving the building\n", me->id);    

    return NULL;
}