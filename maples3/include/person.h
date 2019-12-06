/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 6th, 2019
 * Name of this file: person.h
 * Description of the program: Header for person.c
 */
#ifndef PERSON_H
#define PERSON_H

#include <pthread.h>
#include "queue.h"

// Struct of a person's data
struct person_data {
    pthread_t thread;
    int id;
    int num_pairs;
    queue *schedule;
};

// Typedef struct so it can be used like an object
typedef struct person_data person;

// Functions provided by person.c
void *run_person(void *arg);

#endif // PERSON_H