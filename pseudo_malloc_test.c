#include "my_buddy_allocator.h"
#include "pseudo_malloc.h"
#include <stdio.h>
extern mybuddy buddy;

int main() {
    char memory[MEMORYSIZE];
    uint8_t buffer[BUFFER_SIZE];  // Adjust this size as needed
    mybuddy_init(&buddy,memory,buffer);


    // Test 1: Allocate using buddy allocator
    printbuddy(&buddy);
    printf("Test 1: Allocate using buddy allocator\n");
    int size = 64;
    void *ptr1 = pseudo_malloc(size);
    if (ptr1) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr1);
        malloc_free(ptr1,size); // Free a buddy to reuse it
    }
    else {
        printf("Failed to allocate memory\n");
    } 


    // Test 2: Allocate using mmap
    printf("\n\nTest 2: Allocate using mmap\n");
    size = 4096;
    void *ptr2 = pseudo_malloc(size);
    if (ptr2) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr2);
        malloc_free(ptr2,size); // Free a buddy to reuse it
    }
    else {
        printf("Failed to allocate memory\n");
    } 



    // Test 3: Allocate and free using buddy allocator
    printf("\n\nTest 3: Allocate and free using buddy allocator\n");
    size = 128;
    void *ptr3 = pseudo_malloc(size);
    if (ptr3) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr3);
        malloc_free(ptr3,size); // Free a buddy to reuse it
    }
    else {
        printf("Failed to allocate memory\n");
    } 


    // Test 4: Allocate using mmap and free using free function
    printf("\n\nTest 4: Allocate using mmap and free using free function\n");
    size = 1024;
    void *ptr4 = pseudo_malloc(size);
     if (ptr4) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr4);
        malloc_free(ptr4,size);

    }
    else {
        printf("Failed to allocate memory\n");
    } 



    // Test 5: Allocate maximum amount using buddy allocator
    printf("\n\nTest 5: Allocate maximum amount using buddy allocator\n");
    size = 512;
    void *ptr5 = pseudo_malloc(size);
    if (ptr5) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr5);
        malloc_free(ptr5,size);
    }
    else {
        printf("Failed to allocate memory\n");
    } 




    // Test 6: Allocate 2 portions of max memory using buddy allocator
    printf("\n\nTest 6: Allocate 2 portions of max memory using buddy allocator\n");
    size = 512;
    void *ptr6 = pseudo_malloc(size);
    if (ptr6) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr6);
    }
    else {
        printf("Failed to allocate memory\n");
    } 

    void *ptr6_1 = pseudo_malloc(size);
    if (ptr6_1) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr6_1);
    }
    else {
        printf("Failed to allocate memory\n");
    } 

        malloc_free(ptr6,size);


    //Test 7: Trying to allocate different portions of different size
    printf("\n\nTest 7: Trying to allocate different portions of different size\n");
    size = 512;
    void *ptr7 = pseudo_malloc(size);
    if (ptr7) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr7);
    }
    else {
        printf("Failed to allocate memory\n");
    } 
    size = 256;
    void *ptr7_1 = pseudo_malloc(size);
    if (ptr7_1) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr7_1);
    }
    else {
        printf("Failed to allocate memory\n");
    } 


  

    //Test 8: Allocate a block using calloc
    printf("\n\nTest 8: Allocate a block using calloc\n");
    size = 12;
    int elem = 10;
    void *ptr8 = pseudo_calloc(size,elem);
    if (ptr8) {
        printf("Allocated memory using buddy allocator at address: %p, all the %d block of size %d have been set to 0\n", ptr8,elem,size);
    }
    else {
        printf("Failed to allocate memory\n");
    } 
    malloc_free(ptr8,size);


   //Test 9: Allocate a block using calloc mmap
    printf("\n\nTest 9: Allocate a block using calloc nmap\n");
    size = 4;
    elem = 300;
    void *ptr9= pseudo_calloc(size,elem);
    if (ptr9) {
        printf("Allocated memory using buddy allocator at address: %p, all the %d block of size %d have been set to 0\n", ptr9,elem,size);
    }
    else {
        printf("Failed to allocate memory\n");
    } 
    malloc_free(ptr9,size * elem);
    return 0;
}
