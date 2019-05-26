#ifndef QS_Memoria
#define QS_Memoria

#include "utilidades.h"

void quick_sort_memoria(int *inicio, int *fim)
{
    while (fim > inicio)
    {
        int *pivo_escolhido = escolher_pivo(inicio, fim);
        int *pivo = particionamento(inicio, fim, pivo_escolhido);
        if (pivo - inicio < fim - pivo)
        {
            quick_sort_memoria(inicio, pivo - 1);
            inicio = pivo + 1;
        }
        else
        {
            quick_sort_memoria(pivo + 1, fim);
            fim = pivo - 1;
        }
    }
}

#endif