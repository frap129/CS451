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

int parse_state(char* pid_path, char* state) {
	// Get read-only pointer to /proc/<pid>/stat
    FILE* stat_ptr = fopen(strcat(pid_path, STAT), "r");

    // Read file, return 1 if error
    if (!fscanf(stat_ptr, "%s", state)) {
        fclose(stat_ptr);
        return 1;
    }

  	fclose(stat_ptr);
    return 0;
}

int parse_memory(char* pid_path, char* memory) {
	// Get read-only pointer to /proc/<pid>/statm
    FILE* statm_ptr = fopen(strcat(pid_path, STATM), "r");

    // Read file, return 1 if error
    if (!fscanf(statm_ptr, "%s", memory)) {
        fclose(statm_ptr);
        return 1;
    }

    fclose(statm_ptr);
    return 0;
}

int parse_command(char* pid_path, char* command) {
	// Get read-only pointer to /proc/<pid>/cmdline
    FILE* cmdline_ptr = fopen(strcat(pid_path, CMDLINE), "r");

    // Read file, return 1 if error
    if (!fscanf(cmdline_ptr, "%s", command)) {
        fclose(cmdline_ptr);
        return 1;
    }

    fclose(cmdline_ptr);
    return 0;
}