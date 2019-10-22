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

#include <linux/limits.h>
#include <zconf.h>

// Constant paths
#define PROC	"/proc"
#define STAT	"/stat"
#define STATM	"/statm"
#define STATUS	"/status"
#define CMDLINE	"/cmdline"

// Constant sizes
#define CMDLINE_MAX		ARG_MAX // Copy from limits.h
#define PID_LEN_MAX		(sizeof(char) * 5) // Length of /proc/sys/kernel/pid_max
#define TIME_LEN_MAX	(sizeof(char) * 100) // Actually pick a value TODO
#define MEM_LEN_MAX		(sizeof(char) * 11) // Enough to fit double digit Gigabytes

// Conversion constants
#define SEC_PER_HOUR	(60 * 60) // 60 sec/min times 60 min/hour
#define SEC_PER_MIN		60 // 60 sec/min

struct pid_data_orig {
	FILE *stat;
	FILE *statm;
	FILE *status;
	char *cmd;
	char *state;
	char *vmem;
	char *time;
};
typedef struct pid_data_orig pid_data;

pid_data alloc_data();
void free_data();
int parse_state(const char *pid_path, pid_data data);
int parse_vmem(const char *pid_path, pid_data data);
int parse_cmd(const char *pid_path, pid_data data);
int parse_time(const char *pid_path, pid_data data);
#endif // PARSER_H