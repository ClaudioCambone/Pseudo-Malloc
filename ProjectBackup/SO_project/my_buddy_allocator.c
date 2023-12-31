#include <stdio.h>
#include <assert.h>
#include <math.h> 
#include "my_buddy_allocator.h"
#include <stdlib.h>


// these are trivial helpers to support you in case you want
// to do a bitmap implementation

int levelIdx(size_t size){
  return MAXLEVELS -(ceil(log2(size)));
}

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

int leftchild(int parentindx){
    return parentindx * 2 + 1;
}

int rightchild(int parentindx) {
  return parentindx * 2 + 2;
}

void mybuddy_init (mybuddy *buddy_alloc,char *memory, uint8_t *buffer){
    int num_bits = (1 << MAXLEVELS) -1; //CALCOLATE NUM_BITS REQUIRED TO REPRESENT A TREE WITH MAXLEVELS levels (like pow(2,maxlevels +1) -1)
    buddy_alloc->memory = memory;
    buddy_alloc->num_levels = MAXLEVELS;
    BitMap_init(&(buddy_alloc->bitmap),num_bits,buffer);


    // for(int i = 0; i <= MAXLEVELS; i++){
    //     buddy_alloc->num_nodes[i] = (1 << i);  //each floor the number of nodes is 2^i, e.g. floor i = 3 has 2^3 = 8 nodes  (like pow(2,i) but it is an integer and not float)
    // }
}

int mybuddy_getFree(BitMap* bit_map, int level) {
  int start = (1 << level) - 1;
  int end = (1 << (level + 1)) - 1;
  for(int i = start; i <= end; i++) {
    if(BitMap_bit(bit_map, i) == 0) {
      printf("Available buddy at level %d found! It has index %d in the BitMap\n", level, i);
      return i;
    }
  }
  printf("No available buddies found at level %d\n", level);
  return -1;
}


// TO-DO 
void *mybuddy_allocBuddy(mybuddy *buddy_alloc, int size){
    if( size > MEMORYSIZE){
        perror("memory requested overflow available");
        exit(-1);
    }
    int nec_level = levelIdx(size); //ceil is used to round a number up to the nearest integer 
    assert(nec_level >= 0);
    while(nec_level > -1){
    int numbuddies =  (1 << nec_level);  
    printf("num buddies %d level %d \n\n",numbuddies,nec_level);
    int free = mybuddy_getFree(&(buddy_alloc->bitmap),nec_level);   

    if(free != -1){
        BitMap_setBit((&buddy_alloc->bitmap),free,1);
        int buddysize = MEMORYSIZE / (1 << nec_level); 
        printf("memory allocated, buddy size is %d\n\n", buddysize);
            return free;
    }
    else{
        printf("N.A. Memory, cheching lv below \n");
        nec_level = nec_level - 1;
    }

    }
        //if no memory is available goes here
    printf("Not enough memory, abort allocBuddy \n");
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
    uint8_t buffer[BUFFER_SIZE]; 
    mybuddy buddy;
    mybuddy_init(&buddy,memory,buffer);
    BitMap_setall(&buddy.bitmap,0); 
    //BitMap_setBit(&buddy.bitmap, 2097149, 1);
    BitMap_setBit(&buddy.bitmap, 0, 1);
    //BitMap_setBit(&buddy.bitmap, 2049, 1);
    //BitMap_setbyte(buffer,32);
    //BitMap_setchunk(buffer,2060,32);
    printbuddy(&buddy);
    
    //int result = BitMap_checkchunk(buffer, 44,63);
    //printf("risultato %d",result);
    //int i = levelIdx(1025); 
    //printf("%d",i);
    //i = BuddyAllocator_getFreeBuddy(&buddy.bitmap, i);
    //for(int i = 0; i < 128; i++){
    //mybuddy_allocBuddy(&buddy,2047);
    //}
        // mybuddy_allocBuddy(&buddy,524287);
        // printbuddy(&buddy);
        //         mybuddy_allocBuddy(&buddy,524287);
        // mybuddy_allocBuddy(&buddy,524287);


      //  mybuddy_allocBuddy(&buddy,524287);

    //printbuddy(&buddy);


}





