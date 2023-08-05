#pragma once
#include <stdio.h>
#include "bit_map.h"

#define MEMORYSIZE (1024*1024)
#define MAXLEVELS 9
#define NUMBUDDIES 1 << MAXLEVELS
#define BUFFER_SIZE ((NUMBUDDIES + 7) << 3)


typedef struct mybuddy{
    int idx; //index of the buddy in the tree
    BitMap bitmap;
    char *memory; //memory size
    int num_levels;
}mybuddy;

//initialize the buddy using the bitmap
void mybuddy_init (mybuddy *buddy_alloc, char *bitmap, uint8_t *buffer);

//print all the data relative the buddy
void printbuddy(mybuddy *buddyalloc);

//alloc size space using the smallest buddy possible
void *balloc(mybuddy *buddy_alloc, int size);

//return the index of the father of a given buddy
int parentIdx(int idx);

//return the index of brother of a given buddy
int buddyIdx(int idx);

//return the lv_idx needed to allocate size bits (e.g. 1025 returns 9 --> memorysize/2^9 = 2048)
int levelIdx(size_t idx);

//returns the idx of the first free buddy
int mybuddy_getFree(BitMap* bit_map, int level);

//returns the idx of the left child of a parent
int leftchild(int parentindx);

//returns the idx of the right child of a parent
int rightchild(int parentindx);


