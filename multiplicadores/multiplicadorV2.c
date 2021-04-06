#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"

uint8_t * multiplicadorNbitsV2(uint8_t * multiplicador, uint8_t * multiplicando, uint8_t palavra) {
	// o produto seriam 2 partes de tamanho palavra,
	// como se estivessem separadas
	uint8_t * produto = (uint8_t *) malloc(sizeof(uint8_t)*2*palavra);
	uint8_t controle = 0;
	uint8_t * primeiraMetadeDoProduto = NULL;

	printf("\n\tAlgoritmo do multiplicador versão 2:\n");
	
	// inicializar itens de produto
	printf("Inicializar o itens de produto com 0\n");
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

		// obter a primeira metade do array produto
		primeiraMetadeDoProduto = splitArray(produto, 0, palavra, 2*palavra);

		printf("Obter a primeira metade do array produto. Metade: ");
		printarBinario(primeiraMetadeDoProduto, palavra);
		printf("\n");
		
		printf("Bit menos significativo do multiplicador: %d\n", multiplicador[palavra-1]);
		if (multiplicador[palavra-1] == 1) {
			printf("Já que o bit menos significativo é 1:\n");
			// somar primeiraMetadeDoProduto com o multiplicando
			printf("  Somar a primeira metade do produto com o multiplicando.\n");

			primeiraMetadeDoProduto = somadorNbits(primeiraMetadeDoProduto,multiplicando,0, palavra);

			printf("  Resultado da soma: ");
			printarBinario(primeiraMetadeDoProduto, palavra);
			printf("\n");
		}
		
		// copiar primeiraMetadeDoProduto pra produto 
		for (size_t i = 0; i < palavra; i++) 
			produto[i] = primeiraMetadeDoProduto[i];
			
		printf("Fazer o shift right do produto e do multiplicador.\n");
		printf("  Após o shift:\n");

		shiftRight(produto, 2*palavra);
		shiftRight(multiplicador, palavra);

		printf("    Produto: ");
		printarBinario(produto, 2*palavra);
		printf("\n");
		printf("    Multiplicador: ");
		printarBinario(produto, palavra);
		printf("\n");

		controle++;
	}
	
	free(primeiraMetadeDoProduto);
	primeiraMetadeDoProduto = NULL;
	
	return produto;
}
