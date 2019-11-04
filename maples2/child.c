/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: child.c
 * Description of the program: Prime checking algorithms for child processes.
 */

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BASE_PRIME	1234000031
#define MAX_RANGE   1000000
#define LLU		long long unsigned

LLU int highest_prime;
int child_num;
int priority;
pid_t pid;

void sig_handler(int sigval) {
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

int check_prime(long long unsigned int check) {
    // Determine our range of 3 to sqrt(n)
    LLU int range = sqrt(check);
    LLU int i = 2; 

    int prime = 1;
    while (prime == 1 && i <= range) { 
        if (check % i == 0) 
            prime = 0;
        i++;
    } 
    return (prime);
}

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

    int num_printed = 0;
    LLU int num_to_check = BASE_PRIME; 
    while (num_printed < MAX_RANGE) {
        if (check_prime(num_to_check)) {
            highest_prime = num_to_check;
            num_printed++;
        }

        // Add 2 to skip even numbers
        num_to_check += 2; 
    }

}
