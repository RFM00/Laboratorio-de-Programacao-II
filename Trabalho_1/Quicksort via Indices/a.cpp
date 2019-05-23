#include <iostream>
#include <random>
using namespace std;

void troca(int *i, int *j){
	int aux;
	aux = *i;
	*i = *j;
	*j = aux;
}

int particionamento_indices (int *v, int inicio, int fim, int pivo){

  troca(&v[inicio], &v[pivo]);
	pivo = inicio;

	int i = inicio;

	for(int j = i + 1 ; j < fim + 1; j++){
		if(v[j] < v[pivo]){
			i++;
			troca(&v[i], &v[j]);
		}
	}
	
	troca(&v[inicio], &v[i]);
	return i;
}

int escolher_pivo_indices(int primeiro, int ultimo){
	return ultimo;
}

void quick_sort_indices(int *v, int inicio, int fim){
    if(fim > inicio){
			int pivo_escolhido = escolher_pivo_indices(inicio, fim);
      int pivo = particionamento_indices(v, inicio, fim, pivo_escolhido);
			quick_sort_indices(v, inicio, pivo - 1);
			quick_sort_indices(v, pivo + 1, fim);
	}
}

void imprimir_vetor(int *v, int n){
    for(int i = 0; i < n; ++i)
		cout << v[i] << " ";
	cout << endl;
}

int main(){
    cout << "Forneca o numero de elementos do vetor ( maior que 0 )" << endl;

    int n = -1;
    while (n < 1) cin >> n;
    int* v = new int[n];

    cout << "Forneca o intervalo desses" << endl;

    int li = 1, ls = 0;
    while (li > ls) {
        cout << "Limite inferior" << endl;
        cin >> li;
        cout << "Limite superior" << endl;
        cin >> ls;
    }

    random_device RD;
    mt19937 ger(RD());
    uniform_int_distribution<int> dis(li,ls);


    for(int i = 0; i < n; ++i)
		v[i] = dis(ger);

    int *inicio = v;
    int *fim = v + n - 1;


    cout << "Vetor inicialmente: ";
	imprimir_vetor(v, n);
	
	quick_sort_indices(v, 0, n - 1);

	cout << "Vetor apos QuickSort: ";
	imprimir_vetor(v, n);
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_a a.cpp