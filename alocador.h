/* Cabeçalho com a declaração das funções que seu gerenciador
 * de memória deve definir (implementar). Já possui outros
 * includes comumente necessários para sua implementação.
 * Portanto, no seu arquivo alocador.c, basta basta inserir a 
 * diretiva #include "alocador.h" no início do arquivo.
 * 
 * By.: Vandeir Eduardo
 */ 

// Include de outras funções comumente utilizadas
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

// Declaração das funções
int inicia_alocador();
int finalizar();
char *aloca(int);
int desaloca(char *);
