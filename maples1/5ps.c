/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: October 23rd, 2019
 * Name of this file: 5ps.c
 * Description of the program: A simple version of ps that accepts 5 arguments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "parser.h"
#include "utils.h"

/*
    Function Name: print_stats
    Input to the method: Valid options passed to program, path to /proc/<pid>
                         and the name of this program's executable
    Output(Return value): Nothing (Void)
    Brief description of the task: Parse stats based on the enabled options,
                                   format them, and print them.
 */
void print_stats(const options opts, char *pid_path, char *this_prog) {
    // Create and preallocate memory for a data sruct
    pid_data data = alloc_data();

    // Always print PID first
    printf("%d: ", opts.pid);

    /*
        If the '-s' option was passed, parse the state,
        check for errors, and print the state.
    */
    if (opts.state) {
        // If parse_state returns 1, error and exit
        if (parse_state(pid_path, data)) {
            printf("\n%s: error parsing state\n", this_prog);
            exit(EXIT_FAILURE);
        } else
            printf("%c ", data.state[0]);
    }

    /*
        If the '-t' option was passed, parse the time,
        check for errors, and print the time.
    */
    if (opts.time) {
        // If parse_time returns 1, error and exit
        if (parse_time(pid_path, data)) {
            printf("\n%s: error parsing time\n", this_prog);
            exit(EXIT_FAILURE);
        } else
            printf("time=%s ", data.time);
    }

    /*
        If the '-v' option was passed, parse the vmem size,
        check for errors, and print the vmem size.
    */
    if (opts.vmem) {
        // If parse_vmem returns 1, error and exit
        if (parse_vmem(pid_path, data)) {
            printf("\n%s: error parsing size\n", this_prog);
            exit(EXIT_FAILURE);
        } else
            printf("sz=%s ", data.vmem);
    }

    /*
        If the '-v' option was passed, parse the name of the process,
        check for errors, and print the name of the process.
    */
    if (opts.cmd) {
        // If parse_cmd returns 1, error and exit
        if (parse_cmd(pid_path, data)) {
            printf("\n%s: error parsing command\n", this_prog);
            exit(EXIT_FAILURE);
        } else
            printf("[%s]", data.cmd);
    }

    // Finish output with newline
    printf("\n");

    // Cleanup memory
    free_data(data);
    free(pid_path);
}

/*
    Function Name: main
    Input to the method: Number of arguments passed and the list of arguments
    Output(Return value): Error or not error (Int)
    Brief description of the task: Validate options passed to program, and
                                   call print_stats
 */
int main(int argc, char **argv) {
    // Get a struct of the options
    options opts = set_options(argc, argv);

    // Exit if the user didn't pass options
    if (is_opts_empty(opts))
        return 0;

    // If pid was not set, use 1
    if (opts.pid == 0)
        opts.pid = 1;

    // Get path to /proc/<pid>/
    struct stat pid_stat;
    char *pid_path = (char *) malloc(sizeof("/proc/") + PID_LEN_MAX);
    sprintf(pid_path, "%s%s%d", PROC, "/", opts.pid);

    // Verify path exists, error if it doesn't
    if (stat(pid_path, &pid_stat)) {
        printf("%s: No such PID", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Collect and print requested stats
    print_stats(opts, pid_path, argv[0]);

    return 0;
}
