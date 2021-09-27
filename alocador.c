#include "alocador.h"

const int MEMORIA_4KB = 4096;

typedef struct posicao
{
    char *ponteiro;
    int indice;
    int tamanho;
    struct posicao *proxima;
} posicao;

posicao *inicio;

char *memoria = NULL;

int inicia_alocador()
{
    memoria = mmap(NULL, MEMORIA_4KB, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if(memoria == MAP_FAILED)
       return 1;
    else
       return 0;
}

int finalizar()
{
    if (memoria == NULL || munmap(memoria, MEMORIA_4KB) == -1)
       return 1;
    else
       return 0;
}

char *aloca(int quantidade)
{
    if (memoria == NULL)
        return NULL;

    int indice = 0;

    if (inicio == NULL)
    {
        posicao nova = { &memoria[indice], indice, quantidade, NULL };
        inicio = &nova;
        
        return inicio->ponteiro;
    }
    else
    {
        posicao *atual = inicio;
        posicao *proxima;

        while (atual->proxima != NULL)
        {
            proxima = atual->proxima;

            if (atual->indice + atual->tamanho != atual->proxima->indice && atual->proxima->indice - atual->indice + atual->tamanho >= quantidade)
            {
                indice = atual->indice + atual->tamanho;
                break;
            }

            atual = atual->proxima;
        }
        
        posicao nova = { &memoria[indice], indice, quantidade, NULL };
        (&nova)->proxima = proxima;
        atual->proxima = &nova;

        return (&nova)->ponteiro;
    }

    return NULL;
}

int desaloca(char * ponteiro)
{
    if (inicio == NULL)
        return 1;

    posicao *anterior;
    posicao *atual = inicio;
    posicao *proxima;

    while (atual->proxima != NULL)
    {
        proxima = atual->proxima;

        if (atual->ponteiro == ponteiro)
            break;
        
        anterior = atual;
        atual = proxima;
    };
        
    if (munmap(ponteiro, atual->tamanho) == -1)
        return 1;

    if (anterior != NULL)
        anterior->proxima = proxima;
    else
        inicio = proxima;

    return 0;
}