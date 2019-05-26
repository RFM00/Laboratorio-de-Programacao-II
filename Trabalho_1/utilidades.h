#ifndef Utilidades
#define Utilidades

#include <iostream>
#include <random>

using namespace std;

random_device RDA;
mt19937 ger(RDA());

void troca(int *i, int *j)
{
    int aux;
    aux = *i;
    *i = *j;
    *j = aux;
}

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

#endif