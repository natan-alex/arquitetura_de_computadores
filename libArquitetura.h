#ifndef LIB_ARQUITETURA
#define LIB_ARQUITETURA

#include <stdint.h>


typedef struct BinaryNumber {
    uint8_t number_of_bits;
    uint8_t * bits;
} BinaryNumber;

typedef struct SumResultOf1BitOperation {
    uint8_t sum;
    uint8_t carry_out;
} SumResultOf1BitOperation;

typedef struct SumResultOfNBitsOperation {
    BinaryNumber * sum;
    uint8_t carry_out;
} SumResultOfNBitsOperation;


BinaryNumber * create_new_binary_number(uint8_t number_of_bits);

void doInPlaceShiftLeft(BinaryNumber * binary);

void doInPlaceShiftRight(BinaryNumber * binary);

SumResultOf1BitOperation * getHalfSum(uint8_t first_bit, uint8_t second_bit);

SumResultOf1BitOperation * getSumOf1Bit(uint8_t first_bit, uint8_t second_bit, uint8_t carry_in);

SumResultOfNBitsOperation * getSumOfNBits(BinaryNumber * first, BinaryNumber * second, uint8_t carry_in);

BinaryNumber * getNewBinaryByJoiningTwoBinaryNumbers(BinaryNumber * first, BinaryNumber * second);

BinaryNumber * getASliceOfABinaryNumber(BinaryNumber * binary, uint8_t index_of_first_bit, uint8_t slice_length);

void showBinaryNumber(BinaryNumber * binary);

int getDecimalValue(BinaryNumber * binary);

int getDecimalValueOfABinaryNumberRepresentedByAString(char binary[]);

BinaryNumber * readBinaryNumber(uint8_t number_of_bits);

uint8_t getDecimalValueOfAHexChar(char c);


#endif