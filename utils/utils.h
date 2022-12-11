/* primary_header.h */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CHAR 256

#define INITIAL_CAPACITY 5
#define GROWTH_FACTOR 1.618
typedef struct Vector
{
    void** data;
    size_t elem_size;
    size_t limit;
    size_t count;
    void (*push_back)   (struct Vector*, void*);
    void (*pop_back)    (struct Vector*, void*);
    void (*remove_at)   (struct Vector*, int);
    void (*free)        (struct Vector*);
} Vector;

void VectorInit(Vector* vector);

extern FILE * f;
extern int part;

/*
* Parse the command line arguments and return 0 for success or 1 for failure
* The first parameter is the input file name. The second parameter is the part of the challenge <1 or 2>
*/
int parse_command_line(int argc, char ** argv);

#endif /* UTILS_H */