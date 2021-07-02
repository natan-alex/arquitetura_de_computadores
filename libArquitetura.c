#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#include "libArquitetura.h"

BinaryNumber * create_new_binary_number(uint8_t number_of_bits) {
    BinaryNumber * binary = (BinaryNumber *) malloc(sizeof(BinaryNumber));

    binary->bits = (uint8_t *) malloc(sizeof(uint8_t) * number_of_bits);
    binary->number_of_bits = number_of_bits;

    return binary;
}

void doInPlaceShiftLeft(BinaryNumber * binary) {
	for (int i = 0; i < binary->number_of_bits; i++) {
        binary->bits[i] = binary->bits[i+1];
	}

    binary->bits[binary->number_of_bits-1] = 0;
}

void doInPlaceShiftRight(BinaryNumber * binary) {
	for (int i = binary->number_of_bits; i > 0; i--) {
        binary->bits[i] = binary->bits[i-1];
	}

    binary->bits[0] = 0;
}

SumResultOf1BitOperation * getHalfSum(uint8_t first_bit, uint8_t second_bit) {
    SumResultOf1BitOperation * result = (SumResultOf1BitOperation *) malloc(sizeof(SumResultOf1BitOperation));

    result->sum = first_bit ^ second_bit;
    result->carry_out = first_bit & second_bit;

	return result;
}

SumResultOf1BitOperation * getSumOf1Bit(uint8_t first_bit, uint8_t second_bit, uint8_t carry_in) {
	SumResultOf1BitOperation * first_half_sum = getHalfSum(first_bit, second_bit);
	SumResultOf1BitOperation * second_half_sum = getHalfSum(carry_in, first_half_sum->sum);
    SumResultOf1BitOperation * result = (SumResultOf1BitOperation *) malloc(sizeof(SumResultOf1BitOperation));

    result->sum = second_half_sum->sum;
    result->carry_out = first_half_sum->carry_out | second_half_sum->carry_out;

    free(first_half_sum);
    free(second_half_sum);

	return result;
}

SumResultOfNBitsOperation * getSumOfNBits(BinaryNumber * first, BinaryNumber * second, uint8_t carry_in) {
    if (first->number_of_bits != second->number_of_bits) {
        printf("The sum cannot be done because the numbers do not have the same number of bits.\n");
        return NULL;
    }

	SumResultOf1BitOperation * temporary = (SumResultOf1BitOperation *) malloc(sizeof(SumResultOf1BitOperation));
	SumResultOfNBitsOperation * result = (SumResultOfNBitsOperation *) malloc(sizeof(SumResultOfNBitsOperation));

	result->sum = create_new_binary_number(first->number_of_bits);
    
    temporary->sum = 0;
    temporary->carry_out = 0;

	for (int i = first->number_of_bits; i >= 0; i--) {
		temporary = getSumOf1Bit(first->bits[i], second->bits[i], temporary->carry_out);
		result->sum->bits[i] = temporary->sum;
	}

	result->carry_out = temporary->carry_out;
	free(temporary);

	return result;
}

BinaryNumber * getNewBinaryByJoiningTwoBinaryNumbers(BinaryNumber * first, BinaryNumber * second) {
	BinaryNumber * result = create_new_binary_number(first->number_of_bits + second->number_of_bits);

	for (int i = 0; i < first->number_of_bits; i++) 
		result->bits[i] = first->bits[i];

	for (int i = 0; i < second->number_of_bits; i++) 
		result->bits[i+second->number_of_bits] = second->bits[i];

	return result;
}

BinaryNumber * getASliceOfABinaryNumber(BinaryNumber * binary, uint8_t index_of_first_bit, uint8_t slice_length) {
	BinaryNumber * result = create_new_binary_number(slice_length);
	uint8_t where_insert_in_result = 0;

	for (int i = index_of_first_bit; i < (index_of_first_bit + slice_length) && i < binary->number_of_bits; i++) {
		result->bits[where_insert_in_result++] = binary->bits[i];
	}

	return result;
}

void showBinaryNumber(BinaryNumber * binary) {
	printf("[ ");

	for (int i = 0; i < binary->number_of_bits; i++) 
		printf("%d ", binary->bits[i]);

	printf("]");
}

int getDecimalValue(BinaryNumber * binary) {
	int result = 0;
	int positional_value = 1;

	for (int i = binary->number_of_bits-1; i >= 0; i--) {
		if (binary->bits[i] == 1)
			result += positional_value;
		positional_value *= 2;
	}

	return result;
}

int getDecimalValueOfABinaryNumberRepresentedByAString(char binary[]) {
	int result = 0;
	int positional_value = 1;
	size_t binary_length = strlen(binary);

	for (int i = binary_length-1; i >= 0; i--) {
		if (binary[i] == '1')
			result += positional_value;
		positional_value *= 2;
	}

	return result;
}

BinaryNumber * readBinaryNumber(uint8_t number_of_bits) {
	BinaryNumber * result = create_new_binary_number(number_of_bits);
	char binary_as_string[number_of_bits+1];

	printf("Digite o número binário: ");
	scanf("%s", binary_as_string);

	uint8_t isBinaryInvalid = 0;
	for (int i = 0; i < number_of_bits; i++) {
		if (binary_as_string[i] == '0') { 
            result->bits[i] = 0;
		} else if (binary_as_string[i] == '1') {
            result->bits[i] = 1;
        } else {
			isBinaryInvalid = 1;
            result->bits[i] = 0;
		}
	}

	if (isBinaryInvalid)
		printf("\n *** Número inserido possui caracteres inválidos ou não possui todos os dígitos. Os caracteres faltantes ou inválidos serão substituídos por 0 ***\n");

	return result;
}

uint8_t getDecimalValueOfAHexChar(char c) {
    /*  
     * Char     Valor ascii
     * 0   ->   48
     * 1   ->   49
     * 2   ->   50
     * ...
     * 9   ->   58
     * A   ->   65
     * B   ->   66
     * ...
     * F   ->   70
     * a   ->   97
     * b   ->   98
     * ...
     * f   ->   102
     */
    uint8_t ascii_value_of_the_char = c;
    uint8_t hex_value = -1; 

    if (ascii_value_of_the_char >= 48 && ascii_value_of_the_char <= 58) {
        hex_value = ascii_value_of_the_char - 48;  
    } else if (ascii_value_of_the_char >= 65 && ascii_value_of_the_char <= 70) {
        hex_value = ascii_value_of_the_char - 55; 
    } else if (ascii_value_of_the_char >= 97 && ascii_value_of_the_char <= 102) {
        hex_value = ascii_value_of_the_char - 87; 
    }   

    return hex_value;
}
