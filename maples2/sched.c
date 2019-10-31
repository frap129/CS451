/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: sched.c
 * Description of the program: A simple priority based scheduler with
                               preemption
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "sched.h"
#include "parser.h"
#include "timer.h"

char *prog_name;
pid_t children[10];

void create_child(process *jobs, int num_children){
    children[++num_children] = fork();

    char child_num[3];
    sscanf(child_num, "%d", &num_children);
    char child_prio[3];
    sscanf(child_prio, "%d", &jobs[num_children].priority);

    if (children[num_children] == 0) {
        execlp("./child", "./child", child_num, child_prio, NULL);
    } else {
        waitpid(children[num_children], NULL ,0);
        printf("child finished");
   } 
}

void suspend_child(pid_t child) {
	kill(child, SIGTSTP);
}

void resume_child(pid_t child) {
	kill(child, SIGCONT);
}

void kill_child(pid_t child) {
	kill(child, SIGTERM);
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

    //process *jobs;
    //jobs = parse_input(argv[1]);

    start_timer();
    return 0;
}
