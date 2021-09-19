#include "alocador.h"

MEMORIA_4KB = 4096;

char* memoria = NULL;

int inicia_alocador()
{
    memoria = mmap(NULL, MEMORIA_4KB, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if(memoria == -1)
       return 1;
    else
        return 0;
}

int finalizar()
{
    if (munmap(memoria, MEMORIA_4KB) == -1)
       return 1;
    else
       return 0;
}

char *aloca(int)
{
    return NULL;
}

int desaloca(char *)
{
    if (munmap(char*, tamanho) == -1)
        return 1;
    else
        return 0;
}
