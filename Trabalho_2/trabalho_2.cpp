#include <iostream>
#include <stdlib.h>
#include <string>

#include "gerador.h"
#include "buscador.h"

using namespace std;

int main(){
    
    int tamTexto = 0, tamPadrao = 0, variedade = 0;
    
    cout << "\nInserir tamanho do texto: ";
    cin >> tamTexto;
    cout << "\nInserir tamanho do padrao: ";
    cin >> tamPadrao;
    cout << "\nInserir grau de variedade: ";
    cin >> variedade;
    
    int *saida_bruta = new int[tamTexto + 1];
    int *saida_kmp = new int[tamTexto + 1];
    char *texto, *padrao;

    // Teste com gerador aleatório
	
	srand (time(NULL)); /* initialize random seed: */

    cout << "\nTESTE COM GERADOR ALEATÓRIO\n";
	
    texto = gerador_aleatorio(tamTexto, variedade);
    cout << "\nTexto: ";
	for(int i = 0; i < tamTexto; i++) cout << *(texto + i) << " ";
	cout << endl;

	padrao = gerador_aleatorio(tamPadrao, variedade);
    cout << "\nPadrao: ";
	for(int i = 0; i < tamPadrao; i++) cout << *(padrao + i) << " ";
	cout << endl;

	// Força Bruta
    int start = clock();
	buscar_forca_bruta(texto, padrao, saida_bruta);
	cout << "\nINTUITIVO - Tempo Transcorrido: " << clock() - start << "ms" << endl;
    for(int i = 0; saida_bruta[i] != -1; i++) cout << *(saida_bruta + i) << ", ";

	// KMP 
	start = clock();
	buscar_KMP(texto, padrao, saida_kmp);
	cout << "\nKMP - Tempo Transcorrido: " << clock() - start << "ms" << endl;
    for(int i = 0; saida_kmp[i] != -1; i++) cout << *(saida_kmp + i) << ", ";



    // Testes de pior caso 1
    
    cout << "\nTESTE DE PIOR CASO 1\n";

    texto = gerador_pior_caso_1(tamTexto);
    cout << "\nTexto: ";
	for(int i = 0; i < tamTexto; i++) cout << *(texto + i) << " ";
	cout << endl;

	padrao = gerador_pior_caso_1(tamPadrao);
    cout << "\nPadrao: ";
	for(int i = 0; i < tamPadrao; i++) cout << *(padrao + i) << " ";
	cout << endl;

	// Força Bruta
    start = clock();
	buscar_forca_bruta(texto, padrao, saida_bruta);
	cout << "\nINTUITIVO - Tempo Transcorrido: " << clock() - start << "ms" << endl;
    for(int i = 0; saida_bruta[i] != -1; i++) cout << *(saida_bruta + i) << ", ";

	// KMP
	start = clock();
	buscar_KMP(texto, padrao, saida_kmp);
	cout << "\nKMP - Tempo Transcorrido: " << clock() - start << "ms" << endl;
    for(int i = 0; saida_kmp[i] != -1; i++) cout << *(saida_kmp + i) << ", ";
	

    // Testes de pior caso 2
    
    cout << "\nTESTE DE PIOR CASO 2\n";

    texto = gerador_pior_caso_2(tamTexto);
    cout << "\nTexto: ";
	for(int i = 0; i < tamTexto; i++) cout << *(texto + i) << " ";
	cout << endl;

	padrao = gerador_pior_caso_2(tamPadrao);
    cout << "\nPadrao: ";
	for(int i = 0; i < tamPadrao; i++) cout << *(padrao + i) << " ";
	cout << endl;

	// Força Bruta
    start = clock();
	buscar_forca_bruta(texto, padrao, saida_bruta);
	cout << "\nINTUITIVO - Tempo Transcorrido: " << clock() - start << "ms" << endl;
    for(int i = 0; saida_bruta[i] != -1; i++) cout << *(saida_bruta + i) << ", ";

	// KMP
	start = clock();
	buscar_KMP(texto, padrao, saida_kmp);
	cout << "\nKMP - Tempo Transcorrido: " << clock() - start << "ms" << endl;
    for(int i = 0; saida_kmp[i] != -1; i++) cout << *(saida_kmp + i) << ", ";
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_2 trabalho_2.cpp