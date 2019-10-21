/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: utils.h
 * Description of the program: Misc utility functions
 */
#ifndef UTILS_H
#define UTILS_H

struct program_options {
	int pid;
	int state;
	int time;
	int vmem;
	int cmd;
};

typedef struct program_options options;

options set_options(int argc, char **argv);
int is_opts_empty(options opts);
void print_help(char **argv);

#endif // UTILS_H