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
                if (optopt == 'p') {
                    print_help(argv);
                    exit(EXIT_FAILURE);
                } else {
                    print_help(argv);
                    exit(EXIT_FAILURE);
                }

            default:
                exit(EXIT_FAILURE);
        }
    }
    return opts;
}

int is_opts_empty(options opts) {
    if (opts.pid == 0 && opts.cmd == 0 && opts.state == 0 &&
        opts.time == 0 && opts.vmem == 0)
        return 1;

    return 0;
}

void print_help(char **argv) {
    printf("\n");
    printf("Usage: %s [options]\n\n", argv[0]);
    printf("Options:\n");
    printf("-p <pid> \t Display information about the given process id.\n");
    printf("-s \t\t Display the processes current state.\n");
    printf("-t \t\t Display the time the process has consumed.\n");
    printf("-v \t\t Display the amount of virtual memory used by the process.\n");
    printf("-c \t\t Display the program that spawned the process.\n");
}