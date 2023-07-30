#include <assert.h>
#include "bit_map.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h> 
#include <stddef.h>
#include <stdlib.h>

// returns the number of bytes to store bits booleans
int BitMap_getBytes(int bits){
  return bits/8 + (bits%8!=0);
}

// initializes a bitmap on an external array
void BitMap_init(BitMap* bit_map, int num_bits, uint8_t* buffer){
  bit_map->buffer=buffer;
  bit_map->num_bits=num_bits;
  bit_map->buffer_size=BitMap_getBytes(num_bits);
}

int BitMap_checkfree(uint8_t* buffer, size_t portion){
  return (buffer[portion / 8] |=  (1 << (portion % 8)) == 0);
}

void BitMap_setbyte(uint8_t* buffer, size_t portion){
        buffer[portion / 8] |=  (1 << (portion % 8));
}

void BitMap_setchunk(uint8_t* buffer,int start, int chunk){
  for(int i = start; i < chunk + start; i++){
    BitMap_setbyte(buffer,i);
  }
}
// set the byte bit_num in the bitmap
// status= 0 or 1
//DEPRECATED, USING SETBYTE
void BitMap_setBit(BitMap* bit_map, int bit_num, int status){
  // get byte
  if(status != 0 && status != 1){
    perror("wrong status input");
    exit(EXIT_FAILURE);
  }
  int byte_num=bit_num/8;
  assert(byte_num<bit_map->buffer_size);
  int bit_in_byte=byte_num&0x03;
  if (status) {
    bit_map->buffer[byte_num] |= (1<<bit_in_byte);
  } else {
    bit_map->buffer[byte_num] &= ~(1<<bit_in_byte);
  }
}

void BitMap_setall(BitMap* bit_map,int status){
    for(int i = 0; i < bit_map->buffer_size * 8; i++){
       BitMap_setBit(bit_map, i, status);
    }

}

void BitMap_printall(BitMap* bit_map){
    for(int i = 0; i < 256; i++  ){
      printf("%d", BitMap_bit(bit_map,i) );
    }
      printf("\n ---END OF BITMAP--- \n\n");
}

// inspects the status of the bit bit_num
int BitMap_bit(const BitMap* bit_map, int bit_num){
  int byte_num=bit_num>>3; 
  assert(byte_num<bit_map->buffer_size);
  int bit_in_byte=byte_num&0x03;
  return (bit_map->buffer[byte_num] & (1<<bit_in_byte))!=0;
}
 /*
int main() {
    int BITMAPSIZE = 256; //buffer size is bitmap/8
    BitMap bit_map;
    uint8_t buffer[BITMAPSIZE]; // Adjust the size based on your requirements
    int num_bits = BITMAPSIZE; // You can adjust the number of bits for testing

  //SOME TESTING AND PRINTINGS 

    BitMap_init(&bit_map, num_bits, buffer);
    assert(bit_map.num_bits == num_bits);
    assert(bit_map.buffer_size == BitMap_getBytes(num_bits));

    printf("BUFFER SIZE in Byte %d \n", bit_map.buffer_size);

    BitMap_setall(&bit_map,1);
    BitMap_printall(&bit_map);

    BitMap_setBit(&bit_map,32,0);

    printf("bit num %d is %d \n", 32, BitMap_bit(&bit_map,32));

        BitMap_printall(&bit_map);

    return 0;


}*/