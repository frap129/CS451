/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: person.h
 * Description of the program: Header for person.c
 */
#ifndef PERSON_H
#define PERSON_H

// Struct of a person's data
struct person_data {
	//pthread_t thread;
	int num_pairs;
	int *max_wander_time[2];
};

// Typedef struct so it can be used like an object
typedef struct person_data person;

#endif // PERSON_H