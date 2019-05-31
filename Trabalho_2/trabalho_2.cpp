#include <iostream>
#include <string>
#include <time.h>

#include "gerador.h"
#include "buscador.h"
#include "instancias_Reais_Trabalho_2.hpp"

using namespace std;

bool benchmark(const char *texto, const char *padrao, int *saida_bruta, int *saida_kmp){
	clock_t instanteInicial = clock();
	
	buscar_forca_bruta(texto, padrao, saida_bruta);
	cout << "\nForca Bruta - Tempo Transcorrido: " << (double)(clock() - instanteInicial) / CLOCKS_PER_SEC << " segundos.";

	instanteInicial = clock();
	buscar_KMP(texto, padrao, saida_kmp);
	cout << "\nKMP - Tempo Transcorrido: " << (double)(clock() - instanteInicial) / CLOCKS_PER_SEC << " segundos.\n";

	while (*saida_bruta == *saida_kmp){
		if(*saida_bruta == -1 && *saida_kmp == -1)
			return true;
		saida_bruta++;
		saida_kmp++;
	}

	return false;
}

int main(){
	srand (time(NULL));
	int opcao = 0, padraoEscolhido, tamTexto = 0, tamPadrao = 0, variedade = 0;
	const char *texto, *padrao;
	int *saida_bruta, *saida_kmp;

	cout << "Busca por padroes em textos!\n";

	while (opcao != 3){
		opcao = 0;
		cout << "\nQual instancia deseja utilizar:\n1 - Instanca Aleatoria\n2 - Instancia Real\n3 - Sair\n";
		cin >> opcao;

		switch (opcao)
		{
		case 1:
			cout << "\nInserir tamanho do texto: "; cin >> tamTexto;
			if(tamTexto < 1) {cout << "Tamanho do texto deve ser maior que 1"; break;}
			cout << "\nInserir tamanho do padrao : "; cin >> tamPadrao;
			if(tamPadrao > tamTexto){cout << "Tamanho do Padrão deve ser menor que o tamanho do texto"; break;}
			cout << "\nInserir grau de variedade (1 a 26): "; cin >> variedade;
			if(variedade < 1 || variedade > 26) {cout << "Variedade deve estar no intervalo requerido"; break;}
	

			saida_bruta = new int[tamTexto + 1];
			saida_kmp = new int[tamTexto + 1];

			cout << "\nTestes com instancias aleatorias\n";
			texto = gerador_aleatorio(tamTexto, variedade);
			padrao = gerador_aleatorio(tamPadrao, variedade);

			if(!benchmark(texto, padrao, saida_bruta, saida_kmp))
				cout << "Falha na ordenacao!\n";
			

			cout << "\nTestes com instancias de pior caso 1\n";
			texto = gerador_pior_caso_1(tamTexto);
			padrao = gerador_pior_caso_1(tamPadrao);

			if(!benchmark(texto, padrao, saida_bruta, saida_kmp))
				cout << "Falha na ordenacao!\n";


			cout << "\nTestes com instancias de pior caso 2\n";
			texto = gerador_pior_caso_2(tamTexto);
			padrao = gerador_pior_caso_2(tamPadrao);

			if(!benchmark(texto, padrao, saida_bruta, saida_kmp))
				cout << "Falha na ordenacao!\n";

			delete[] texto;
			delete[] padrao;
			delete[] saida_bruta;
			delete[] saida_kmp;
			break;
		case 2:
			cout << "\nDigite um numero no intervalo de 0 a 35129 para selecionar a palavra: "; cin >> padraoEscolhido;
			if(padraoEscolhido < 0 || padraoEscolhido > 35129) {cout << "O numero escolhido deve estar entre 0 e 35129"; break;}

			saida_bruta = new int[10000000];
			saida_kmp = new int[10000000];

			if(!benchmark(Texto_Livros, Padroes_Palavras[padraoEscolhido], saida_bruta, saida_kmp))
				cout << "Falha na ordenacao!\n";
		case 3:
			break;
		}
	}
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_2 trabalho_2.cpp