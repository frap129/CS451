/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 6th, 2019
 * Name of this file: main.c
 * Description of the program: Initializes and starts threads
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"
#include "utils.h"
#include "elevator.h"

/*
    Function Name: main
    Input to the method: number of args (int), list of args (char**)
    Output(Return value): Exit code (int)
    Brief description of the task: Initialize and start threads
 */
int main(int argc, char **argv) {
    // Parse input options
    options *opts = malloc(sizeof(options)); 
    opts[0] = set_options(argc, argv);

    // Exit if no options passed
    if (is_opts_empty(opts)) {
        printf("error: no options pased\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the elevator thread
    pthread_t ethread;
    init_elevator(opts);
    pthread_create(&ethread, NULL, run_elevator, opts);

    // Initialize the people threads
    person *people = parse_input(opts);
    for (int i = 0; i < opts->num_people; i++) {
        people[i].id = i;
        pthread_create(&people[i].thread, NULL, run_person, &people[i]);    
    }

    // Nothing else to do, join elevator
    pthread_join(ethread, NULL);

    // Cleanup when the thread exits
    free(people);
    free(opts);

    return 0;
}