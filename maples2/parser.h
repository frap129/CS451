/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: parser.h
 * Description of the program: A group of functions that 
                handle parsing information from input files
 */
#ifndef PARSER_H
#define PARSER_H


// Struct for holding data on a process
struct process_orig {
	int proc_num;
	int arrival;
	int burst;
	int priority;
};

// Typedef struct so it can be used like an object
typedef struct process_orig process;

// Functions publically provided by parser.c
process process(); // pseudo constructor
process parse_line(const char *line);
#endif // PARSER_H