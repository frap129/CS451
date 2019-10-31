/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
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


void alarm_handler(int sigval) {
	printf("BEEP BEEP BEEP WAKE UP\n");
}

int start_timer() {

	// Create and set sigaction
    struct sigaction sa;
    memset (&sa, 0, sizeof(sa));
    sa.sa_handler = alarm_handler;
    sigaction (SIGALRM, &sa, NULL);

    // Create interval timer
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;   
    timer.it_interval = timer.it_value;

    // Start itimer, error and exit if we can't
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        printf("error caused by setitimer");
        exit(1);
  }

  while (1) {
  	//wait for timer
  }
}
