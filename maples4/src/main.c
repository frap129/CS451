/*
 * Author: Joseph Maples
 * Assignment Number: 4
 * Date of Submission: TBD
 * Name of this file: main.c
 * Description of the program:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void handle_cmd(list *mem, char *input, int len) {
    if (input[0] == 'R') {
        if (input[1] == 'Q') {
            if (input[3] == 'P') {
                int proc, fit = 0;
                LLU size = 0;
                char fit_tmp = 'B';
                sscanf(input, "%*s %*c%d %llu %c", &proc, &size, &fit_tmp);
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
                        break;
                }
                if (!insert(mem, size, proc, fit))
                    printf("error: Not enough space available, try compacting first.\n");
            }
        } else if (input[1] == 'L') {
            if (input[3] == 'P') {
                int proc = 0;
                sscanf(input, "%*s %*c%d", &proc);
                release(mem, proc);
            }
        }
    } else if (input[0] == 'C') {
        compact(mem);
    } else if (input[0] == 'X') {
        free(input);
        free_list(mem);
        exit(EXIT_SUCCESS);
    } else if (input[0] == 'S') {
        if (len >= 4) {
            char *test = (char*) malloc(sizeof(char)*5);
            sprintf(input, "%.*s", 4, test);
            if (strcmp(test, "STAT")) {
                stat(mem);
            }
        }
    }
}

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

    free_list(mem);
    return;
}

/*
    Function Name: main
    Input to the method: number of args (int), list of args (char**)
    Output(Return value): Exit code (int)
    Brief description of the task:
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("%s: size missing from arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    LLU size = atoll(argv[1]);
    interact(size, argv[0]);
    
    return 0;
}