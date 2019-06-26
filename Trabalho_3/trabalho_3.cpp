#include <iostream>
#include <fstream>
#include <time.h>

#include "huffman.h"
#include "heap.h"
#include "arquivo.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc != 4)
    {
        cout << "\nForma de uso : " << endl;
        cout << "\\.trabalho_3 --compactar arquivo.txt arquivo.huff " << endl;
        cout << "\\.trabalho_3 --descompactar arquivo.huf arquivo.txt ";
        exit(1);
    } 
    clock_t t0;
    if (((string)argv[1] == "--compactar")){
        // Compactação
        t0 = clock();
        CompactarEscrita(argv[2], argv[3]);
        cout << "Arquivo Compactado com sucesso" << endl;
        cout << "Tempo Gasto: " << (double)(clock() - t0) / CLOCKS_PER_SEC << " segundos.\n";
    } else if (((string)argv[1] == "--descompactar")){
        // Descompactação.
        t0 = clock();
        Descompactar(argv[2], argv[3]);
        cout << "Arquivo Descompactado com sucesso" << endl;
        cout << "Tempo Gasto: " << (double)(clock() - t0) / CLOCKS_PER_SEC << " segundos.\n";
    }
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o trabalho_3 trabalho_3.cpp