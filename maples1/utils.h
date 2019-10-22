/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: utils.h
 * Description of the program: Misc utility functions
 */
#ifndef UTILS_H
#define UTILS_H

// Struct of options used by the program
struct program_options {
	int pid;
	int state;
	int time;
	int vmem;
	int cmd;
};

// Typedef struct so it can be used like an object
typedef struct program_options options;

// Functions publically provided by utils.c
options set_options(int argc, char **argv);
int is_opts_empty(options opts);
void print_help(char **argv);

#endif // UTILS_H