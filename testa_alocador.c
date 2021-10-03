/* Programinha para testar seu gerenciador de memória.
 * Aloca, preenche a região de memória com caracteres e
 * depois compara com strings de referência. Veja maiores
 * explicações no decorrer do código.
 * 
 * By.: Vandeir Eduardo
 */

#include "alocador.h"

int main()
{
	printf("Iniciando testes básicos...\n\n");

	//Chama a função que inicializa o gerenciador de memória
	if (inicia_alocador() != 0) {
		//se não retornar zero, ocorreu algum erro
	  	printf("Teste básico falhou! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum erro na função de inicialização!\n");
		return 1;	
	}

	//Aloca duas áreas de 512 bytes
	char *str = aloca(512);
	char *str2 = aloca(512);

	//Testa alocação
	if (str == NULL || str2 == NULL) {
		//se str contém NULL, houve problemas na alocação
	  	printf("Teste básico falhou! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum problema na alocação de memória. ****\n");
		printf("**** Não foi possível alocar duas áreas de 512 bytes ****\n");
		return 1;
	}

	strcpy(str, "Olá mundo!");
	if (strcmp("Olá mundo!", str)) {
  		printf("Teste básico falhou! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Ocorreu algum problema no armazenamento da string 'Olá mundo!' ****\n");
	  	return 1;
	} else {
	 	printf("Teste básico de armazenamento de string bem sucedido!\n");
	}

	//Libera áreas iniciais alocadas e testa sucesso na liberação
	if (desaloca(str) != 0 || desaloca(str2) != 0) {
  		printf("Teste básico falhou! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Ocorreu algum problema na liberação das áreas alocadas. ****\n");
	  	return 1;
	}
	
	printf("\nIniciando testes avançados...\n\n");

	/*** teste 1 ****/
	//Aloca 4 áreas de 1024 bytes e as preenche com letras
	//Depois compara com 4 strings de referência

	//Gerando strings de comparação e preenchendo com letras
	char stringA[1024], stringB[1024], stringC[1024], stringD[1024], stringX[1024];
	for(int i = 0; i < 1023; i++) {
		stringA[i] = 'a';
		stringB[i] = 'b';
		stringC[i] = 'c';
		stringD[i] = 'd';
		stringX[i] = 'x';
	}
	//Preenche a última posição da string com o caracter '\0' que indica o final da string
	stringA[1023] = stringB[1023] = stringC[1023] = stringD[1023] = stringX[1023] = '\0';

	//Faz quatro alocações de 1024 bytes
	char *strA = aloca(1024);
	char *strB = aloca(1024);
	char *strC = aloca(1024);
	char *strD = aloca(1024);

	//Testa alocações
	if (strA == NULL || strB == NULL || strC == NULL || strD == NULL)  {
		//se str contém NULL, houve problemas na alocação
		printf("Não passou no teste 1! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum problema na alocação de memória. ****\n");
		printf("**** Não foi possível alocar quatro áreas de 1024 bytes. ****\n");
		return 1;
	}

	//Preenche áreas alocadas com letras
	for (int i = 0; i < 1023; i++) {
		strA[i] = 'a';
		strB[i] = 'b';
		strC[i] = 'c';
		strD[i] = 'd';
	}
	//Preenche última posição com o caracter indicador de final de string
	strA[1023] = strB[1023] = strC[1023] = strD[1023] = '\0';

	//Compara as strings de referência com as strings armazenadas nas áreas alocadas
	//Se strcmp retornar um número diferente de zero, há diferença nas strings
	if (strcmp(stringA, strA) == 0 && strcmp(stringB, strB) == 0 && 
	   strcmp(stringC, strC) == 0 && strcmp(stringD, strD) == 0) {
		printf("Teste avançado 1 bem sucedido: alocação de 4 áreas de 1024 bytes.\n");
	} else {
		printf("Não passou no teste 1! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Há diferença nas strings armazenadas: A: %d, B: %d, C: %d, D: %d ****\n", 
		        strcmp(stringA, strA), strcmp(stringB, strB), 
				strcmp(stringC, strC), strcmp(stringD, strD));
		return 1;
	}

	/**** Teste 2 ****/
	//Libera uma área alocada de 1024 bytes e depois aloca novamente

	//Libera área alocada da string C
	//Libera área alocada e testa sucesso na liberação
	if (desaloca(strC) != 0) {
		printf("Não passou no teste 2! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Ocorreu algum problema na liberação da área alocada. ****\n");
	  	return 1;
	}

	//Faz uma nova alocação do mesmo tamanho (1024 bytes)
	char *strX = aloca(1024);

	//Testa alocação
	if (strX == NULL)  {
		//se str contém NULL, houve problemas na alocação
		printf("Não passou no teste 2! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum problema na alocação de memória ****.\n");
		printf("**** Não foi possível alocar uma nova área de 1024 bytes. ****\n");
		return 1;
	}

	//Preenche área alocada
	for (int i = 0; i < 1023; i++) {
		strX[i] = 'x';
	}
	strX[1023] = '\0';

	//Compara stringX com área alocada e preenchida
	if (strcmp(stringX, strX) == 0) {
		printf("Teste avançado 2 bem sucedido: desalocação seguida de nova alocação de 1024 bytes.\n");
	} else {
		printf("Não passou no teste 2! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Há diferença na string armazenada: X: %d ****\n", strcmp(stringX, strX));
		return 1;
	}

	/*** Teste 3 ***/
	//Libera uma área alocada de 1024 bytes e faz duas novas alocações de 512 bytes
	
	//Cria duas strings de referência com 512 bytes e as preenche
	char stringY[512], stringZ[512];
	for (int i = 0; i < 511; i++) {
		stringY[i] = 'y';
		stringZ[i] = 'z';
	}
	stringY[511] = stringZ[511] = '\0';

	//Libera área da strB (1024 bytes)
	if (desaloca(strB) != 0) {
		printf("Não passou no teste 3! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Ocorreu algum problema na liberação da área alocada. ****\n");
	  	return 1;
	}

	//Aloca duas áreas de 512 bytes
	char *strY = aloca(512);
	char *strZ = aloca(512);

	//Testa alocações
	if (strY == NULL || strZ == NULL)  {
		//se str contém NULL, houve problemas na alocação
		printf("Não passou no teste 3! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum problema na alocação de memória. ****\n");
		printf("**** Não foi possível alocar duas áreas de 512 bytes. ****\n");
		return 1;
	}

	//Preenche áreas alocadas
	for(int i = 0; i < 511; i++) {
		strY[i] = 'y';
		strZ[i] = 'z';
	}
	strY[511] = strZ[511] = '\0';

	if(strcmp(stringY, strY) == 0 && strcmp(stringZ, strZ) == 0) {
		printf("Teste avançado 3 bem sucedido: desalocação seguida de duas alocações menores (512 bytes).\n");
	} else {
		printf("Não passou no teste 3! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Há diferença nas strings armazenadas: Y: %d, Z: %d ****\n", 
		       strcmp(stringY, strY), strcmp(stringZ, strZ));
		return 1;
	}

	/*** Teste 4 ***/
	//Libera duas áreas alocadas de 512 bytes e faz alocação de uma área de 1024
	//Testa fusão de áreas livres adjacentes

	//Libera duas áreas alocadas de 512 bytes
	if (desaloca(strZ) != 0 || desaloca(strY) != 0) {
		printf("Não passou no teste 4! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Ocorreu algum problema na liberação das áreas alocadas. ****\n");
	  	return 1;
	}

	//Aloca uma nova área de 1024 bytes
	strY=aloca(1024);

	//Testa alocação
	if (strY == NULL)  {
		//se str contém NULL, houve problemas na alocação
		printf("Não passou no teste 4! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum problema na alocação de memória. ****\n");
		printf("**** Não foi possível alocar área de 1024 bytes. ****\n");
		return 1;
	}

	//Preenche área alocada
	for (int i = 0; i < 1023; i++) {
		strY[i] = 'x';
	}
	strY[1023] = '\0';
	
	if (strcmp(stringX, strY) == 0) {
		printf("Teste avançado 4 bem sucedido: fusão de duas áreas livres adjacentes (512 bytes), seguida de nova alocação de 1024 bytes.\n");
	} else {
		printf("Não passou no teste 4! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Há diferença na string armazenada: Y: %d ****\n", strcmp(stringX, strY));
		return 1;
	}

	/*** Teste 5 ***/
	//Libera duas áreas alocadas de 1024 bytes e aloca uma nova de 2048 bytes
	//Testa fusão de áreas adjacentes livres

	//Libera duas áreas alocadas de 1024 bytes
	if (desaloca(strX) != 0 || desaloca(strY) != 0) {
		printf("Não passou no teste 5! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Ocorreu algum problema na liberação das áreas alocadas. ****\n");
	  	return 1;
	}

	strX= aloca(2048);

	//Testa alocação
	if (strX == NULL)  {
		//se str contém NULL, houve problemas na alocação
		printf("Não passou no teste 5! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum problema na alocação de memória. ****\n");
		printf("**** Não foi possível alocar área de 2048 bytes. ****\n");
		return 1;
	}

	//Cria string de referência e a preenche
	//Também já tenta preecher a área alocada
	char  stringM[2048];
	for (int i=0; i<2047; i++) {
		strX[i]=stringM[i]='z';
	}
	strX[2047]=stringM[2047]='\0';

	if (!strcmp(stringM, strX)) {
		printf("Teste avançado 5 bem sucedido: fusão de duas áreas livres adjacentes (1024 bytes), seguida de nova alocação de 2048 bytes.\n");
	} else {
		printf("Não passou no teste 5! :-( (Linha: %d)\n", __LINE__);
	  	printf("**** Há diferença na string armazenada: X: %d ****\n", strcmp(stringM, strX));
		return 1;
	}
	
	if (finalizar() != 0) {
		//se não retornar zero, ocorreu algum erro
	  	printf("Teste básico falhou! :-( (Linha: %d)\n", __LINE__);
		printf("**** Ocorreu algum erro na função de finalização!\n");
		return 1;
	}

	printf("\n************************\n");
	printf("Parabéns! Seu gerenciador de memória passou em todos os testes!\n");
	printf("Bom trabalho! :-)))\n");
	printf("************************\n");

	return 0;
}
