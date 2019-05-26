#ifndef QS_Mediana
#define QS_Mediana

#include "utilidades.h"
#include "qs_ponteiros.h"

void tri_particionamento(int *inicio, int *fim, int *pivo, int **r, int **s)
{
    troca(inicio, pivo);
    pivo = inicio;

    int *m = inicio;
    int *i = inicio;
    int *j = i + 1;

    for (; j != fim + 1; j++)
    {
        if (*j == *pivo)
        {
            i++;
            troca(i, j);
        }
        if (*j < *pivo)
        {
            m++;
            i++;
            troca(i, j);
            troca(i, m);
        }
    }
    troca(pivo, m);

    *r = m;
    *s = i;
}

void selecao_linear_BFPRT(int *inicio, int *iesimo, int *fim)
{
	if(fim < inicio)
		return;
	
    int k = 0;
    int *segmento = inicio;
	// caso em que v[a...b] >= 5
    while(fim > segmento + 5){
		quick_sort_ponteiros(segmento, segmento + 4);
		troca(inicio + k, segmento + 2); 
		segmento = segmento + 5;
		k++;
	}
	// Caso base, se v[a...b] < 5;
	if(segmento < fim){
		quick_sort_ponteiros(segmento, fim);
		troca(inicio + k, segmento + (fim - segmento) / 2);
		k++;
	}

	selecao_linear_BFPRT(inicio, inicio + k / 2, inicio + k - 1);    

	int *Mediana = inicio;
    int *r = NULL;
    int *s = NULL;
    tri_particionamento(inicio, fim, Mediana, &r, &s);
	
    if (iesimo < r)
        selecao_linear_BFPRT(inicio, iesimo, r - 1);
    if (iesimo > s)
        selecao_linear_BFPRT(s + 1, iesimo, fim);
	
}

void quick_sort_mediana(int *inicio, int *fim){
	if(fim > inicio){
		selecao_linear_BFPRT(inicio, inicio + (fim - inicio) / 2, fim);
		quick_sort_mediana(inicio, inicio + (fim - inicio) / 2 - 1);
		quick_sort_mediana(inicio + (fim - inicio) / 2 + 1, fim);
	}
}

#endif