#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/mman.h>
#include <string.h>
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
        *((int *)ptr) = size;
        return ptr + sizeof(int);
    }

}

void *pseudo_calloc( int size, int elem){
    void* ptr = pseudo_malloc(size * elem);
    memset(ptr , 0 , size * elem);

    return ptr;
}


//free the memory pointed
void malloc_free(void *ptr,int size){
    //i tried to implement a function working only with ptr as parameter but it didn't work
     if (size < PAGESIZE/4){
        int* index_ptr = ((int*)ptr) - 1;
         // Adjust the pointer to point to the index
        int idx = *index_ptr;
        mybuddy_Freebuddy(&buddy,idx);
        printf("\nmemory freed correctly with buddy allocator \n");

    }
    else{
        munmap(ptr, *((int*)ptr));
        printf("\n memory freed correctly with munmap \n");
    }

}

/*

void malloc_free(void *ptr) {
    if (ptr >= (void*)memory && ptr < (void*)(memory + MEMORYSIZE * sizeof(char))) {
        int* index_ptr = ((int*)ptr) - 1;
        // Adjust the pointer to point to the index
        int idx = *index_ptr;
        // Proceed to free the buddy or perform other necessary actions
    }
    else {
        munmap(ptr - sizeof(int), *((int*)(ptr - sizeof(int))));
        printf("\n memory freed correctly with munmap \n");
    }
}
*/