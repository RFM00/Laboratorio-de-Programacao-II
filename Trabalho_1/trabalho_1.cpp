#include <iostream>
#include <random>
#include <time.h>
#include "instancias_ruins_Quicksort.hpp"
using namespace std;

void troca(int *i, int *j)
{
    int aux;
    aux = *i;
    *i = *j;
    *j = aux;
}

// Quicksort Índices ---------------------------------------------------------------

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

// Fim Quicksort Índices ------------------------------------------------------------

int *particionamento(int *inicio, int *fim, int *pivo)
{

    troca(inicio, pivo);
    pivo = inicio;

    int *i = inicio;
    int *j = i + 1;

    for (; j != fim + 1; j++)
    {
        if (*j < *pivo)
        {
            i++;
            troca(i, j);
        }
    }

    troca(inicio, i);
    return i;
}

int *escolher_pivo(int *primeiro, int *ultimo)
{
    int a = (ultimo - primeiro) / 2;
    return primeiro + a;
}

// Quicksort Ponteiros ---------------------------------------------------------------

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

// Fim Quicksort Ponteiros -----------------------------------------------------------

// Quicksort Memoria -----------------------------------------------------------------

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

// Fim Quicksort Memoria -------------------------------------------------------------

// Quicksort Mediana -----------------------------------------------------------------

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


// Fim Quicksort Mediana -------------------------------------------------------------

// Quicksort Pivo Aleatório ----------------------------------------------------------

// Coisas para aleatoriedade

random_device RDA;
mt19937 ger(RDA());

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

// Fim Quicksort Pivo Aleatório ------------------------------------------------------

bool verifica_ordenacao(int *inicio, int *fim)
{
    int *p = inicio;
    inicio++;
    for (; inicio != fim + 1; inicio++)
    {
        if (*p > *inicio)
            return false;
        p++;
    }
    return true;
}

void imprimir_vetor(int *v, int n)
{
    for (int i = 0; i < n; ++i)
        cout << v[i] << " ";
    cout << endl;
}

void gerar_instancia_aleatoria(int *v, int n)
{
    cout << "Forneca o intervalo" << endl;

    int li = 1, ls = 0;
    while (li > ls)
    {
        cout << "Limite inferior: ";
        cin >> li;
        cout << "Limite superior: ";
        cin >> ls;
    }
    cout << endl;

    uniform_int_distribution<int> dis(li, ls);

    for (int i = 0; i < n; ++i)
        v[i] = dis(ger);
}

void copiar_vetor(int *v, int *copia, int n)
{
    for (int i = 0; i < n; i++)
        copia[i] = v[i];
}

int main()
{
    cout << "TRABALHO 1 - QUICK SORT\n\n";

    cout << "Forneca o numero de elementos do vetor: ";

    int n = 0;
    while (n < 1)
        cin >> n;

    int *v = new int[n];
    int *copia = new int[n];

    int opcao = 0;
    clock_t Ticks[2];
    
    while (opcao < 1 || opcao > 2){
            cout << "1 - Escrever intervalo com repeticao\n2 - Instancias de pior caso\n\n";
            cin >> opcao;
        }
        if(opcao == 1 ){
            gerar_instancia_aleatoria(v, n);
        }else{
            escrever_instancia(v, n);
        }

    while (true)
    {
        opcao = 0;
        while (opcao < 1 || opcao > 5){
            cout << "\nQual Quick Sort deseja executar?\n1 - Indices\n2 - Ponteiros\n";
            cout << "3 - Memoria\n4 - Mediana\n5 - Aleatorio\n";
            cin >> opcao;
        }

        copiar_vetor(v, copia, n);
        switch (opcao)
        {
        case 1:
            cout << "\nQuick Sort por Indices\n";
            Ticks[0] = clock();
            quick_sort_indices(copia, 0, n - 1);
            break;
        case 2:
            cout << "\nQuick Sort por Ponteiros\n";
            Ticks[0] = clock();
            quick_sort_ponteiros(copia, copia + n - 1);
            break;
        case 3:
            cout << "\nQuick Sort Memoria\n";
            Ticks[0] = clock();
            quick_sort_memoria(copia, copia + n - 1);
            break;
        case 4:
            cout << "\nQuick Sort Mediana\n";
            Ticks[0] = clock();
            quick_sort_mediana(copia, copia + n - 1);
            break;
        case 5:
            cout << "\nQuick Sort Pivo Aleatório\n";
            Ticks[0] = clock();
            quick_sort_pivo_aleatorio(copia, copia + n - 1);
            break;
        }

        Ticks[1] = clock();
        if (verifica_ordenacao(copia, copia + n - 1))
        {
            cout << "O vetor esta ordenado.\n";
            cout << "Tempo " << (double)(Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC << " milisegundos.\n";
        }
        else
            cout << "O vetor não está ordenado\n\n";
        cout << "\nContinuar? 1/0\n";
        cin >> opcao;

        if(opcao == 0)
            break;
    }

    delete[] v;
    delete[] copia;
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_1 trabalho_1.cpp