#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"
#include "multiplicadorV1.h"
#include "multiplicadorV2.h"
#include "multiplicadorV3.h"

#define MAX_BINARY_SIZE 10

uint8_t readAnValidateTheBinarySize() {
	uint8_t num;
	scanf("%hhd", &num);
	while (num <= 0 || num > MAX_BINARY_SIZE) {
		printf("Número inválido (negativo, igual a 0 ou maior que %d). ", MAX_BINARY_SIZE);
		printf("Digite novamente: "); 
		scanf("%hhd", &num);
	}
	return num;
}

int main(int argc, char ** argv) {
	uint8_t word_size, operation;
	BinaryNumber * multiplier, * multiplicand;
	BinaryNumber * product;
	int product_decimal_value = 0;
	int multiplier_decimal_value = 0;
	int multiplicand_decimal_value = 0;
	int waited_value = 0;

	printf("MULTIPLICADORES BINÁRIOS EM C\n");

	do {
		printf("\n\tMENU MULTIPLICADORES BINÁRIOS\n");
		printf("[1] - usar multiplicador versão 1\n");
		printf("[2] - usar multiplicador versão 2\n");
		printf("[3] - usar multiplicador versão 3\n");
		printf("[0] - sair\n");
		printf("  Opção: ");
		scanf("%hhu", &operation);

		if (operation >= 1 && operation <= 3) {
			printf("\nNúmero de bits do multiplicador: ");
			word_size = readAnValidateTheBinarySize();
			printf("\nMultiplicador: \n");
			multiplier = readBinaryNumber(word_size);
			printf("Valor do multiplicador ");
			showBinaryNumber(multiplier);
			multiplier_decimal_value = getDecimalValue(multiplier);
			printf(" = %d em decimal\n", multiplier_decimal_value);
			printf("\nSobre o multiplicando:\n");
			if (operation == 1) {
				printf(" * Na primeira versão ele possui o dobro de bits do multiplicador\n");
				printf(" ** Se atente ao valor que será inserido pois pode haver overflow **\n");
				multiplicand = readBinaryNumber(2*word_size);
				printf("Valor do multiplicador ");
				showBinaryNumber(multiplicand);
				multiplicand_decimal_value = getDecimalValue(multiplicand);
				printf(" = %d em decimal\n", multiplicand_decimal_value);
				product = multiplierNBitsV1(multiplier, multiplicand, word_size);
			} else if (operation == 2) {
				printf(" * Na segunda versão ele possui o mesmo número de bits do multiplicador\n");
				multiplicand = readBinaryNumber(word_size);
				printf("Valor do multiplicador ");
				showBinaryNumber(multiplicand);
				multiplicand_decimal_value = getDecimalValue(multiplicand);
				printf(" = %d em decimal\n", multiplicand_decimal_value);
				product = multiplierNBitsV2(multiplier, multiplicand, word_size);
			} else if (operation == 3) {
				printf(" * Na terceira versão ele possui o mesmo número de bits do multiplicador\n");
				multiplicand = readBinaryNumber(word_size);
				printf("Valor do multiplicador ");
				showBinaryNumber(multiplicand);
				multiplicand_decimal_value = getDecimalValue(multiplicand);
				printf(" = %d em decimal\n", multiplicand_decimal_value);
				product = multiplierNBitsV3(multiplier, multiplicand, word_size);
			}
			printf("\n\nProduto final entre %d e %d: ", multiplier_decimal_value, multiplicand_decimal_value);
			showBinaryNumber(product);
			product_decimal_value = getDecimalValue(product);
			printf(" = %d em decimal\n", product_decimal_value);
			waited_value = multiplicand_decimal_value * multiplier_decimal_value;
			printf("Houve overflow? ");
			if (product_decimal_value < waited_value) 
				printf("Sim. O valor esperado era %d\n", waited_value);
			else
				printf("Não\n");
			printf("\n");
		} else {
			if (operation == 0) {
				printf("\nPrograma encerrado.\n");
                free(multiplier);
                free(multiplicand);
                free(product);
            } else {
				printf("Opção inválida.\n");
            }
		}
	} while (operation != 0);

	return EXIT_SUCCESS;
}

