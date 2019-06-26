#include <iostream>
#include <fstream>

#include "huffman.h"
#include "heap.h"
#include "arquivo.h"

using namespace std;

int main() {
    // Compactação Completa
    // Vetor de frequências por bytes
    unsigned long long int frequencia[256];
    int tamanhoHeap, tamanhoHuffman, totalOriginalBits;
    // Ler arquivo a ser compactado
    // Retorna o numero de caracteres diferentes repetidos
    CompactarLeitura("text.txt", frequencia, tamanhoHeap, totalOriginalBits);
    // Criar Árvore de Huffman com tamanho adequado
    // Tamanho da arvore é 2 * heap - 1
    tamanhoHuffman = 2 * tamanhoHeap - 1;
    Huffman *huffman = new Huffman[tamanhoHuffman];
    criarArvore(huffman, frequencia);
    // Criar heap contendo os elementos da árvore de huffman
    Heap *heap = new Heap[tamanhoHeap];
    criarHeap(heap, huffman, tamanhoHeap);

    algoritmoHuffman(huffman, heap, tamanhoHeap);
    imprimirArvoreHuffman(huffman, tamanhoHuffman);
    if (CompactarEscrita("text.txt", "text.huf", huffman, tamanhoHuffman, totalOriginalBits))
        cout << "Arquivo Compactado com sucesso" << endl;


    // Descompactação.
    Descompactar("text.huf", "text.txt");
    // Huffman *newHuffman;
    // DescompactarLeitura("text.huf", newHuffman);
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o trabalho_3 trabalho_3.cpp