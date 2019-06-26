#include <iostream>
#include <fstream>

#include "huffman.h"
#include "heap.h"
#include "arquivo.h"

using namespace std;

int main() {
    // Compactação
    CompactarEscrita("text.txt", "text.huf");
    cout << "Arquivo Compactado com sucesso" << endl;

    // Descompactação.
    Descompactar("text.huf", "text.txt");
    // Huffman *newHuffman;
    // DescompactarLeitura("text.huf", newHuffman);
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o trabalho_3 trabalho_3.cpp