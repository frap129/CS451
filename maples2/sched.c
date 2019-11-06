/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: November 6th, 2019
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
int running_child = NO_PROCESS;
pid_t children[MAX_JOBS];
process *jobs;

/*
    Function Name: suspend_child
    Input to the method: PID of the child to suspend
    Output(Return value): Nothing (void)
    Brief description of the task: Check if child has been forked, then send 
                                   the SIGTSTP signal.
 */
void suspend_child(pid_t child) {
    // Send SIGTSTP to the child
    if (child != NO_PID)
        kill(child, SIGTSTP);
}

/*
    Function Name: resume_child
    Input to the method: PID of the child to resume
    Output(Return value): Nothing (void)
    Brief description of the task: Check if child has been forked, then send 
                                   the SIGCONT signal.
 */
void resume_child(pid_t child) {
    // Send SIGCONT to the child
    if (child != NO_PID)
        kill(child, SIGCONT);
}

/*
    Function Name: kill_child
    Input to the method: PID of the child to kill
    Output(Return value): Nothing (void)
    Brief description of the task: Check if child has been forked, then send 
                                   the SIGTERM signal.
 */
void kill_child(pid_t child) {
    // Send SIGTERM to the child
    if (child != NO_PID)
	    kill(child, SIGTERM);
}

/*
    Function Name: create_child
    Input to the method: Index of the job to create in jobs[]
    Output(Return value): Nothing (void)
    Brief description of the task: Suspend any running task, then start the
                                   new job.
 */
void create_child(int new_job){
    // Suspend current runnign child before forking
	if (running_child != NO_PROCESS)
		suspend_child(running_child);

    // Fork the new job and save its pid and proc_num
    children[new_job] = fork();
    running_child = new_job;

    // Convert proc_num and priority to strings
    char child_num[ARG_LEN_MAX];
    sprintf(child_num, "%d", jobs[new_job].proc_num);
    char child_prio[ARG_LEN_MAX];
    sprintf(child_prio, "%d", jobs[new_job].priority);

    // Create 2d array of arguments
    char *args[ARG_NUM_MAX] = {"./child", child_num, child_prio, NULL};

    // If we're in the child, run the child executable
    if (children[new_job] == NO_PID) {
        execv("./child", args);
        printf("%s: error executing process %d", prog_name,
                jobs[new_job].proc_num);
        exit(EXIT_FAILURE);
    }
    printf("Scheduler: Starting process %d (PID %d)\n",
            jobs[running_child].proc_num, children[running_child]);
}

/*
    Function Name: check complete
    Input to the method: Index of the job to create in jobs[]
    Output(Return value): Nothing (void)
    Brief description of the task: Check all the burst values, exit if all are
                                   complete.
 */
void check_complete() {
    // Check if all processes are done
    if (running_child == NO_PROCESS) {
        for (int i = 0; i < num_jobs; i++)
            if (jobs[i].burst > 0)
                return; // Return if a job still has a burst

        // Exit if all jobs have completed their burst
        free(prog_name);
        free(jobs);
        exit(EXIT_SUCCESS); 
    }
}

/*
    Function Name: periodic_scheduler
    Input to the method: Number of seconds since starting the timer.
    Output(Return value): Nothing (void)
    Brief description of the task: Check if current job is done, find new jobs
                                   to schedule, compare priorities of all new
                                   and current jobs, and start the job with
                                   the highest priority.
 */
void periodic_scheduler(int time) {
    int time_printed = 0; // Boolean-style int to know if the time was printed

    /*
        Decrement the burst of the currently running process, and check if
        it's done. If it is done, kill the process and reset its PID and
        running_child.
     */
    if (running_child != NO_PROCESS) {
        jobs[running_child].burst--;
        if (jobs[running_child].burst <= 0) {
            printf("Scheduler: Time Now: %u seconds\n", time);
            time_printed = 1;
            printf("Scheduler: Killing process %d (PID %d)\n",
                    jobs[running_child].proc_num, children[running_child]);
            // Kill child if job is dune
            kill_child(children[running_child]);
            children[running_child] = NO_PID;
            running_child = NO_PROCESS;
        }
    }

	/*
        Loop over each process and create an array of processes that have
        arrived but haven't been started.
     */
	int new_children[num_jobs];
	int num_new_jobs = 0;
	for (int i = 0; i < num_jobs; i++) {
		if (jobs[i].arrival <= time && jobs[i].burst > 0 && !children[i]) {
			new_children[num_new_jobs] = i;
			num_new_jobs++;
		}
	}

    // If there arent any new jobs, check if done
    if (num_new_jobs == 0) 
        check_complete();

    /*
        If a process is running, make it the top process. If no processes are
        running, compare the priotities of existing processes.
     */
   	int top_proc = NO_PROCESS;
    if (running_child != NO_PROCESS)
        top_proc = running_child;
    else {
        for (int i = 0; i < num_jobs; i++)
            if (children[i] != 0) {
                // Set top_proc if not already set
                if (top_proc == NO_PROCESS)
                    top_proc = i;

                top_proc = jobs[i].priority < jobs[top_proc].priority ?
                    i : top_proc;
            }
    }

    /*
        If there are new jobs, compare their priorities to existing processes and set the top process accordingly.
     */
    if (num_new_jobs != 0) {
        // Set top_proc if not already set
        if (top_proc == NO_PROCESS)
            top_proc = new_children[0];

        for (int i = 0; i < num_new_jobs; i++) {
            if (jobs[new_children[i]].priority < jobs[top_proc].priority &&
                jobs[new_children[i]].burst > 0)
       	        top_proc = new_children[i];
        }
    }

    /*
        Start by printing the time if needed. If the top process is not
        current running, suspend the current running process and either create
        or resume the top process.
     */
    if (running_child != top_proc && top_proc != NO_PROCESS) {
        if (!time_printed)
            printf("Scheduler: Time Now: %u seconds\n", time);

        if (running_child != NO_PROCESS) {
            printf("Scheduler: Suspending process %d (PID %d)\n",
                    jobs[running_child].proc_num, children[running_child]);
        	suspend_child(children[running_child]);
        }

        if (children[top_proc] == NO_PID) {
            create_child(top_proc);
        } else {
            printf("Scheduler: Resuming process %d (PID %d)\n",
                    jobs[top_proc].proc_num, children[top_proc]);
        	resume_child(children[top_proc]);
            running_child = top_proc;
        }
    }
}

/*
    Function Name: main
    Input to the method: Number of arguments passed and the list of arguments.
    Output(Return value): Error or not error (Int)
    Brief description of the task: First, assign argv[0] to prog_name so that
                                   errors can use the correct executable name.
                                   Next, parse the input file and start the
                                   timer.
 */
int main(__attribute__((unused)) int argc, char **argv) {
    // Make the name of this executable globally accessible
    prog_name = malloc((strlen(argv[0])) * sizeof(char));
    strcpy(prog_name, argv[0]);

    jobs = parse_input(argv[1]);

    start_timer();
    return 0;
}
