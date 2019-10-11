/*
 * Author: Joseph Maples
 * Assignment Number: 1
 * Date of Submission: TBD
 * Name of this file: 5ps.c
 * Description of the program: A simple version of ps that accepts 5 arguments
 */

#include <stdio.h>
#include "parser.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    options opts = set_options(argc, argv);
    if (is_opts_empty(opts))
        return 0;
    
    return 0;
}