/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: parser.h
 * Description of the program: A group of functions that 
                handle parsing information from /proc
 */
#ifndef PARSER_H
#define PARSER_H

#define PROC          "/proc"
#define STAT          "/stat"
#define STATM         "/statm"
#define CMDLINE       "/cmdline"

int parse_state(char* pid_path, char* state);
int parse_memory(char* pid_path, char* memory);

#endif // PARSER_H