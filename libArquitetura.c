#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "libArquitetura.h"

void shiftLeft(uint8_t binario[], size_t tam) {
	for (int i = 0; i < tam-1; i++) {
		binario[i] = binario[i+1];
	}
	binario[tam-1] = 0;
}

void shiftRight(uint8_t binario[], size_t tam) {
	for (int i = tam-1; i > 0; i--) {
		binario[i] = binario[i-1];
	}
	binario[0] = 0;
}

// retorna array contendo a soma na primeira 
// posição e o carryOut na segunda
uint8_t * meioSomador(uint8_t a, uint8_t b) {
	uint8_t soma = a ^ b;
	uint8_t carryOut = a & b;
	uint8_t * result = (uint8_t *)malloc(sizeof(uint8_t)*2);
	result[0] = soma;
	result[1] = carryOut;
	return result;
}

uint8_t * somador1bit(uint8_t a, uint8_t b, uint8_t carryIn) {
	uint8_t * primeiraSoma = meioSomador(a,b);
	uint8_t * segundaSoma = meioSomador(carryIn, primeiraSoma[0]);
	uint8_t carryOut = primeiraSoma[1] | segundaSoma[1];
	uint8_t * result = (uint8_t *)malloc(sizeof(uint8_t)*2);
	result[0] = segundaSoma[0];
	result[1] = carryOut;
	return result;
}

// somador de n bits
// retorna array contendo a soma
// entradas são arrays que representam os números binários
uint8_t * somadorNbits(uint8_t a[], uint8_t b[], uint8_t carryIn, uint8_t n) {
	// tmp é usado para controle dos carries
	// e a soma de cada par de bits
	uint8_t * tmp = (uint8_t *)malloc(sizeof(uint8_t)*2);
	uint8_t * result = (uint8_t *)malloc(sizeof(uint8_t)*n);
	// carry in inicial e soma inicial valem 0
	tmp[0] = 0;
	tmp[1] = 0;
	for (int i = n-1; i >= 0; i--) {
		// soma bit a bit
		// tmp[0] armazena o resultado da soma
		// tmp[1] armazena o carry in
		tmp = somador1bit(a[i], b[i], tmp[1]);
		result[i] = tmp[0];
	}
	free(tmp);
	return result;
}

// junta dois arrays em um único binario
uint8_t * joinArrays(uint8_t parte1[], uint8_t parte2[], size_t tamParte) {
	uint8_t * result = (uint8_t *)malloc(sizeof(uint8_t)*tamParte*2);
	// add primeiro array
	for (int i = 0; i < tamParte; i++) 
		result[i] = parte1[i];	
	// add segundo array
	for (int i = 0; i < tamParte; i++) 
		result[i+tamParte] = parte2[i];
	return result;
}

// retorna parte de um array de inicio a inicio + qtd
uint8_t * splitArray(uint8_t binario[], uint8_t inicio, uint8_t qtd, size_t tam) {
	uint8_t * result = (uint8_t *)malloc(sizeof(uint8_t)*qtd);
	uint8_t k = 0;
	for (int i = inicio; i < (inicio + qtd) && i < tam; i++) {
		result[k++] = binario[i];
	}
	return result;
}

// printar elementos de um array
// que representa um número binário
void printarBinario(uint8_t binario[], size_t tam) {
	printf("[ ");
	for (int i = 0; i < tam; i++) 
		printf("%d ", binario[i]);
	printf("]");
}

// retorna valor decimal de um
// número binário representado por um array
int binarioToDecimal(uint8_t binario[], size_t tam) {
	int result = 0;
	int valorPosicional = 1;
	for (int i = tam-1; i >= 0; i--) {
		if (binario[i] == 1)
			result += valorPosicional;
		valorPosicional *= 2;
	}
	return result;
}

// retorna valor decimal de um número
// binário representado por uma string
int binarioStrToDecimal(char binario[]) {
	int result = 0;
	int valorPosicional = 1;
	size_t tam = strlen(binario);
	for (int i = tam-1; i >= 0; i--) {
		if (binario[i] == '1')
			result += valorPosicional;
		valorPosicional *= 2;
	}
	return result;
}

// retorna um array contendo um número binário
// sendo que cada posição do vetor contém um bit
// desse binário
uint8_t * lerBinario(size_t tam) {
	uint8_t * result = (uint8_t *) malloc(sizeof(uint8_t)*tam);
	char binarioDigitado[tam+1];

	printf("Digite o número binário: ");
	scanf("%s", binarioDigitado);

	// percorrer a string digitada de forma
	// a validar os caracteres: trocar caracteres
	// inválidos ou não digitados por 0
	uint8_t isBinInvalido = 0;

	for (int i = 0; i < tam; i++) {
		if (binarioDigitado[i] != '0' && binarioDigitado[i] != '1') {
			isBinInvalido = 1;
			binarioDigitado[i] = '0';
		}
		result[i] = numStrToInt(binarioDigitado[i]);
	}

	if (isBinInvalido)
		printf("\n *** Número inserido possui caracteres inválidos ou não possui todos os dígitos. Os caracteres faltantes ou inválidos serão substituídos por 0 ***\n");

	return result;
}

// retorna o valor hexadecimal de um caracter
// com base no seu valor ascii
// retorna -1 se o caracter for invalido
uint8_t getDecimalFromHexChar(char c) {
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
    uint8_t asciiC = c;
    uint8_t valorHexa = -1; 
    if (asciiC >= 48 && asciiC <= 58) {
        valorHexa = asciiC - 48;  
    } else if (asciiC >= 65 && asciiC <= 70) {
        valorHexa = asciiC - 55; 
    } else if (asciiC >= 97 && asciiC <= 102) {
        valorHexa = asciiC - 87; 
    }   
    return valorHexa;
}

// converter um caracter que represeta
// um número no seu inteiro correspondente
uint8_t numStrToInt(char c) {
	uint8_t asciiC = c;
	uint8_t retorno = -1;

    if (asciiC >= 48 && asciiC <= 58) {
        retorno = asciiC - 48;  
	}

	return retorno;
}
