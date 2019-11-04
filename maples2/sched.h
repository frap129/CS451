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
extern char *prog_name;

// Constants
#define PID_LEN_MAX		(sizeof(char) * 5) /* Length of /proc/sys/kernel/
                                              pid_max */
#define ARG_LEN_MAX		7
#define ARG_NUM_MAX		4
#define NOTHING_RUNNING	-1

int periodic_scheduler(int time);
#endif // SCHED_H