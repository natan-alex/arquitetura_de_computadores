#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../libArquitetura.h"
#include "multiplicadorV1.h"
#include "multiplicadorV2.h"
#include "multiplicadorV3.h"

#define LIMITE_DE_BITS 10

uint8_t lerNumBits() {
	int num;
	scanf("%d", &num);
	while (num <= 0 || num > LIMITE_DE_BITS) {
		printf("Número inválido (negativo, igual a 0 ou maior que %d). ", LIMITE_DE_BITS);
		printf("Digite novamente: "); 
		scanf("%d", &num);
	}
	return (uint8_t) num;
}

int main(int argc, char ** argv) {
	uint8_t palavra, op;
	uint8_t * multiplicador, * multiplicando;
	uint8_t * produto;
	int produtoEmDecimal = 0;
	int multiplicadorEmDecimal = 0;
	int multiplicandoEmDecimal = 0;
	int valorEsperado = 0;
	printf("MULTIPLICADORES BINÁRIOS EM C\n");
	do {
		printf("\n\tMENU MULTIPLICADORES BINÁRIOS\n");
		printf("[1] - usar multiplicador versão 1\n");
		printf("[2] - usar multiplicador versão 2\n");
		printf("[3] - usar multiplicador versão 3\n");
		printf("[0] - sair\n");
		printf("  Opção: ");
		scanf("%hhu", &op);

		if (op >= 1 && op <= 3) {
			printf("\nNúmero de bits do multiplicador: ");
			palavra = lerNumBits();
			printf("\nMultiplicador: \n");
			multiplicador = lerBinario(palavra);
			printf("Valor do multiplicador ");
			printarBinario(multiplicador, palavra);
			multiplicadorEmDecimal = binarioToDecimal(multiplicador, palavra);
			printf(" = %d em decimal\n", multiplicadorEmDecimal);
			printf("\nSobre o multiplicando:\n");
			if (op == 1) {
				printf(" * Na primeira versão ele possui o dobro de bits do multiplicador\n");
				printf(" ** Se atente ao valor que será inserido pois pode haver overflow **\n");
				multiplicando = lerBinario(2*palavra);
				printf("Valor do multiplicando ");
				printarBinario(multiplicando, 2*palavra);
				multiplicandoEmDecimal = binarioToDecimal(multiplicando, 2*palavra);
				printf(" = %d em decimal\n", multiplicandoEmDecimal);
				produto = multiplicadorNbitsV1(multiplicador, multiplicando, palavra);
			} else if (op == 2) {
				printf(" * Na segunda versão ele possui o mesmo número de bits do multiplicador\n");
				multiplicando = lerBinario(palavra);
				printf("Valor do multiplicando ");
				printarBinario(multiplicando, palavra);
				multiplicandoEmDecimal = binarioToDecimal(multiplicando, palavra);
				printf(" = %d em decimal\n", multiplicandoEmDecimal);
				produto = multiplicadorNbitsV2(multiplicador, multiplicando, palavra);
			} else if (op == 3) {
				printf(" * Na terceira versão ele possui o mesmo número de bits do multiplicador\n");
				multiplicando = lerBinario(palavra);
				printf("Valor do multiplicando ");
				printarBinario(multiplicando, palavra);
				multiplicandoEmDecimal = binarioToDecimal(multiplicando, palavra);
				printf(" = %d em decimal\n", multiplicandoEmDecimal);
				produto = multiplicadorNbitsV3(multiplicador, multiplicando, palavra);
			}
			printf("\n\nProduto final entre %d e %d: ", multiplicadorEmDecimal, multiplicandoEmDecimal);
			printarBinario(produto, palavra*2);
			produtoEmDecimal = binarioToDecimal(produto, 2*palavra);
			printf(" = %d em decimal\n", produtoEmDecimal);
			valorEsperado = multiplicandoEmDecimal * multiplicadorEmDecimal;
			printf("Houve overflow? ");
			if (produtoEmDecimal < valorEsperado) 
				printf("Sim. O valor esperado era %d\n", valorEsperado);
			else
				printf("Não\n");
			printf("\n");
		} else {
			if (op == 0)
				printf("\nPrograma encerrado.\n");
			else
				printf("Opção inválida.\n");
		}
	} while (op != 0);

	return EXIT_SUCCESS;
}

