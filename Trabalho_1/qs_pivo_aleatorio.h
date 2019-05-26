#ifndef QS_Pivo_Aleatorio
#define QS_Pivo_Aleatorio

#include "utilidades.h"

int *escolher_pivo_aleatorio(int *primeiro, int *ultimo)
{
    uniform_int_distribution<int> dis(0, ultimo - primeiro);
    return primeiro + dis(ger);
}

void quick_sort_pivo_aleatorio(int *inicio, int *fim)
{
    while (fim > inicio)
    {
        int *pivo_escolhido = escolher_pivo_aleatorio(inicio, fim);
        int *pivo = particionamento(inicio, fim, pivo_escolhido);
        if (pivo - inicio < fim - pivo)
        {
            quick_sort_pivo_aleatorio(inicio, pivo - 1);
            inicio = pivo + 1;
        }
        else
        {
            quick_sort_pivo_aleatorio(pivo + 1, fim);
            fim = pivo - 1;
        }
    }
}

#endif