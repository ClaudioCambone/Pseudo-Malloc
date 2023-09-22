#pragma once
#include <stdio.h>
#include "bit_map.h"





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
int mybuddy_allocBuddy(mybuddy *buddy_alloc, int nec_level);

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

//returns a pointer to the memory address of a buddy
void *mybuddy_getAddress(mybuddy *buddy_alloc,int off);

//returns the offset given a buddy idx
int mybuddy_getoffset(mybuddy *buddy_alloc,int level, int buddy_idx);

//returns size of a buddy
int mybuddy_getBuddysize(int level);

//this function is the core of the program, 
//it alloc the smallest buddy to manage size memory and returns a pointer to the memory address of the allocated buddy
void *mybuddy_malloc(mybuddy *buddy_alloc, int size);

//free buddy of a given index
void mybuddy_Freebuddy(mybuddy *buddyalloc, int idx);

void detachbuddy(mybuddy *buddyalloc, void* ptr);
