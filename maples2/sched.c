/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: sched.c
 * Description of the program: A simple priority based scheduler with preemption
 */

#include <stdio.h>
#include "parser.h"

char *prog_name;

/*
    Function Name: main
    Input to the method: Number of arguments passed and the list of arguments
    Output(Return value): Error or not error (Int)
    Brief description of the task:
 */
int main(int argc, char **argv) {
    prog_name = malloc(strlen(argv[0]) * sizeof(char));
    strcpy(prog_name, argv[0]);

    return 0;
}
