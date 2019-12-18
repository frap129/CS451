/*
 * Author: Joseph Maples
 * Assignment Number: 4
 * Date of Submission: December 18th, 2019
 * Name of this file: main.c
 * Description of the program: Executes user requests for memory management
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
    Function Name: handle_rq_cmd
    Input to the method: memory (list), user input (string)
    Output(Return value): None (void)
    Brief description of the task: Parse RQ command and execute insert.
 */
void handle_rq_cmd(list *mem, char *input) {
    // Scan in data from input string
    int proc, fit = 0;
    LLU size = 0;
    char fit_tmp = 'B';
    sscanf(input, "%*s %*c%d %llu %c", &proc, &size, &fit_tmp);

    /*
        Assign a numeric fit value based on the input char, print an error if the fit is invalid.
    */
    switch(fit_tmp) {
        case 'F':
            fit = FIRST;
            break;
        case 'B':
            fit = BEST;
            break;
        case 'W':
            fit = WORST;
            break;
        default:
            printf("error: Invalid fit function\n");
            return;
            break;
    }

    // Insert the memory, print an error if there isn't space
    if (!insert(mem, size, proc, fit))
        printf("error: Not enough space available, try compacting first\n");
}

/*
    Function Name: handle_cmd
    Input to the method: memory(list), user input (string), input length (int)
    Output(Return value): None (void)
    Brief description of the task: Execute the function that corresponds to
                                   the users input command.
 */
void handle_cmd(list *mem, char *input, int len) {
    /*
        Parse input to determine which command was given. Once a command is 
        determined, call the function that executes that command. Otherwise,
        print an unknown command error.
    */
    if (input[0] == 'R' && input[1] == 'Q' && input[3] == 'P') {
        handle_rq_cmd(mem, input);
    } else if (input[0] == 'R' && input[1] == 'L' && input[3] == 'P') {
        // Scan in data from input
        int proc = 0;
        sscanf(input, "%*s %*c%d", &proc);
        release(mem, proc);
    } else if (input[0] == 'C' && len <= 2) {
        compact(mem);
    } else if (input[0] == 'X' && len <= 2) {
        // Free everything and exit
        free(input);
        free_list(mem);
        exit(EXIT_SUCCESS);
    } else if (input[0] == 'S' && len <= 4) {
        // Verify that the cmd was actually "STAT"
        char *test = (char*) malloc(sizeof(char)*5);
        sprintf(input, "%.*s", 4, test);
        if (strcmp(test, "STAT"))
            stat(mem);
        else
            printf("error: Invalid command: %s\n", input);
    } else
        printf("error: Invalid command: %s\n", input);
}

/*
    Function Name: interact
    Input to the method: size(long long unsigned int) and program name(string)
    Output(Return value): None (void)
    Brief description of the task: Read user input and send to cmd handler.
 */
void interact(LLU size, char *prog_name) {
    int character = 0;
    list *mem = init_list(size);

    // Run until Ctrl+D (EOF) is sent
    while (character != EOF) {
        char *input = malloc(1);
        int length = 0;
        printf("%s> ", prog_name);
        // Read each line of input char by char
        while((character = fgetc(stdin)) != '\n' && character != EOF) {
            input[length++] = character;
            input = realloc(input, length + 1); // Increase memory as needed
        }

        clearerr(stdin); // Clear error after reaching EOF

        // If EOF is reached on a blank line, exit early
        if (length == 0 && character == EOF)
            return;

        // Preform requested action
        handle_cmd(mem, input, length);

        // clean up
        free(input);
    }

    // Destroy the list
    free_list(mem);
    return;
}

/*
    Function Name: main
    Input to the method: number of args (int), list of args (char**)
    Output(Return value): Exit code (int)
    Brief description of the task: Read the initial arguments and start user
                                   interaction.
 */
int main(int argc, char **argv) {
    // Ensure a total size was passed
    if (argc < 2) {
        printf("%s: size missing from arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Read total size and start user interaction
    LLU size = atoll(argv[1]);
    interact(size, argv[0]);
    
    return 0;
}