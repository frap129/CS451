/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: main.c
 * Description of the program: An elevator system that syncronizes elevator
                               and person movement.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "utils.h"

#define DEBUG 1

char *prog_name;
person *people;
elevator lift;

int main (int argc, char **argv) {
	strcpy(prog_name, argv[0]);
	options opts = set_options(argc, argv);
	init_elevator(opts);
	people = malloc(sizeof(pthread_t) * opts.num_people);
#if DEBUG == 1
	FILE *input = fopen("input.txt", "r");
#else
	FILE *input = STDIN_FILENO;
#endif
    parse_input(input, opts);
	for (int i = 0; i < opts.num_people; i++) {
		people[i].person_id = i;
		pthread_create(&people[i].thread, NULL, run_person, &people[i]);		
	}



    pthread_create(&lift.thread, NULL, run_elevator, NULL);
    pthread_join(lift.thread, NULL);

	return 0;
}