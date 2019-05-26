#ifndef QS_Ponteiros
#define QS_Ponteiros

#include "utilidades.h"

void quick_sort_ponteiros(int *inicio, int *fim)
{
    if (fim > inicio)
    {
        int *pivo_escolhido = escolher_pivo(inicio, fim);
        int *pivo = particionamento(inicio, fim, pivo_escolhido);
        quick_sort_ponteiros(inicio, pivo - 1);
        quick_sort_ponteiros(pivo + 1, fim);
    }
}

#endif