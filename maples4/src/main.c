/*
 * Author: Joseph Maples
 * Assignment Number: 4
 * Date of Submission: TBD
 * Name of this file: main.c
 * Description of the program:
 */
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "main.h"

/*
    Function Name: parse_fit
    Input to the method: Number of cmdline arguments passed and the list of
                         arguments
    Output(Return value): An instance of options containing int/bools of the
                          valid arguments passed
    Brief description of the task: Parse argv for valid arguments and set them
                                   in options, error on unknown options.
 */
int parse_fit(const int argc, char **argv) {
    int getopt_ret; // Create int to store getopts return val
    int fit = BEST_FIT;

    // Loop over every passed option with getopt
    while ((getopt_ret = getopt(argc, argv, "fbw")) != -1) {
        // Chceck which opton was passed and handle accordingly
        switch (getopt_ret) {
            case 'f':
                fit = FIRST_FIT;
                break;
            case 'b':
                fit = BEST_FIT;
                break;
            case 'w':
                fit = WORST_FIT;
                break;
            case '?':
            default:
                exit(EXIT_FAILURE);
        }
    }

    // Return struct of selected options.
    return fit;
}

/*
    Function Name: main
    Input to the method: number of args (int), list of args (char**)
    Output(Return value): Exit code (int)
    Brief description of the task:
 */
int main(int argc, char **argv) {
    arguments args;
    args.fit = parse_fit(argc, argv);
    printf("%d", args.fit);
    return 0;
}