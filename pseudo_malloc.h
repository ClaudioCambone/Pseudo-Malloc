#pragma once
#include <stdio.h>
#include "bit_map.h"



#define MEMORYSIZE (1 << 20)
#define MAXLEVELS 9
#define NUMBUDDIES ((1 << MAXLEVELS) - 1)
#define BUFFER_SIZE (MEMORYSIZE/MAXLEVELS)

char memory[MEMORYSIZE];
mybuddy buddy;


//Allocate memory of size size
void *pseudo_malloc(size_t size);

void *pseudo_calloc( int size, int elem);


//free the pointed memory
void malloc_free(void *ptr,int size);