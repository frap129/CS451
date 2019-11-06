/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: November 6th, 2019
 * Name of this file: child.c
 * Description of the program: Prime checking algorithm for child processes.
 */

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BASE_PRIME	1234000031
#define LLU		long long unsigned

LLU int highest_prime;
int child_num;
int priority;
pid_t pid;

/*
    Function Name: sig_handler
    Input to the method: Numeric value of the recieved signal.
    Output(Return value): Nothing (void)
    Brief description of the task: Handle each signal with the correct strings
                                   and action (pause or exit).
 */
void sig_handler(int sigval) {
    // Handle SIGTSTP, SIGCONT, and SIGTERM
    switch(sigval) {
        case SIGTSTP:
            printf("Process %d: My priority is %d, my PID is %d: I am about to"
                    " be suspended... Highest prime number I found is %llu.\n",
                    child_num, priority, pid, highest_prime);
            pause();
            break;
        case SIGCONT:
            printf("Process %d: My priority is %d, my PID is %d: I just got"
                    " resumed. Highest prime number I found is %llu.\n",
                    child_num, priority, pid, highest_prime);
            break;
        case SIGTERM:
            printf("Process %d: My priority is %d, my PID is %d: I completed"
                    " my task and will exit. Highest prime number I found is "
                    "%llu.\n", child_num, priority, pid, highest_prime);
            exit(EXIT_SUCCESS);
            break;
        default:
            //Ignore other signals
            break;
    } 
}

/*
    Function Name: check_prime
    Input to the method: An interger to check for primality.
    Output(Return value): Prime or not prime (Int)
    Brief description of the task: Check if a number is prime by dividing it
                                   by every number from 3 to sqrt(input) and
                                   checking the remainder.
 */
int check_prime(LLU int check) {
    // Determine our range of 2 to sqrt(n)
    LLU int range = sqrt(check); // truncated on purpose
    LLU int i = 3; 

    // Check the remainder of 2 to sqrt(n)
    int prime = 1;
    while (prime == 1 && i <= range) { 
        if (check % i == 0) 
            prime = 0;
        i++;
    } 

    return (prime);
}

/*
    Function Name: main
    Input to the method: Number of arguments passed and the list of arguments.
    Output(Return value): Error or not error (Int)
    Brief description of the task: Parse input, setup a signal handler, and
                                   begin checking primes.
 */
int main(__attribute__((unused)) int argc, char **argv) {
    // Set global PID value
    child_num = atoi(argv[1]);
    priority = atoi(argv[2]);
    pid = getpid();

    // Print that we're getting started
    printf("Process %d: My priority is %d, my PID is %d: I just got started. "
            "I am starting with the number %u to find the next prime number.\n"
            , child_num, priority, pid, BASE_PRIME);

    // Create and set sigaction
    struct sigaction sa;
    memset (&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sigaction (SIGTSTP, &sa, NULL);
    sigaction (SIGCONT, &sa, NULL);
    sigaction (SIGTERM, &sa, NULL);

    // Check all numbers from BASE_PRIME to BASE_PRIME+2*MAX_RANGE
    int num_found = 0;
    LLU int num_to_check = BASE_PRIME; 
    while (1) {
        // If number is prime, increment num_found and save it
        if (check_prime(num_to_check)) {
            highest_prime = num_to_check;
            num_found++;
        }

        // Add 2 to skip even numbers
        num_to_check += 2; 
    }

}
