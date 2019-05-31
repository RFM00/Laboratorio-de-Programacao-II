#include <iostream>
#include <string>

#include "gerador.h"
#include "buscador.h"
#include "instancias_Reais_Trabalho_2.hpp"

using namespace std;

void imprimirSaida(int *saida){
	while(*saida != -1) {
		cout << *saida << ", ";
		saida++;
	}
	cout << endl;
}

int main(){
    
    int tamTexto = 0, tamPadrao = 0, variedade = 0;
    
    cout << "\nInserir tamanho do texto: ";
    cin >> tamTexto;
    cout << "\nInserir tamanho do padrao: ";
    cin >> tamPadrao;
    cout << "\nInserir grau de variedade: ";
    cin >> variedade;
    
    int *saida_bruta = new(nothrow) int[tamTexto + 1];
    int *saida_kmp = new(nothrow) int[tamTexto + 1];
    char *texto = NULL, *padrao = NULL;
	

    // Teste com gerador aleatório
	
	srand (time(NULL)); /* initialize random seed: */

    cout << "\nTESTE COM GERADOR ALEATÓRIO\n";
	
    texto = gerador_aleatorio(tamTexto, variedade);
    cout << "\nTexto: ";
	for(int i = 0; i < tamTexto; i++) cout << texto[i] << " ";
	cout << endl;

	padrao = gerador_aleatorio(tamPadrao, variedade);
    cout << "\nPadrao: ";
	for(int i = 0; i < tamPadrao; i++) cout << padrao[i] << " ";
	cout << endl;

	// Força Bruta
	buscar_forca_bruta(texto, padrao, saida_bruta);
	// imprimirSaida(saida_bruta);

	// KMP 
	buscar_KMP(texto, padrao, saida_kmp);
	// imprimirSaida(saida_kmp);

	delete[] saida_bruta;
	delete[] saida_kmp;
	delete[] texto;
	delete[] padrao;
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_2 trabalho_2.cpp