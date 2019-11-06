/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: November 6th, 2019
 * Name of this file: parser.h
 * Description of the program: A group of functions that 
                handle parsing information from input files.
 */
#ifndef PARSER_H
#define PARSER_H

// Constants
#define MAX_LINE_LEN	50 // Just an estimate, not sure of actual
#define PROCESS_SIZE	4 * sizeof(int) // size of the process struct

// External variables
extern int num_jobs;

// Struct for holding data on a process
struct process_orig {
	int proc_num;
	int arrival;
	int burst;
	int priority;
};

// Typedef struct so it can be used like an object
typedef struct process_orig process;

// Functions provided by parser.c
process *parse_input(const char *input_path);
#endif // PARSER_H