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
    // Send SIGTSTP to the child
	kill(child, SIGTSTP);
}

void resume_child(pid_t child) {
    // Send SIGCONT to the child
	kill(child, SIGCONT);
}

void kill_child(pid_t child) {
    // Send SIGTERM to the child
	kill(child, SIGTERM);
}

void create_child(process new_job){
    // Suspend current runnign child before forking
	if (running_child != NOTHING_RUNNING)
		suspend_child(running_child);

    // Fork the new job and save its pid and proc_num
    children[new_job.proc_num] = fork();
    running_child = new_job.proc_num;

    // Convert proc_num and priority to strings
    char child_num[ARG_LEN_MAX];
    sprintf(child_num, "%d", new_job.proc_num);
    char child_prio[ARG_LEN_MAX];
    sprintf(child_prio, "%d", new_job.priority);

    // Create 2d array of arguments
    char *args[ARG_NUM_MAX] = {"./child", child_num, child_prio, NULL};

    // If we're in the child, run the child executable
    if (children[new_job.proc_num] == 0)
        execv("./child", args);

    // Let the parent wait on the child
    waitpid(children[new_job.proc_num], NULL, WNOHANG);
}

void check_complete() {
    // Check if all processes are done
    if (running_child == NOTHING_RUNNING) {
        for (int i = 0; i < num_jobs; i++)
            if (jobs[i].burst != 0)
                return; // Return if a job still has a burst
        // Exit if all jobs have completed their burst
        exit(EXIT_SUCCESS); 
    }
}

void check_current_job_done() {
    // Start by seeing if current job is done
    if (running_child != NOTHING_RUNNING) {
        jobs[running_child].burst--;
        if (jobs[running_child].burst == 0) {
            // Kill child if job is dune
            kill_child(children[running_child]);
            children[running_child] = 0;
            running_child = NOTHING_RUNNING;
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
    if (running_child != NOTHING_RUNNING)
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
        if (running_child != NOTHING_RUNNING)
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
    running_child = NOTHING_RUNNING;
    start_timer();
    return 0;
}
