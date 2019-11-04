/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: parser.c
 * Description of the program: A group of functions that
                handle parsing information from input files
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sched.h"
#include "parser.h"

int num_jobs;

process parse_line(const char *line) {
    // Create empty process data
    process parsed = {0,0,0,0};

    // Error if we read less than 4 bytes
    if (sscanf(line, "%d %d %d %d\n", &parsed.proc_num, &parsed.arrival,
            &parsed.burst, &parsed.priority) < 4) {
        printf("%s: error parsing input file.\n", prog_name);
        exit(EXIT_FAILURE);
    }

    return parsed;
}

process *parse_input(const char *input_path) {
    // Get pointer to input file
    FILE *input_ptr = fopen(input_path, "r");
    
    // Check if pointer was acquired
    if (input_ptr == NULL) {
        printf("%s: error opening input file.\n", prog_name);
        exit(EXIT_FAILURE);
    } 

    // Create storage for input values
    process *lines = malloc(MAX_JOBS * PROCESS_SIZE);
    char *line = malloc(MAX_LINE_LEN * sizeof(char));

    // Get all lines of input
    int num_lines = 0;
    while (fgets(line, MAX_LINE_LEN, input_ptr)) {
        // Parse line
        lines[num_lines] = parse_line(line);
        num_lines++;

        // Erase line
        strcpy(line, "\0");
    }
    
    // Close pointer
    fclose(input_ptr);
    free(line);

    // Make the total number of jobs globally available
    num_jobs = num_lines;

    return lines;
}


