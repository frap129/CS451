/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: parser.c
 * Description of the program: A group of functions that 
                handle parsing information from /proc
 */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>

pid_data alloc_data() {
    // Create empty data struct
    pid_data data;

    // Allocated max space needed for each string
    data.cmd = malloc(CMDLINE_MAX);
    data.state = malloc(STATE_LEN_MAX);
    data.vmem = malloc(MEM_LEN_MAX);
    data.time = malloc(TIME_LEN_MAX);

    return data;
}

void free_data(pid_data data) {
    // Free all strings stored in data
    free(data.cmd);
    free(data.state);
    free(data.vmem);
    free(data.time);
}

int parse_state(const char *pid_path, pid_data data) {
    // Create path to /proc/<pid>/stat
    char *file_path = malloc(PATH_LEN_MAX);
    strcpy(file_path, pid_path);
    strcat(file_path, STAT);

    // Get read-only pointer to /proc/<pid>/stat
    FILE *stat_ptr = fopen(file_path, "r");

    // Return 1 if file not found
    if (stat_ptr == NULL)
        return 1;

    // Return 1 if less than 1 byte was read
    if (fscanf(stat_ptr, "%*d %*s %c", data.state) < 1)
        return 1;

    // Free unneeded memory
    fclose(stat_ptr);
    free(file_path);

    return 0;
}

int parse_vmem(const char *pid_path, pid_data data) {
    // Create path to /proc/<pid>/statm
    char *file_path = malloc(PATH_LEN_MAX);
    strcpy(file_path, pid_path);
    strcat(file_path, STATM);

    // Get read-only pointer to /proc/<pid>/statm
    FILE *statm_ptr = fopen(file_path, "r");

    // Return 1 if less than 1 byte was read
    if (statm_ptr == NULL)
        return 1;

    // Return 1 if error scanning file
    if (fscanf(statm_ptr, "%s", data.vmem) < 1)
        return 1;

    // Free unneeded memory
    fclose(statm_ptr);
    free(file_path);

    return 0;
}

int parse_cmd(const char *pid_path, pid_data data) {
    // Create path to /proc/<pid>/status
    char *file_path = malloc(PATH_LEN_MAX);
    strcpy(file_path, pid_path);
    strcat(file_path, STATUS);

    // Get read-only pointer to /proc/<pid>/status
    FILE *status_ptr = fopen(file_path, "r");

    // Return 1 if less than 1 byte was read
    if (status_ptr == NULL)
        return 1;

    // Return 1 if error scanning file
    if (fscanf(status_ptr, "%*s\t%s", data.cmd) < 1)
        return 1;

    // Free unneeded memory
    fclose(status_ptr);
    free(file_path);

    return 0;
}

int parse_time(const char *pid_path, pid_data data){
    // Create path to /proc/<pid>/stat
    char *file_path = malloc(PATH_LEN_MAX);
    strcpy(file_path, pid_path);
    strcat(file_path, STAT);

    // Get read-only pointer to /proc/<pid>/stat
    FILE *stat_ptr = fopen(file_path, "r");

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

    // Return 1 if less than 1 byte was read
    if (fscanf(stat_ptr, "%lu", &utime) < 1 ||
        fscanf(stat_ptr, "%lu", &stime) < 1)
        return 1;

    // Free unneeded memory
    fclose(stat_ptr);
    free(file_path);

    // Get time by adding {s,u}time and dividing by tickrate
    long unsigned int time = (utime + stime) / sysconf(_SC_CLK_TCK);

    // Convert time in seconds to hh:mm:ss
    long unsigned int hours = time / SEC_PER_HOUR;
    long unsigned int minutes = (time % SEC_PER_HOUR) / SEC_PER_MIN;
    long unsigned int seconds = (time % SEC_PER_HOUR) % SEC_PER_MIN;
    sprintf(data.time, "%lu:%lu:%lu", hours, minutes, seconds);
    
    return 0;
}