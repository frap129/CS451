/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: OTBD
 * Name of this file: utils.h
 * Description of the program: Misc utility functions
 */
#ifndef UTILS_H
#define UTILS_H

// Struct of options used by the program
struct program_options {
	int num_floors;
	int max_wander_time;
	int num_people;
};

// Typedef struct so it can be used like an object
typedef struct program_options options;


// Functions publically provided by utils.c
options set_options(const int argc, char **argv);
int is_opts_empty(const options opts);
void print_help(char *this_prog);

#endif // UTILS_H