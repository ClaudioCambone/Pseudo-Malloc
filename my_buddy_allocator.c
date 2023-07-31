#include <stdio.h>
#include <assert.h>
#include <math.h> 
#include "my_buddy_allocator.h"
#include <stdlib.h>

// these are trivial helpers to support you in case you want
// to do a bitmap implementation
int levelIdx(size_t idx){
  return (int)floor(log2(idx));
};

int buddyIdx(int idx){
  if (idx&0x1){
    return idx-1;
  }
  return idx+1;
}

int parentIdx(int idx){
  return idx/2;
}

int startIdx(int idx){
  return (idx-(1<<levelIdx(idx)));
}

void mybuddy_init (mybuddy *buddy_alloc,char *memory, uint8_t *buffer){
    int num_bits = (1 <<(MAXLEVELS +1)) -1; //CALCOLATE NUM_BITS REQUIRED TO REPRESENT A TREE WITH MAXLEVELS levels (like pow(2,maxlevels +1) -1)
    BitMap_init(&buddy_alloc->bitmap,num_bits,buffer);
    buddy_alloc->memory = memory;
    buddy_alloc->num_levels = MAXLEVELS;

    for(int i = 0; i <= MAXLEVELS; i++){
        buddy_alloc->num_nodes[i] = (1 << i);  //each floor the number of nodes is 2^i, e.g. floor i = 3 has 2^3 = 8 nodes  (like pow(2,i) but it is an integer and not float)
    }
}

// TO-DO 
void *balloc(mybuddy *buddy_alloc, int size){
    if( size > MEMORYSIZE){
        perror("memory requested overflow available");
        exit(-1);
    }
    int nec_level = MAXLEVELS -  ceil(log2(size)); //ceil is used to round a number up to the nearest integer 
                                                    //nec_level is the smallest level possible to alloc size space 

    //we need to find the first free buddy (first block of space in the bitmap)
    // Start the search from the position corresponding to the calculated level
    int start_position = (1 << nec_level) - 1;
    int offset = 0;
    while(nec_level>= 0){
    offset++;
    if( BitMap_checkchunk(buddy_alloc->bitmap.buffer,start_position,size) == 0){
        printf("free space, allocating memory");
        BitMap_setchunk(buddy_alloc->bitmap.buffer,(1 << nec_level) + offset,size);
        return (1 << nec_level) - offset;
    }
    else{
        nec_level--;
        start_position = (start_position - 1) / 2;       

    }
    }
    //if we reach here there is no available space
    return NULL;
}

void printbuddy(mybuddy *buddyalloc){
    printf("BITMAP PRINT \n");
    BitMap_printall(&buddyalloc->bitmap);
    printf("BUFFER SIZE %d \n", buddyalloc->bitmap.buffer_size);
    printf("MEMORY SIZE %d \n", MEMORYSIZE);
    printf("NUMBITS %d \n", buddyalloc->bitmap.num_bits);
    printf("NUMLEVELS %d \n",buddyalloc->num_levels);

}

int main(){
    char memory[MEMORYSIZE];
    //TESTING TIME
    uint8_t buffer[(1 << (MAXLEVELS + 1))]; 
    mybuddy buddy;
    mybuddy_init(&buddy,memory,buffer);
    BitMap_setall(&buddy.bitmap,0); 
    //BitMap_setBit(&buddy.bitmap, 2097149, 1);
    // BitMap_setBit(&buddy.bitmap, 9, 1);
    //BitMap_setBit(&buddy.bitmap, 3, 1);
    //BitMap_setbyte(buffer,32);
    //BitMap_setchunk(buffer,2060,32);
    //printbuddy(&buddy);
    
    //int result = BitMap_checkchunk(buffer, 44,63);
    //printf("risultato %d",result);

    void *i = balloc(&buddy,8192);
    printbuddy(&buddy);
    //i = balloc(&buddy, 512);


    if(i == NULL)
        printf("no space available, memory not allocated \n");
    else
        printf("memory allocated starts here %lu",(unsigned long) i);

        //RESULTS FROM TESTING WITH 2048 
    //START FROM 504 AND ARRIVES TO 2552 ( BYTE 63 TO BYTE 319 --> 256 * 8 bit == 2048 bit  )
}




