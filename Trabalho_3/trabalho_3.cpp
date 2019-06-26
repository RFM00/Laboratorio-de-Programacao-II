#include <iostream>
#include <fstream>

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
    if (((string)argv[1] == (string)"--compactar")){
        // Compactação
        CompactarEscrita(argv[2], argv[3]);
        cout << "Arquivo Compactado com sucesso" << endl;
    } else if (((string)argv[1] == (string)"--descompactar")){
        // Descompactação.
        Descompactar(argv[2], argv[3]);
        cout << "Arquivo Descompactado com sucesso" << endl;
        // Huffman *newHuffman;
    }
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o trabalho_3 trabalho_3.cpp