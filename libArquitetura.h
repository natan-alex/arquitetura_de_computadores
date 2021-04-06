#include <stdint.h>
#include <stddef.h>
#ifndef LIB_ARQUITETURA_H
#define LIB_ARQUITETURA_H

// faz o shift left de um número binário representado
// por um array
void shiftLeft(uint8_t binario[], size_t tam);

// faz o shift right de um número binário representado
// por um array
void shiftRight(uint8_t binario[], size_t tam);

// retorna binario contendo a soma na primeira 
// posição e o carryOut na segunda
uint8_t * meioSomador(uint8_t a, uint8_t b);

uint8_t * somador1bit(uint8_t a, uint8_t b, uint8_t carryIn);

// somador de n bits
// retorna array contendo a soma
// entradas são arrays que representam os números binários
uint8_t * somadorNbits(uint8_t a[], uint8_t b[], uint8_t carryIn, uint8_t n);

// junta dois arrays em um único binario
uint8_t * joinArrays(uint8_t parte1[], uint8_t parte2[], size_t tamParte);

// retorna parte de um array de inicio a inicio + qtd
uint8_t * splitArray(uint8_t binario[], uint8_t inicio, uint8_t qtd, size_t tam);

// printar elementos de um array
// que representa um número binário
void printarBinario(uint8_t binario[], size_t tam);

// retorna valor decimal de um
// número binário representado por um array
int binarioToDecimal(uint8_t binario[], size_t tam);

// retorna valor decimal de um número
// binário representado por uma string
int binarioStrToDecimal(char binario[]);

// retorna um array contendo um número binário
// sendo que cada posição do vetor contém um bit
// desse binário
uint8_t * lerBinario(size_t tam);

// retorna o valor hexadecimal de um caracter
// com base no seu valor ascii
// retorna -1 se o caracter for invalido
uint8_t getDecimalFromHexChar(char c);

// converter um caracter que represeta
// um número no seu inteiro correspondente
uint8_t numStrToInt(char c);

#endif
