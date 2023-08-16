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
    void *ptr1 = pseudo_malloc(64);
    if (ptr1) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr1);
        mybuddy_Freebuddy(&buddy, mybuddy_getFree(&buddy.bitmap, 3)); // Free a buddy to reuse it
    } else {
        printf("Failed to allocate memory\n");
    }

    // Test 2: Allocate using mmap
    printf("\nTest 2: Allocate using mmap\n");
    void *ptr2 = pseudo_malloc(4096);
    if (ptr2) {
        printf("Allocated memory using mmap at address: %p\n", ptr2);
        free(ptr2);
    } else {
        printf("Failed to allocate memory\n");
    }

    // Test 3: Allocate and free using buddy allocator
    printf("\nTest 3: Allocate and free using buddy allocator\n");
    void *ptr3 = pseudo_malloc(128);
    if (ptr3) {
        printf("Allocated memory using buddy allocator at address: %p\n", ptr3);
        mybuddy_Freebuddy(&buddy, mybuddy_getFree(&buddy.bitmap, 4));
    } else {
        printf("Failed to allocate memory\n");
    }

    // Test 4: Allocate using mmap and free using free function
    printf("\nTest 4: Allocate using mmap and free using free function\n");
    void *ptr4 = pseudo_malloc(1024);
    if (ptr4) {
        printf("Allocated memory using mmap at address: %p\n", ptr4);
        free(ptr4);
    } else {
        printf("Failed to allocate memory\n");
    }

    return 0;
}
