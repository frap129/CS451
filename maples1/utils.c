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

options set_options(int argc, char **argv) {
	int getopt_status;
	options opts = {0, 0, 0, 0, 0};

    while ((getopt_status = getopt(argc, argv, "p:cstv")) != -1) {
        switch (getopt_status) {
            case 'p':
                opts.pid = atoi(optarg);
                break;
            case 'c':
                opts.command = 1;
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
                if (optopt == 'p') {
                    //The -p flag was set but no argument was provided
                    printf("You must provide a PID with the -%c option.\n", optopt);
                    exit(EXIT_FAILURE);
                } else {
                    printf("Unknown option `-%c'.\n", optopt);
                    exit(EXIT_FAILURE);
                }

            default:
                exit(EXIT_FAILURE);
        }
    }
    return opts;
}

int is_opts_empty(options opts) {
    if (opts.pid == 0 && opts.command == 0 && opts.state == 0 &&
        opts.time == 0 && opts.vmem == 0)
        return 1;

    return 0;
}