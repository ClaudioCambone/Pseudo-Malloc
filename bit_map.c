  #include <assert.h>
  #include "bit_map.h"
  #include <stdio.h>
  #include <stdint.h>
  #include <math.h> 
  #include <stddef.h>
  #include <stdlib.h>
  #include <unistd.h>

  // returns the number of bytes to store bits booleans
  int BitMap_getBytes(int bits){
    return bits / 8 + ((bits % 8) != 0);
  }

  // initializes a bitmap on an external array
  void BitMap_init(BitMap* bit_map, int num_bits, uint8_t* buffer){
    bit_map->buffer=buffer;
    bit_map->num_bits=num_bits;
    bit_map->buffer_size=BitMap_getBytes(num_bits);
    for(int i = 0; i < num_bits; i++){
      BitMap_setBit(bit_map,i,FREE);
    }
  }

  void BitMap_setBit(BitMap* bit_map, int bit_num, int status){
    // get byte
    int byte_num = bit_num / 8;
    assert(byte_num < bit_map->buffer_size);
    int bit_in_byte = bit_num % 8;
    if (status)
    {
      bit_map->buffer[byte_num] |= (1 << bit_in_byte);
    }
    else
    {
      bit_map->buffer[byte_num] &= ~(1 << bit_in_byte);
    }
  }

  void BitMap_setall(BitMap* bit_map,int status){
      for(int i = 0; i < bit_map->num_bits; i++){
        BitMap_setBit(bit_map, i, status);
      }

  }
  void BitMap_printall(BitMap* bit_map) {
      for (int i = 0; i < bit_map->num_bits; i++) {
          printf("Bit %d: %d ", i, BitMap_bit(bit_map, i));
          if ((i + 1) % 8 == 0) {
              printf("\n"); // Print a newline after every 8 bits
          }
      }
      printf("\n ---END OF BITMAP--- \n\n");
  }


  // inspects the status of the bit bit_num
  int BitMap_bit(const BitMap* bit_map, int bit_num){
    int byte_num = bit_num / 8;
    assert(byte_num < bit_map->buffer_size);
    int bit_in_byte = bit_num % 8;
    return (bit_map->buffer[byte_num] & (1 << bit_in_byte)) != 0;
  }

  /*UNUSED 
  int BitMap_checkfree(uint8_t* buffer, size_t portion){
    return (buffer[portion / 8] |=  (1 << (portion % 8)) == 0);
  }

  int BitMap_checkchunk(uint8_t* buffer,int start, int chunk){
    int result;
    start = (start / 8) * 8;
    chunk = BitMap_getBytes(chunk) * 8;
    for(int i = start; i < chunk + start; i++){
      if(BitMap_checkfree(buffer,i) == 1)
        return -1;
    }
    return 0;
  }

  void BitMap_setchunk(uint8_t* buffer,int start, int chunk){
    start = (start / 8) * 8;
    chunk = BitMap_getBytes(chunk) * 8;
    for(int i = start; i < chunk + start; i++){
      BitMap_setbyte(buffer,i);
    }
  }

  int BitMap_find_first_free(BitMap* bit_map, int start_bit) {
      int byte_num = start_bit >> 3;
      int bit_in_byte = byte_num & 0x07;

      // Start searching from the specified start_bit
      int current_byte = byte_num;
      int current_bit = bit_in_byte;

      // Find the first free bit in the bitmap
      while (current_byte < bit_map->buffer_size) {
          uint8_t byte_value = bit_map->buffer[current_byte];
          uint8_t mask = 1 << current_bit;

          // Check if the current bit is free (0)
          if ((byte_value & mask) == 0) {
              printf("free %d",(current_byte << 3) + current_bit);
              return (current_byte << 3) + current_bit;
          }

          // Move to the next bit
          current_bit++;
          if (current_bit >= 8) {
              current_byte++;
              current_bit = 0;
          }
      }

      // If no free bit is found, return -1
      return -1;
  }
  
  void BitMap_setbyte(uint8_t* buffer, size_t portion){
          buffer[portion / 8] |=  (1 << (portion % 8));
  }
  */