/* primary_header.h */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern FILE * f;
extern int part;

/*
* Parse the command line arguments and return 0 for success or 1 for failure
* The first parameter is the input file name. The second parameter is the part of the challenge <1 or 2>
*/
int parse_command_line(int argc, char ** argv);

#endif /* PRIMARY_HEADER_H */