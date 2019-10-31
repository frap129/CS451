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

process empty_process() {
    process new_process = {0,0,0,0};
    return new_process;
}

process parse_line(const char *line) {
    // Create empty process data
    process parsed = empty_process();

    // Error if we read less than 4 bytes
    if (sscanf(line, "%d %d %d %d\n", &parsed.proc_num, &parsed.arrival,
            &parsed.burst, &parsed.priority) < 4) {
        printf("%s: error parsing input file.\n", prog_name);
        exit(EXIT_FAILURE);
    }

    return parsed;
}

/*process **parse_input(const char *input_path) {
    FILE *input_ptr = fopen(input_path, "r");
    
    fgets
}*/
