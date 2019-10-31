/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: child.c
 * Description of the program: Prime checking algorithms for child processes.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BASE_PRIME    123400003

long long unsigned int highest_prime;
int child_num;
pid_t pid;

void sig_handler(int sigval) {
    if (sigval == SIGTSTP) {
        printf("Process %d: My PID is %d: I am about to be suspended... " 
                    "Highest prime number I found is %llu.\n", child_num, pid,
                    highest_prime);
            pause();
    } else if (sigval == SIGCONT) {
        printf("Process %d: My PID is %d: I just got resumed " 
                "Highest prime number I found is %llu.\n", child_num, pid,
                highest_prime);
    } else if (sigval == SIGTERM) {
        printf("Process %d: My PID is %d: I completed my task and I am " 
                "exiting. Highest prime number I found is %llu.\n", child_num,
                pid, highest_prime);
        exit(EXIT_SUCCESS);
    }
}

int check_prime(long long unsigned int check) {
    long long unsigned int range = check / 2;
    long long unsigned int i = 2; 
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
    pid = getpid();

    // Print that we're getting started
    printf("Process %d: My PID is %d: I just got started. I am starting with " 
            "the number %u to find the next prime number.\n", child_num, pid,
             BASE_PRIME);

    // Create and set sigaction
    struct sigaction sa;
    memset (&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sigaction (SIGTSTP, &sa, NULL);
    sigaction (SIGCONT, &sa, NULL);
    sigaction (SIGTERM, &sa, NULL);

    int num_printed = 0;
    long long unsigned int num_to_check = BASE_PRIME + 1; 
    while (num_printed < 100) {
        if (check_prime(num_to_check) == 1) {
            printf("prime number is %llu \n", num_to_check);
            highest_prime = num_to_check;
            num_printed++;
        }
        num_to_check++; 
    }
}
