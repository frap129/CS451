/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 5th, 2019
 * Name of this file: main.c
 * Description of the program: Initializes and starts threads
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "person.h"
#include "utils.h"
#include "elevator.h"

char *prog_name;

/*
    Function Name: main
    Input to the method: number of args (int), list of args (char**)
    Output(Return value): Exit code (int)
    Brief description of the task: Initialize and start threads
 */
int main(int argc, char **argv) {
    prog_name = malloc((strlen(argv[0])) + 1 * sizeof(char));
    strcpy(prog_name, argv[0]);

    options *opts = malloc(sizeof(options)); 
    opts[0] = set_options(argc, argv);
    elevator lift;
    init_elevator(opts);
    pthread_create(&lift.thread, NULL, run_elevator, opts);
    person *people = parse_input(opts);
    for (int i = 0; i < opts->num_people; i++) {
        people[i].id = i;
        pthread_create(&people[i].thread, NULL, run_person, &people[i]);    
    }

    pthread_join(lift.thread, NULL);
    free(people);
    free(prog_name);

    return 0;
}