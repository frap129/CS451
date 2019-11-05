/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: sched.h
 * Description of the program: Header for sched.c
 */
#ifndef SCHED_H
#define SCHED_H

// External variables
extern char *prog_name; // For error printing

// Constants
#define ARG_LEN_MAX		7 // Length of "./child"
#define ARG_NUM_MAX		4 // 4 arguments get passed to the child
#define NO_PROCESS		-1 // Just a sentinel value
#define NO_PID			0 // Another sentinel value
#define MAX_PRIORITY	100 // No priority should be greater than 100
#define MAX_JOBS		10 // Only 10 jobs can be parsed at once
#define PID_LEN_MAX		(sizeof(char) * 5) /* Length of /proc/sys/kernel/
                                              pid_max */
// Functions provided by sched.c
int periodic_scheduler(int time);
#endif // SCHED_H