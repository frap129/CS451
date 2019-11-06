/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: November 6th, 2019
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

/*
    Function Name: parse_line
    Input to the method: One line from the input file.
    Output(Return value): A process struct containing data from the input line.
    Brief description of the task: Parse the line and store its data in a
                                   process struct.
 */
process parse_line(const char *line) {
    // Create empty process data
    process parsed = {0,0,0,0};

    // Parse line, error if we read less than 4 bytes
    if (sscanf(line, "%d %d %d %d\n", &parsed.proc_num, &parsed.arrival,
            &parsed.burst, &parsed.priority) < 4) {
        printf("%s: error parsing input file.\n", prog_name);
        exit(EXIT_FAILURE);
    }

    return parsed;
}

/*
    Function Name: parse_input
    Input to the method: String containing the path to the input file.
    Output(Return value): A pointer to an array of process structs.
    Brief description of the task: parse the input file line by line, storing
                                   all of the data in an array of process.
 */
process *parse_input(const char *input_path) {
    // Get pointer to input file
    FILE *input_ptr = fopen(input_path, "r");
    
    // Check if pointer was acquired, error if not.
    if (input_ptr == NULL) {
        printf("%s: error opening input file.\n", prog_name);
        exit(EXIT_FAILURE);
    } 

    // Create storage for input values
    process *lines = malloc(MAX_JOBS * PROCESS_SIZE);
    char *line = malloc(MAX_LINE_LEN * sizeof(char));

    /*
        Loop over the lines of input and parse each one.
     */
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


