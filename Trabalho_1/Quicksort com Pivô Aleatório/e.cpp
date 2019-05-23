#include <iostream>
#include <random>
using namespace std;

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

int *escolher_pivo(int *primeiro, int *ultimo) {}
random_device RD;
mt19937 ger(RD());
uniform_int_distribution<int> dis(0, ultimo - primeiro);

return primeiro + dis(ger);
}

void quick_sort_pivo_aleatorio(int *inicio, int *fim)
{
	while (fim > inicio)
	{
		int *pivo_escolhido = escolher_pivo(inicio, fim);
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

void imprimir_vetor(int *v, int n)
{
	for (int i = 0; i < n; ++i)
		cout << v[i] << " ";
	cout << endl;
}

int main()
{
	cout << "Forneca o numero de elementos do vetor ( maior que 0 )" << endl;

	int n = -1;
	while (n < 1)
		cin >> n;
	int *v = new int[n];

	cout << "Forneca o intervalo desses" << endl;

	int li = 1, ls = 0;
	while (li > ls)
	{
		cout << "Limite inferior" << endl;
		cin >> li;
		cout << "Limite superior" << endl;
		cin >> ls;
	}

	random_device RD;
	mt19937 ger(RD());
	uniform_int_distribution<int> dis(li, ls);

	for (int i = 0; i < n; ++i)
		v[i] = dis(ger);

	int *inicio = v;
	int *fim = v + n - 1;

	cout << "Vetor inicialmente: ";
	imprimir_vetor(v, n);

	quick_sort_pivo_aleatorio(inicio, fim);

	cout << "Vetor apos QuickSort: ";
	imprimir_vetor(v, n);
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_e e.cpp