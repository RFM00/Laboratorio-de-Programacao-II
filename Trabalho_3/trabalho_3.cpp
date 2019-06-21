#include <iostream>
#include <fstream>
#include "heap.h"
#include "huffman.h"

using namespace std;

int main() {
    // Vetor de frequências por bytes
    unsigned long long int frequencia[256];
    for (int i = 0; i < 256; i++) frequencia[i] = 0;

    // Abrir arquivo
    ifstream file("text.txt");                                                                                                                                                                                                                                                                            

    // Identificador do byte
    unsigned long long int byte;

    // Contador de quantidade de diferentes bytes
    int tamanhoHeap = 0;

    // Leitor de arquivo
    while(!file.eof()){
        byte = file.get();
        //Contador de frequência
        if(frequencia[byte] == 0)
            tamanhoHeap++;
        ++frequencia[byte];
    }

    // Fim do arquivo.
    file.close();

    // Criar Árvore de Huffman
    Huffman *huffmanTree = new Huffman[2 * tamanhoHeap - 1];
    int j = 0;
    for (int i = 0; i < 256; i++){
        // Apenas elementos que ocorrem
        if (frequencia[i] != 0){
            huffmanTree[j].elem = i;
            huffmanTree[j].freq = frequencia[i];
            cout << "HuffmanTree: " << huffmanTree[j].elem << ", " << huffmanTree[j].freq << endl;
            j++;
        }
    }

    // Criar heap contendo os elementos da árvore de huffman
    Noh *Heap = new Noh[tamanhoHeap];
    j = 0;
    for (int i = 0; i < tamanhoHeap; i++){
        Heap[i].freq = huffmanTree[i].freq;
        Heap[i].indice = i;
    }

    buildMinHeap(Heap, tamanhoHeap);

    while (tamanhoHeap > 0){
        removerMin(Heap, tamanhoHeap);
        imprimirHeap(Heap, tamanhoHeap);
    }

}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_3 trabalho_3.cpp