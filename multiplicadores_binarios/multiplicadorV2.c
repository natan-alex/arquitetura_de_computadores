#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"

BinaryNumber * multiplierNBitsV2(BinaryNumber * multiplier, BinaryNumber * multiplicand, uint8_t word) {
	BinaryNumber * product = create_new_binary_number(2*word);
	BinaryNumber * firstHalfOfProduct = create_new_binary_number(word);

	printf("\n\tAlgoritmo do multiplicador versão 2:\n");
	
	printf("Inicializar o itens de produto com 0\n");
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

		firstHalfOfProduct = getASliceOfABinaryNumber(product, 0, word);

		printf("Obter a primeira metade do array produto. Metade: ");
		showBinaryNumber(firstHalfOfProduct);
		printf("\n");
		
		printf("Bit menos significativo do multiplicador: %d\n", multiplier->bits[word-1]);
		if (multiplier->bits[word-1] == 1) {
			printf("Já que o bit menos significativo é 1:\n");
			printf("  Somar a primeira metade do produto com o multiplicando.\n");

			firstHalfOfProduct = getSumOfNBits(firstHalfOfProduct, multiplicand, 0)->sum;

			printf("  Resultado da soma: ");
			showBinaryNumber(firstHalfOfProduct);
			printf("\n");
		}
		
		for (int i = 0; i < word; i++) 
			product->bits[i] = firstHalfOfProduct->bits[i];
			
		printf("Fazer o shift right do produto e do multiplicador.\n");
		printf("  Após o shift:\n");

		doInPlaceShiftRight(product);
		doInPlaceShiftRight(multiplier);

		printf("    Produto: ");
		showBinaryNumber(product);
		printf("\n");
		printf("    Multiplicador: ");
		showBinaryNumber(multiplier);
		printf("\n");
	}
	
	free(firstHalfOfProduct->bits);
	free(firstHalfOfProduct);
	firstHalfOfProduct = NULL;
	
	return product;
}
