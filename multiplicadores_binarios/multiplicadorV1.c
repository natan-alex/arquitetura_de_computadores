#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"
#include "multiplicadorV1.h"

BinaryNumber * multiplierNBitsV1(BinaryNumber * multiplier, BinaryNumber * multiplicand, uint8_t word) {
	// multiplier possui word bits
	// multiplicand possui 2*word bits
	// product possui 2*word bits

	BinaryNumber * product = create_new_binary_number(2*word);
	
	printf("\n\tAlgoritmo do multiplicador versão 1:\n");
	printf("Inicializar os itens de produto com 0\n");

	for (int i = 0; i < 2*word; i++)
		product->bits[i] = 0;
		
    for (int i = 0; i < word; i++) {
		printf("\n  %dª iteração:\n", i+1);
		printf("Produto: ");
		showBinaryNumber(product);
		printf("\n");
		printf("Multiplicador: ");
		showBinaryNumber(multiplier);
		printf("\n");
		printf("Multiplicando: ");
		showBinaryNumber(multiplicand);
		printf("\n");
	
		printf("Bit menos significativo do multiplicador: %d\n", multiplier->bits[word-1]);
		if (multiplier->bits[word-1] == 1) {
			printf("Já que o bit menos significativo é 1:\n");
			printf("  Somar o produto e o multiplicando.\n");

			product = getSumOfNBits(product, multiplicand, 0)->sum;

			printf("  Resultado da soma: ");
			showBinaryNumber(product);
			printf("\n");
		}
		
		printf("Fazer o shift right do multiplicador e o shift left do multiplicando.\n");

		doInPlaceShiftLeft(multiplicand);
		doInPlaceShiftRight(multiplier);

		printf("  Após o shift:\n");

		printf("    Multiplicador: ");
		showBinaryNumber(multiplier);
		printf("\n");
		printf("    Multiplicando: ");
		showBinaryNumber(multiplicand);
		printf("\n");
	}
	
	return product;
}
