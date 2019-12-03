/*
 * Author: Joseph Maples
 * Assignment Number: 3
 * Date of Submission: TBD
 * Name of this file: utils.c
 * Description of the program: Misc utility functions
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "main.h"
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
                // Print help for unknown options
                print_help(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Return struct of selected options.
    return opts;
}

int parse_input(FILE *input_ptr, options opts) {
    // Check if pointer was acquired, error if not.
    if (input_ptr == NULL) {
        printf("%s: error opening input file.\n", prog_name);
        exit(EXIT_FAILURE);
    } 

    char *line = malloc(100 * sizeof(char));

    /*
        Loop over the lines of input and parse each one.
     */
    int num_lines = 0;
    while (fgets(line, 100, input_ptr)) {
        fscanf(input_ptr, "%d", &people[num_lines].num_pairs);
        people[num_lines].schedule = init_queue();
        for (int i = 0; i < people[num_lines].num_pairs; i++) {
            int floor, time;
            fscanf(input_ptr, "%d %d", &floor, &time);
            if (time > opts.max_wander_time) time = opts.max_wander_time;
            enqueue(people[num_lines].schedule, floor, time);
        }
    }

    return 0;   
}


/*
    Function Name: is_opts_empty
    Input to the method: An instance of the options struct
    Output(Return value): Empty or not (Int: 1 true, 0 false)
    Brief description of the task: Check if all ints in options are zero
 */
int is_opts_empty(const options opts) {
    // Check all values stored in opts, return 1 if all 0
    return (opts.num_floors == 0 && opts.num_people == 0 &&
            opts.max_wander_time == 0);
}

/*
    Function Name: print_help
    Input to the method: The name of this executable (argv[0])
    Output(Return value): Nothing (Void)
    Brief description of the task: Print program usage and help dialog
 */
void print_help(char *this_prog) {
    // Print correct usage of program and its options
    printf("\n");
    printf("Usage: %s [options] < /path/to/input/file\n\n", this_prog);
    printf("Options:\n");
    printf("-p <num>\tSet number of people using the elevator.\n");
    printf("-f <num>\tSet number of floors in the building.\n");
    printf("-w <num>\tSet the max time any person can wander.\n");
}