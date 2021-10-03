#include "alocador.h"

const int MEMORIA_4KB = 4096;

typedef struct posicao
{
    char *ponteiro;
    int tamanho;
} posicao;

char *memoria = NULL;
posicao posicoes[4096];

int inicia_alocador()
{
    memoria = mmap(NULL, MEMORIA_4KB, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if(memoria == MAP_FAILED)
       return 1;
    else
       return 0;
}

char *aloca(int quantidade)
{
    if (memoria == NULL)
        return NULL;

    int indice = MEMORIA_4KB;

    for (int i = 0; i < MEMORIA_4KB; i++)
    {
        int tamanhoAtual = i + posicoes[i].tamanho;
        int indiceProxima = -1;

        for (int j = tamanhoAtual; j <= MEMORIA_4KB; j++)
        {
            if (posicoes[j].ponteiro != NULL || j == MEMORIA_4KB)
            {
                indiceProxima = j;
                break;
            }
        }

        if (indiceProxima == -1)
            return NULL;

        int tamanhoDisponivel = indiceProxima - tamanhoAtual;

        if (tamanhoDisponivel >= quantidade)
        {
            indice = tamanhoAtual;
            break;
        }
    }

    if (indice + quantidade - 1 >= MEMORIA_4KB)
        return NULL;

    posicoes[indice].ponteiro = &memoria[indice];
    posicoes[indice].tamanho = quantidade;

    return posicoes[indice].ponteiro;
}

int desaloca(char * ponteiro)
{
    if (memoria == NULL)
        return 1;

    int indice = -1;

    for (int i = 0; i < MEMORIA_4KB; i++)
    {
        if (posicoes[i].ponteiro == ponteiro)
        {
            indice = i;
            break;
        }
    }

    if (indice < 0)
        return 1;

    memset(ponteiro, 0, posicoes[indice].tamanho);

    posicoes[indice].ponteiro = NULL;
    posicoes[indice].tamanho = 0;

    return 0;
}

int finalizar()
{
    if (memoria == NULL || munmap(memoria, MEMORIA_4KB) == -1)
       return 1;
    else
       return 0;
}