#include <iostream>
#include <random>
using namespace std;

void troca(int *i, int *j){
	int aux;
	aux = *i;
	*i = *j;
	*j = aux;
}

int particionamento (int *v, int inicio, int fim, int pivo){

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

void quick_sort (int *v, int inicio, int fim){
    if(fim > inicio){
        int pivo = particionamento(v, inicio, fim, fim);
		quick_sort(v, inicio, pivo - 1);
		quick_sort(v, pivo + 1, fim);
	}
}

void imprimir_vetor(int *v, int n){
    for(int i = 0; i < n; ++i)
		cout << v[i] << " ";
	cout << endl;
}

int main(){
    // Gerador de números aleatórios
    random_device RD;
    mt19937 ger(RD());
    uniform_int_distribution<int> dis(1,10);
    //int meu_num = dis(ger);

    cout << "Forneca um numero positivo de elementos que o vetor deve ter" << endl;
    int n = -1;
    while (n < 1) cin >> n;
    int* v = new int[n];

    for(int i = 0; i < n; ++i)
		v[i] = dis(ger);


    cout << "Vetor inicialmente: ";
	imprimir_vetor(v, n);
	
	quick_sort(v, 0, n - 1);

	cout << "Vetor apos QuickSort: ";
	imprimir_vetor(v, n);
}