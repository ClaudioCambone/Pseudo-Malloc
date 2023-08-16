#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/mman.h>
#include "my_buddy_allocator.h"
#include "pseudo_malloc.h"
#include "bit_map.h"

//i'm taking the pagesize from the system, but i think is bettere if I used a fixed size (4096)
#define PAGESIZE 4096



//Allocate memory of size
void *pseudo_malloc(size_t size){
    //IF SIZE > PAGE/4 DO MMAP, ELSE USE BUDDY ALLOC
    
    if(size < PAGESIZE/4){
        //use buddy allocator
        void *ptr = mybuddy_malloc(&buddy,size);
        return ptr;
    }
    else{
        //use mmap
        void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        return ptr;
    }

}


//TESTING NEEDED
//free the memory pointed
void free(void *ptr){
    if(ptr < MEMORYSIZE +(void *) memory && ptr >= (void *) memory){
        size_t idx = (ptr - (void*) memory)/PAGESIZE;
        mybuddy_Freebuddy(&buddy,idx);
    }
    else{
    //mmap
    munmap(ptr,sizeof(ptr));
    }
}
