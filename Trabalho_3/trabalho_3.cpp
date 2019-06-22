#include <iostream>
#include <fstream>

#include "huffman.h"
#include "heap.h"
#include "arquivo.h"

using namespace std;



int main() {
    // Vetor de frequências por bytes
    unsigned long long int frequencia[256];
    for (int i = 0; i < 256; i++) frequencia[i] = 0;

    int tamanhoHeap = 0, tamanhoHuffman = 0;

    // Ler arquivo a ser compactado
    // Retorna o numero de caracteres diferentes repetidos
    tamanhoHeap = lerArquivoCompactar(frequencia, "text.txt");
    // Ler arquivo a ser descompactado
    // tamanhoHeap = lerArquivoDescompactar(frequencia, "text.huf");

    // Tamanho da arvore é 2 * heap - 1
    tamanhoHuffman = 2 * tamanhoHeap - 1;
    // Criar Árvore de Huffman
    Huffman *huffman = new Huffman[tamanhoHuffman];
    criarArvore(huffman, frequencia);
    // Criar heap contendo os elementos da árvore de huffman
    Heap *heap = new Heap[tamanhoHeap];
    criarHeap(heap, huffman, tamanhoHeap);

    imprimirArvoreHuffman(huffman, tamanhoHuffman);

    algoritmoHuffman(huffman, heap, tamanhoHeap);

    imprimirArvoreHuffman(huffman, tamanhoHuffman);

    // escreverArquivoCompactado(huffman, "inputs/text.huf", tamanhoHuffman);
    if (escreverArquivoCompactado(huffman, "inputs/text.huf", tamanhoHuffman))
        cout << "Arquivo Compactado com sucesso, apesar de ainda nao ter certeza disso" << endl;
        
    // escreverArquivoDescompactado(huffman, "text.txt");
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o trabalho_3 trabalho_3.cpp