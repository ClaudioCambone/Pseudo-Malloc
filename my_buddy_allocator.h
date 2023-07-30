#pragma once
#include <stdio.h>
#include "bit_map.h"

#define MAXLEVELS 20 // 2^20 buddies
#define MEMORYSIZE 1024*1024 //1MB


typedef struct mybuddy{
    BitMap bitmap;
    char *memory; //memory size
    int num_levels;
    size_t num_nodes[MAXLEVELS + 1];
}mybuddy;

//initialize the buddy using the bitmap
void mybuddy_init (mybuddy *buddy_alloc, char *bitmap, uint8_t *buffer);

//print all the data relative the buddy
void printbuddy(mybuddy *buddyalloc);

