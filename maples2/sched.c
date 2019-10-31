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
#include "sched.h"
#include "parser.h"

char *prog_name;

int check_prime(unsigned long long int check) {
      unsigned long long int i = 2; 
      int prime = 1; 
      while (prime == 1&& i < check/2) { 
              if (check % i == 0) 
                prime = 0;
              i++;
      } 
      return (prime);
}

int child_task() {
	int num_printed = 0;
    long long unsigned int num_to_check = BASE_PRIME + 1; 
    while (num_printed < 10) {
        if (check_prime(num_to_check == 1)) {
            printf("prime number is %llu \n", num_to_check);
            num_printed++;
        }
        num_to_check++; 
    }
    return num_printed;
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

    return 0;
}
