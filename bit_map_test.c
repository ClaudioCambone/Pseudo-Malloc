  #include <assert.h>
  #include "bit_map.h"
  #include <stdio.h>
  #include <stdint.h>
  #include <math.h> 
  #include <stddef.h>
  #include <stdlib.h>
  #include <unistd.h>

int main() {
      int BITMAPSIZE = 256; //buffer size is bitmap/8
      BitMap bit_map;
      uint8_t buffer[BITMAPSIZE]; // Adjust the size based on your requirements
      int num_bits = BITMAPSIZE; // You can adjust the number of bits for testing

    //Some simple prints and set

      BitMap_init(&bit_map, num_bits, buffer);
      assert(bit_map.num_bits == num_bits);
      assert(bit_map.buffer_size == BitMap_getBytes(num_bits));

      printf("BUFFER SIZE in Byte %d \n", bit_map.buffer_size);

    //Test 1: set all bit 1
      BitMap_setall(&bit_map,1);
      BitMap_printall(&bit_map);

    //Test 2: set 1 bit to 0
      BitMap_setBit(&bit_map,32,0);
      printf("bit num %d is %d \n", 32, BitMap_bit(&bit_map,32));
      BitMap_printall(&bit_map);
    
    //Test 3: Get bytes function
      int size = 10;
      printf("%d in bytes is %d",size,BitMap_getBytes(size));

      return 0;

  }