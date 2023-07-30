#include <stdio.h>
#include <assert.h>
#include <math.h> 
#include "my_buddy_allocator.h"

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
    int num_bits = pow(2,MAXLEVELS +1) -1; //CALCOLATE NUM_BITS REQUIRED TO REPRESENT A TREE WITH MAXLEVELS levels
    BitMap_init(&buddy_alloc->bitmap,num_bits,buffer);
    buddy_alloc->memory = memory;
    buddy_alloc->num_levels = MAXLEVELS;

    for(int i = 0; i <= MAXLEVELS; i++){
        buddy_alloc->num_nodes[i] = pow(2,i);  //each floor the number of nodes is 2^i, e.g. floor i = 3 has 2^3 = 8 nodes 
    }
}

// TO-DO 
void balloc(mybuddy *buddy_alloc, int size){
    if( size > MEMORYSIZE)
        perror("memory requested overflow available");
    int nec_level = MAXLEVELS - (int) ((log2(size))) + 1; 
    printf("approssimo per eccesso?? %d", nec_level);
    
    
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
    uint8_t buffer[2^MAXLEVELS + 1]; 
    mybuddy buddy;
    mybuddy_init(&buddy,memory,buffer);
    BitMap_setall(&buddy.bitmap,0); 
    //BitMap_setBit(&buddy.bitmap, 2097149, 1);
    // BitMap_setBit(&buddy.bitmap, 9, 1);
    //BitMap_setBit(&buddy.bitmap, 3, 1);
    //BitMap_setbyte(buffer,32);
    BitMap_setchunk(buffer,16,64);
    printbuddy(&buddy);

    int result = BitMap_checkfree(buffer,8);
    printf("risultato %d",result);
    balloc(&buddy,1024);
}