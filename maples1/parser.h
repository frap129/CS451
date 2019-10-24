/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: October 23rd, 2019
 * Name of this file: parser.h
 * Description of the program: A group of functions that 
                handle parsing information from /proc
 */
#ifndef PARSER_H
#define PARSER_H

#include <linux/limits.h>

// Constant paths
#define PROC	"/proc"
#define STAT	"/stat"
#define STATM	"/statm"
#define STATUS	"/status"

// Constant sizes
#define CMDLINE_MAX		ARG_MAX // Copy from limits.h
#define STATE_LEN_MAX	sizeof(char) // One char (for pointer of char)
#define PID_LEN_MAX		(sizeof(char) * 5) /* Length of /proc/sys/kernel/
                                              pid_max */
#define TIME_LEN_MAX	(sizeof(char) * 100) // Actually pick a value TODO
#define MEM_LEN_MAX		(sizeof(char) * 11) /* Enough to fit double digit 
                                               Gigabytes */
#define PATH_LEN_MAX	((sizeof(char) * 12) + 5) /* Length of /proc + 
                                                     /status and a pid */

// Conversion constants
#define SEC_PER_HOUR	(60 * 60) // 60 sec/min times 60 min/hour
#define SEC_PER_MIN		60 // 60 sec/min

// Struct for holding data on a process
struct pid_data_orig {
	char *cmd;
	char *state;
	char *vmem;
	char *time;
};

// Typedef struct so it can be used like an object
typedef struct pid_data_orig pid_data;

// Functions publically provided by parser.c
pid_data alloc_data();
void free_data();
int parse_state(const char *pid_path, pid_data data);
int parse_vmem(const char *pid_path, pid_data data);
int parse_cmd(const char *pid_path, pid_data data);
int parse_time(const char *pid_path, pid_data data);
#endif // PARSER_H