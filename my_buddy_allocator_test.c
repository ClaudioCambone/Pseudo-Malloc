#include <stdio.h>
#include <assert.h>
#include <math.h> 
#include "my_buddy_allocator.h"
#include "pseudo_malloc.h"
#include <stdlib.h>

    //Testing some functions and some allocations 

int main(){
    char memory[MEMORYSIZE];
    uint8_t buffer[BUFFER_SIZE]; 
    mybuddy buddy;
    mybuddy_init(&buddy,memory,buffer);
    //BitMap_setBit(&buddy.bitmap, 2097149, 1);
    //BitMap_setBit(&buddy.bitmap, 9, 1);
    //BitMap_setBit(&buddy.bitmap, 2049, 1);
    //BitMap_setbyte(buffer,32);
    //BitMap_setchunk(buffer,2060,32);
    //printbuddy(&buddy);
    
    //int result = BitMap_checkchunk(buffer, 44,63);
    //printf("risultato %d",result);
    //int i = levelIdx(1025); 
    //printf("%d",i);
    //i = BuddyAllocator_getFreeBuddy(&buddy.bitmap, i);

    //mybuddy_allocBuddy(&buddy,0);

    printbuddy(&buddy);

        for( int i = 0; i < 10; i++){
          mybuddy_allocBuddy(&buddy,3);
    }

    mybuddy_allocBuddy(&buddy,0);
    mybuddy_allocBuddy(&buddy,1);
    mybuddy_allocBuddy(&buddy,1);
    mybuddy_allocBuddy(&buddy,2);
    mybuddy_allocBuddy(&buddy,2);
    mybuddy_allocBuddy(&buddy,2);

  for(int i = 0; i < 8; i++){

  void *allocated_memory = mybuddy_malloc(&buddy, 64); // Allocate 128 bytes
    if (allocated_memory) {
        printf("Allocated memory at address: %p\n", allocated_memory);
    }
  }
      printbuddy(&buddy);
        mybuddy_Freebuddy(&buddy,6);
          printbuddy(&buddy);

}