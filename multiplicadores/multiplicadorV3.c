#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"

uint8_t * multiplicadorNbitsV3(uint8_t * multiplicador, uint8_t * multiplicando, uint8_t palavra) {
	// o produto seriam 2 partes de tamanho palavra,
	// como se estivessem separadas
	uint8_t * produto = (uint8_t *) malloc(sizeof(uint8_t)*2*palavra);
	uint8_t controle = 0;
	uint8_t * primeiraMetadeDoProduto;

	printf("\n\tAlgoritmo do multiplicador versão 3:\n");
	
	// inicializar itens da metade da esquerda de produto
	printf("Inicializar o itens de produto com 0\n");
	for (size_t i = 0; i < palavra; i++)
		produto[i] = 0;
		
	// copiar multiplicador para a metade da direita de produto
	printf("Copiar o multiplicador para a segunda metade do produto.\n");
	for (size_t i = 0; i < palavra; i++)
		produto[i+palavra] = multiplicador[i];
		
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

		primeiraMetadeDoProduto = splitArray(produto, 0, palavra, 2*palavra);
		
		printf("Obter a primeira metade do array produto. Metade: ");
		printarBinario(primeiraMetadeDoProduto, palavra);
		printf("\n");

		printf("Bit menos significativo do produto: %d\n", produto[2*palavra-1]);
		if (produto[2*palavra-1] == 1) {
			// somar primeiraMetadeDoProduto com o multiplicando
			printf("Já que o bit menos significativo é 1:\n");
			printf("  Somar a primeira metade do produto com o multiplicando.\n");

			primeiraMetadeDoProduto = somadorNbits(primeiraMetadeDoProduto,multiplicando,0, palavra);

			printf("  Resultado da soma: ");
			printarBinario(primeiraMetadeDoProduto, palavra);
			printf("\n");
		}
		
		// copiar primeiraMetadeDoProduto pra produto 
		for (size_t i = 0; i < palavra; i++) 
			produto[i] = primeiraMetadeDoProduto[i];
			
		printf("Fazer o shift right do produto.\n");
		printf("  Após o shift:\n");

		shiftRight(produto, 2*palavra);

		printf("    Produto: ");
		printarBinario(produto, 2*palavra);
		printf("\n");

		controle++;
	}
	
	free(primeiraMetadeDoProduto);
	primeiraMetadeDoProduto = NULL;
	
	return produto;
}
