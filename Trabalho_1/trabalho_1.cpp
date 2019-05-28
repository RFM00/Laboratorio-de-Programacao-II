#include <iostream>
#include <random>
#include <time.h>
#include "instancias_ruins_Quicksort.hpp"
#include "utilidades.h"
#include "qs_indices.h"
#include "qs_mediana.h"
#include "qs_memoria.h"
#include "qs_pivo_aleatorio.h"
#include "qs_ponteiros.h"

using namespace std;


int main()
{
    cout << "\nQuick Sorts\n\n";
    cout << "Forneca o numero de elementos do vetor: ";

    int n;
    cin >> n;

    int *v = new int[n];
    int *copia = new int[n];

    int opcao = 0;
    clock_t Ticks[2];
    
    cout << "1 - Escrever intervalo com repeticao\n2 - Instancias de pior caso\n\n";
    cin >> opcao;
    
    if(opcao == 1)
        gerar_instancia_aleatoria(v, n);
    else
        escrever_instancia(v, n);
    
    imprimir_vetor(v, n);

    while (true)
    {
        opcao = 0;
        cout << "\nQual Quick Sort deseja executar?\n1 - Indices\n2 - Ponteiros\n";
        cout << "3 - Memoria\n4 - Mediana\n5 - Aleatorio\n";
        cin >> opcao;
        
        copiar_vetor(v, copia, n);
        Ticks[0] = clock();
        switch (opcao)
        {
        case 1:
            cout << "\nQuick Sort por Indices\n";
            quick_sort_indices(copia, 0, n - 1);
            break;
        case 2:
            cout << "\nQuick Sort por Ponteiros\n";
            quick_sort_ponteiros(copia, copia + n - 1);
            break;
        case 3:
            cout << "\nQuick Sort Memoria\n";
            quick_sort_memoria(copia, copia + n - 1);
            break;
        case 4:
            cout << "\nQuick Sort Mediana\n";
            quick_sort_mediana(copia, copia + n - 1);
            break;
        case 5:
            cout << "\nQuick Sort Pivo Aleatório\n";
            quick_sort_pivo_aleatorio(copia, copia + n - 1);
            break;
        }

        Ticks[1] = clock();
        if (verifica_ordenacao(copia, copia + n - 1))
        {
            cout << "O vetor esta ordenado.\n";
            cout << "Tempo " << (double)(Ticks[1] - Ticks[0]) / CLOCKS_PER_SEC << " segundos.\n";
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