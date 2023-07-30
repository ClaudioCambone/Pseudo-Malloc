#pragma once
#include <stdint.h>
#include <stddef.h>

// simple bit array
typedef struct  {
  uint8_t *buffer;  // externally allocated buffer
  int buffer_size;
  int num_bits; 
} BitMap;

// returns the number of bytes to store bits booleans
int BitMap_getBytes(int bits);

// initializes a bitmap on an external array
void BitMap_init(BitMap* bit_map, int num_bits, uint8_t* buffer);

// sets a the bit bit_num in the bitmap
// status= 0 or 1
//DEPRECATED USING setbyte
void BitMap_setBit(BitMap* bit_map, int bit_num, int status);

// inspects the status of the bit bit_num
//DEPRECATED USING checkfree
int BitMap_bit(const BitMap* bit_map, int bit_num);

// print all the bitmap
void BitMap_printall(BitMap* bit_map);

// set all the bit in the bitmap to 1 or 0 
void BitMap_setall(BitMap* bit_map,int status);

//check if a portion of the bitmap is free, returns 0 if free, returns corrispondent byte 
//like bitmap_bit
int BitMap_checkfree(uint8_t* buffer, size_t portion);

//SET A BYTE TO 1 
void BitMap_setbyte(uint8_t* buffer, size_t portion);

//
void BitMap_setchunk(uint8_t* buffer,int start, int chunk);





