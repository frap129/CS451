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
int running_child;
pid_t children[10];
process *jobs;

void suspend_child(pid_t child) {
	kill(child, SIGTSTP);
}

void resume_child(pid_t child) {
	kill(child, SIGCONT);
}

void kill_child(pid_t child) {
	kill(child, SIGTERM);
}

void create_child(process new_job){
	if (running_child != 0)
		suspend_child(running_child);

    children[new_job.proc_num] = fork();
    running_child = new_job.proc_num;

    char child_num[ARG_LEN_MAX];
    sprintf(child_num, "%d", new_job.proc_num);
    char child_prio[ARG_LEN_MAX];
    sprintf(child_prio, "%d", new_job.priority);

    char *args[ARG_NUM_MAX] = {"./child", child_num, child_prio, NULL};

    if (children[new_job.proc_num] == 0)
        execv("./child", args);

    waitpid(children[new_job.proc_num], NULL, WNOHANG);
    free(args);
}

void check_complete() {
    // Check if all processes are done
    if (running_child == -1) {
        for (int i = 0; i < num_jobs; i++)
            if (jobs[i].burst != 0)
                return;
        exit(EXIT_SUCCESS);
    }
}

void check_current_job_done() {
    // Start by seeing if current job is done
    if (running_child != -1) {
        jobs[running_child].burst--;
        if (jobs[running_child].burst == 0) {
            kill_child(children[running_child]);
            children[running_child] = 0;
            running_child = -1;
        }
    }
}

int periodic_scheduler(int time) {
    check_current_job_done();

	// Find new jobs to launch
	int new_children[num_jobs];
	int num_new_jobs = 0;
	for (int i = 0; i < num_jobs; i++) {
		if (jobs[i].arrival == time) {
			new_children[num_new_jobs] = jobs[i].proc_num;
			num_new_jobs++;
		}
	}

    // IF there arent any new jobs, check if done
    if (num_new_jobs == 0) 
        check_complete();

    // Compare priorities of existing jobs
   	process top_proc;
    if (running_child != -1)
        top_proc = jobs[running_child];
    else {
        top_proc.priority = 100;
        for (int i = 0; i < num_jobs; i++)
            if (children[i] != 0)
                top_proc = jobs[i].priority < top_proc.priority ?
                    jobs[i] : top_proc;
    }

    // Compare priorities of new jobs
    if (num_new_jobs != 0)
        for (int i = 0; i < num_new_jobs; i++) {
            if (jobs[new_children[i]].priority < top_proc.priority &&
                jobs[new_children[i]].burst != 0)
       	        top_proc = jobs[new_children[i]];
        }

    // Handle state of children
    if (running_child != top_proc.proc_num) {
        if (running_child != -1)
        	suspend_child(children[running_child]);

        if (children[top_proc.proc_num] == 0)
            create_child(top_proc);
        else {
        	resume_child(children[top_proc.proc_num]);
            running_child = top_proc.proc_num;
        }
    }

    return 0;
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

    jobs = parse_input(argv[1]);
    running_child = -1;
    start_timer();
    return 0;
}
