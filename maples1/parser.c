/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: parser.c
 * Description of the program: A group of functions that 
                handle parsing information from /proc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


pid_data alloc_data() {
    pid_data data;
    data.cmd = malloc(CMDLINE_MAX);
    data.state = malloc(sizeof(char));
    data.vmem = malloc(MEM_LEN_MAX);
    data.time = malloc(TIME_LEN_MAX);

    return data;
}

void free_data(pid_data data) {
    free(data.cmd);
    free(data.state);
    free(data.vmem);
    free(data.time);
}

int parse_state(char *pid_path, pid_data data) {
    // Get read-only pointer to /proc/<pid>/stat
    FILE *stat_ptr = fopen(strcat(pid_path, STAT), "r");

    // Return 1 if error scanning file
    if (!fscanf(stat_ptr, "%*d %*s %c", data.state))
        return 1;

    fclose(stat_ptr);
    return 0;
}

int parse_vmem(char *pid_path, pid_data data) {
	// Get read-only pointer to /proc/<pid>/statm
    FILE *statm_ptr = fopen(strcat(pid_path, STATM), "r");

    // Return 1 if error scanning file
    if (!fscanf(statm_ptr, "%s", data.vmem))
        return 1;

    fclose(statm_ptr);
    return 0;
}

int parse_cmd(char *pid_path, pid_data data) {
    FILE *status_ptr = fopen(strcat(pid_path, STATUS), "r");

    // Return 1 if error scanning file
    if (!fscanf(status_ptr, "%*s\t%s", data.cmd))
        return 1;

    fclose(status_ptr);
    return 0;
}

int parse_time(char *pid_path, pid_data data){
    // Get read-only pointer to /proc/<pid>/stat
    FILE *stat_ptr = fopen(strcat(pid_path, STAT), "r");

    // Return 1 if file not found
    if (stat_ptr == NULL)
        return 1;
    
    // Skip unused values
    for (int i = 0; i < 13; i++) {
        fscanf(stat_ptr, "%*s");
    }

    // Read stime and utime, then close
    long unsigned int utime = 0;
    long unsigned int stime = 0;
    fscanf(stat_ptr, "%lu", &utime);
    fscanf(stat_ptr, "%lu", &stime);
    fclose(stat_ptr);
    
    // Get time by adding {s,u}time and dividing by tickrate
    long unsigned int time = (utime + stime) / sysconf(_SC_CLK_TCK);

    // Convert time in seconds to hh:mm:ss
    long unsigned int hours = time / SEC_PER_HOUR;
    long unsigned int minutes = (time % SEC_PER_HOUR) / SEC_PER_MIN;
    long unsigned int seconds = (time % SEC_PER_HOUR) % SEC_PER_MIN;
    sprintf(data.time, "%lu:%lu:%lu", hours, minutes, seconds);
    
    return 0;
}