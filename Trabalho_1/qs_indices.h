#ifndef QS_Indices
#define QS_Indices

#include "utilidades.h"

int particionamento_indices(int *v, int inicio, int fim, int pivo)
{

    troca(&v[inicio], &v[pivo]);
    pivo = inicio;

    int i = inicio;

    for (int j = i + 1; j < fim + 1; j++)
    {
        if (v[j] < v[pivo])
        {
            i++;
            troca(&v[i], &v[j]);
        }
    }

    troca(&v[inicio], &v[i]);
    return i;
}

int escolher_pivo_indices(int primeiro, int ultimo)
{
    return (primeiro + ultimo) / 2;
}

void quick_sort_indices(int *v, int inicio, int fim)
{
    if (fim > inicio)
    {
        int pivo_escolhido = escolher_pivo_indices(inicio, fim);
        int pivo = particionamento_indices(v, inicio, fim, pivo_escolhido);
        quick_sort_indices(v, inicio, pivo - 1);
        quick_sort_indices(v, pivo + 1, fim);
    }
}

#endif