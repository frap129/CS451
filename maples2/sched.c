/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: sched.c
 * Description of the program: A simple priority based scheduler with preemption
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sched.h"
#include "parser.h"

char *prog_name;
pid_t children[10];

void create_child(int num_children){

    children[++num_children] = fork();

    char child_num[3];
    sscanf(child_num, "%d", &num_children);

    if (children[num_children] == 0) {
        execlp("./child", "./child", child_num, NULL);
    } else {
        waitpid(children[num_children], NULL ,0);
        printf("child finished");
   } 
}


/*
    Function Name: main
    Input to the method: Number of arguments passed and the list of arguments
    Output(Return value): Error or not error (Int)
    Brief description of the task:
 */

int main(__attribute__((unused)) int argc, char **argv) {
    prog_name = malloc(strlen(argv[0]) * sizeof(char));
    strcpy(prog_name, argv[0]);

    process *jobs;
    jobs = parse_input(argv[1]);

    return 0;
}
