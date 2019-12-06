/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: December 6th, 2019
 * Name of this file: utils.c
 * Description of the program: Misc utility functions
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "queue.h"
#include "utils.h"

/*
    Function Name: set_options
    Input to the method: Number of cmdline arguments passed and the list of
                         arguments
    Output(Return value): An instance of options containing int/bools of the
                          valid arguments passed
    Brief description of the task: Parse argv for valid arguments and set them
                                   in options, error on unknown options.
 */
options set_options(const int argc, char **argv) {
	int getopt_ret; // Create int to store getopts return val
	options opts = {0, 0, 0}; // Create empty opts struct

    // Loop over every passed option with getopt
    while ((getopt_ret = getopt(argc, argv, "f:p:w:")) != -1) {
        // Chceck which opton was passed and handle accordingly
        switch (getopt_ret) {
            case 'f':
                opts.num_floors = atoi(optarg);
                break;
            case 'p':
                opts.num_people = atoi(optarg);
                break;
            case 'w':
                opts.max_wander_time = atoi(optarg);
                break;
            case '?':
            default:
                exit(EXIT_FAILURE);
        }
    }

    // Return struct of selected options.
    return opts;
}

/*
    Function Name: parse_input
    Input to the method: Pointer to options struct
    Output(Return value): An instance of options containing int/bools of the
                          valid arguments passed
    Brief description of the task: Parse contents of stdin after the options
 */
person *parse_input(options *opts) {
    // Initialize a pointer array of people
    person *people = malloc(sizeof(person)*opts->num_people);

    // Loop over the lines of input and parse each one.
    for (int i = 0; i < opts->num_people; i++) {
        // Grab a whole line of input
        char *line = malloc(MAX_LINE_LEN * sizeof(char));
        fgets(line, MAX_LINE_LEN, stdin);

        // Grab the number of pairs and track the offset
        int buf_len,offset = 0;
        sscanf(line, "%d%n", &people[i].num_pairs, &buf_len);
        offset += buf_len;

        // Initialize our input storage queue and arrays for printing
        people[i].schedule = init_queue();
        int *floors = malloc(sizeof(int)*people[i].num_pairs);
        int *times = malloc(sizeof(int)*people[i].num_pairs);

        // Read in all of pairs on this line
        for (int j = 0; j < people[i].num_pairs; j++) {
            sscanf(line+offset, " %d %d%n", &floors[j], &times[j], &buf_len);
            offset += buf_len;
            if (times[j] > opts->max_wander_time)
                times[j] = opts->max_wander_time;
            enqueue(people[i].schedule, floors[j], times[j]);
        }

        // Print the floors to visit
        printf("Person %d: Floors to visit: ", i);
        for (int j = 0; j < people[i].num_pairs; j++)
            printf("%d, ", floors[j]);

        // Print wander times for each floor
        printf("\nPerson %d: Time on each floor: ", i);
        for (int j = 0; j < people[i].num_pairs; j++)
            printf("%d, ", times[j]);
        printf("\n");

        //cleanup
        free(line);
        free(floors);
        free(times);
    }

    // Space out from the rest of the output
    printf("\n");
    return people;
}


/*
    Function Name: is_opts_empty
    Input to the method: An instance of the options struct
    Output(Return value): Empty or not (Int: 1 true, 0 false)
    Brief description of the task: Check if all ints in options are zero
 */
int is_opts_empty(const options *opts) {
    // Check all values stored in opts, return 1 if all 0
    return (opts->num_floors == 0 && opts->num_people == 0 &&
            opts->max_wander_time == 0);
}