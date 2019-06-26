#include <iostream>
#include <fstream>

#include "huffman.h"
#include "heap.h"
#include "arquivo.h"

using namespace std;



int main() {

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

    // imprimirArvoreHuffman(huffman, tamanhoHuffman);

    algoritmoHuffman(huffman, heap, tamanhoHeap);

    imprimirArvoreHuffman(huffman, tamanhoHuffman);

    // escreverArquivoCompactado(huffman, "inputs/text.huf", tamanhoHuffman);
    if (CompactarEscrita("inputs/text.huf", huffman, tamanhoHuffman))
        cout << "Arquivo Compactado com sucesso" << endl;

    criarCodificacao(huffman, tamanhoHuffman);
    // Descompactar.
    // Huffman *newHuffman;
    // DescompactarLeitura("text.huf", newHuffman);
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o trabalho_3 trabalho_3.cpp