#pragma once
#include <stdio.h>
#include "bit_map.h"

#define MAXLEVELS 20 // 2^20 buddies
#define MEMORYSIZE 1024*1024 //1MB


typedef struct mybuddy{
    int idx; //index of the buddy in the tree
    BitMap bitmap;
    char *memory; //memory size
    int num_levels;
    size_t num_nodes[MAXLEVELS + 1];
}mybuddy;

//initialize the buddy using the bitmap
void mybuddy_init (mybuddy *buddy_alloc, char *bitmap, uint8_t *buffer);

//print all the data relative the buddy
void printbuddy(mybuddy *buddyalloc);

//alloc size space using the smallest buddy possible
void *balloc(mybuddy *buddy_alloc, int size);

int parentIdx(int idx);

int buddyIdx(int idx);

int levelIdx(size_t idx);

