/*
 * Author: Joseph Maples
 * Assignment Number: 2
 * Date of Submission: TBD
 * Name of this file: child.c
 * Description of the program: Prime checking algorithms for child processes.
 */

#include <stdio.h>

#define BASE_PRIME    123400003

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

int main() {
	int num_printed = 0;
    long long unsigned int num_to_check = BASE_PRIME + 1; 
    while (num_printed < 10) {
        if (check_prime(num_to_check == 1)) {
            printf("prime number is %llu \n", num_to_check);
            num_printed++;
        }
        num_to_check++; 
    }
}
