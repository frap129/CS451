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

char *prog_name;
person *people;
elevator lift;

int main (int argc, char **argv) {
	prog_name = malloc((strlen(argv[0])) + 1 * sizeof(char));
	strcpy(prog_name, argv[0]);
	options opts = set_options(argc, argv);
	init_elevator(opts);
	people = malloc(sizeof(person) * opts.num_people);
	FILE *input = stdin;
    parse_input(input, opts);
	for (int i = 0; i < opts.num_people; i++) {
		people[i].id = i;
		pthread_create(&people[i].thread, NULL, run_person, &people[i]);		
	}


    pthread_create(&lift.thread, NULL, run_elevator, NULL);
    pthread_join(lift.thread, NULL);

	return 0;
}