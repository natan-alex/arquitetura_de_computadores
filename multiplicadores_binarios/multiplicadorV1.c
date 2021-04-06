#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"
#include "multiplicadorV1.h"

uint8_t * multiplicadorNbitsV1(uint8_t * multiplicador, uint8_t * multiplicando, uint8_t palavra) {
	// multiplicador possui palavra bits
	// multiplicando possui 2*palavra bits
	// produto possui 2*palavra bits
	uint8_t * produto = (uint8_t *) malloc(sizeof(uint8_t)*2*palavra);
	uint8_t controle = 0;
	
	printf("\n\tAlgoritmo do multiplicador versão 1:\n");
	
	printf("Inicializar os itens de produto com 0\n");
	// inicializar itens de produto
	for (size_t i = 0; i < 2*palavra; i++)
		produto[i] = 0;
		
	while (controle < palavra) {
		printf("\n  %dª iteração:\n", controle+1);
		printf("Produto: ");
		printarBinario(produto, 2*palavra);
		printf("\n");
		printf("Multiplicador: ");
		printarBinario(multiplicador, palavra);
		printf("\n");
		printf("Multiplicando: ");
		printarBinario(multiplicando, 2*palavra);
		printf("\n");
	
		printf("Bit menos significativo do multiplicador: %d\n", multiplicador[palavra-1]);
		if (multiplicador[palavra-1] == 1) {
			printf("Já que o bit menos significativo é 1:\n");
			// somar produto com o multiplicando
			printf("  Somar o produto e o multiplicando.\n");

			produto = somadorNbits(produto, multiplicando, 0, 2*palavra);

			printf("  Resultado da soma: ");
			printarBinario(produto, 2 * palavra);
			printf("\n");
		}
		
		printf("Fazer o shift right do multiplicador e o shift left do multiplicando.\n");

		shiftLeft(multiplicando, 2*palavra);
		shiftRight(multiplicador, palavra);

		printf("  Após o shift:\n");

		printf("    Multiplicador: ");
		printarBinario(multiplicador, palavra);
		printf("\n");
		printf("    Multiplicando: ");
		printarBinario(multiplicando, 2* palavra);
		printf("\n");

		controle++;
	}
	
	return produto;
}
