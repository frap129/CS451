/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: utils.c
 * Description of the program: Misc utility functions
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

options set_options(const int argc, const char **argv) {
	int getopt_ret; // Create int to store getopts return val
	options opts = {0, 0, 0, 0, 0}; // Create empty opts struct

    // Loop over every passed option with getopt
    while ((getopt_ret = getopt(argc, argv, "p:cstv")) != -1) {
        // Chceck which opton was passed and handle accordingly
        switch (getopt_ret) {
            case 'p':
                opts.pid = atoi(optarg);
                break;
            case 'c':
                opts.cmd = 1;
                break;
            case 's':
                opts.state = 1;
                break;
            case 't':
                opts.time = 1;
                break;
            case 'v':
                opts.vmem = 1;
                break;
            case '?':
            default:
                // Print help for unknown options
                print_help(argv);
                exit(EXIT_FAILURE);
        }
    }

    // Return struct of selected options.
    return opts;
}

int is_opts_empty(const options opts) {
    // Check all values stored in opts, return 1 if all 0
    if (opts.pid == 0 && opts.cmd == 0 && opts.state == 0 &&
        opts.time == 0 && opts.vmem == 0)
        return 1;

    // Return 0 if options are not all 0
    return 0;
}

void print_help(const char **argv) {
    // Print correct usage of program and its options
    printf("\n");
    printf("Usage: %s [options]\n\n", argv[0]);
    printf("Options:\n");
    printf("-p <pid> \t Display information about the given process id.\n");
    printf("-s \t\t Display the processes current state.\n");
    printf("-t \t\t Display the time the process has consumed.\n");
    printf("-v \t\t Display the amount of virtual memory used by the process.\n");
    printf("-c \t\t Display the program that spawned the process.\n");
}