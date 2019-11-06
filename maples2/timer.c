/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: November 6th, 2019
 * Name of this file: timer.c
 * Description of the program: Functions related to timing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "timer.h"
#include "sched.h"

unsigned int latest_time;

/*
    Function Name: alarm_handler
    Input to the method: Numeric value of the recieved signal.
    Output(Return value): Nothing (void)
    Brief description of the task: Increment the time, and run the periodic
                                   scheduler.
 */
void alarm_handler(__attribute__((unused)) int sigval) {
    // Keep track of time
    latest_time++;

    // Execute the scheduler
    periodic_scheduler(latest_time);
}

/*
    Function Name: start_timer
    Input to the method: Nothing
    Output(Return value): Nothing (void)
    Brief description of the task: Create a signal handler, create a timer,
                                   and start the timer.
 */
void start_timer() {
    // Create and set sigaction
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = alarm_handler;
    sigaction(SIGALRM, &sa, NULL);

    // Create interval timer
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;   
    timer.it_interval = timer.it_value;

    // Start itimer, error and exit if we can't
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        printf("%s: error caused by setitimer.\n", prog_name);
        exit(EXIT_FAILURE);
    }

    while (1) {
        //wait for timer
    }
}
