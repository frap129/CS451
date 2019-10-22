/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: 5ps.c
 * Description of the program: A simple version of ps that accepts 5 arguments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "parser.h"
#include "utils.h"

void print_stats(options opts, char *pid_path, char **argv) {
    pid_data data = alloc_data();

    printf("%d: ", opts.pid);

    if (opts.state) {
        if (parse_state(pid_path, data)) {
            printf("\n%s: error parsing state\n", argv[0]);
            exit(EXIT_FAILURE);
        } else
            printf("%c ", data.state[0]);
    }
    if (opts.time) {
        if (parse_time(pid_path, data)) {
            printf("\n%s: error parsing time\n", argv[0]);
            exit(EXIT_FAILURE);
        } else
            printf("time=%s ", data.time);
    }
    if (opts.vmem) {
        if (parse_vmem(pid_path, data)) {
            printf("\n%s: error parsing size\n", argv[0]);
            exit(EXIT_FAILURE);
        } else
            printf("sz=%s ", data.vmem);
    }
    if (opts.cmd) {
        if (parse_cmd(pid_path, data)) {
            printf("\n%s: error parsing command\n", argv[0]);
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

int main(int argc, char *argv[]) {
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
    char pid_str[PID_LEN_MAX];
    sprintf(pid_str, "%d", opts.pid);
    char *pid_path = (char *) malloc(100);
    sprintf(pid_path, "%s%s%s", PROC, "/", pid_str);

    // Verify path exists
    if (stat(pid_path, &pid_stat)) {
        printf("%s: No such PID", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Collect and print requested stats
    print_stats(opts, pid_path, argv);

    return 0;
}
