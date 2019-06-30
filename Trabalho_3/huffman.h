#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"
#include <string>

using namespace std;

struct Huffman{
    unsigned char elem;
    unsigned long long int freq;
    short int dir = -1;
    short int esq = -1;
};

void criarArvore(Huffman *huffman, unsigned long long int *frequencia){
    int j = 0;
    for (int i = 0; i < 256; i++){
        // Apenas elementos que ocorrem
        if (frequencia[i] != 0){
            huffman[j].elem = i;
            huffman[j].freq = frequencia[i];
            j++;
        }
    }
}

void criarHeap(Heap *heap, Huffman *huffman, int numeroElementos){
    for (int i = 0; i < numeroElementos; i++){
        heap[i].freq = huffman[i].freq;
        heap[i].indice = i;
    }
    buildMinHeap(heap, numeroElementos);
}

Heap algoritmoHuffman(Huffman *huffman, Heap *heap, int numeroElementos){
    Heap min[2];
    int peso = 0, indiceHuffmanAtual = numeroElementos - 1;
    while (numeroElementos > 1){
        // Remove os 2 nohs minimos;
        min[0] = removerMin(heap, numeroElementos);
        min[1] = removerMin(heap, numeroElementos);
        
        // Cria um noh que é a soma dos 2 minimos e adiciona na heap
        peso = min[0].freq + min[1].freq;
        heap[numeroElementos].freq = peso;
        heap[numeroElementos].indice = indiceHuffmanAtual + 1;
        indiceHuffmanAtual++;
        
        // Adiciona o novo noh na arvore
        huffman[indiceHuffmanAtual].freq = peso;
        huffman[indiceHuffmanAtual].dir = min[0].indice;
        huffman[indiceHuffmanAtual].esq = min[1].indice;
        numeroElementos++;
        buildMinHeap(heap, numeroElementos);
    }

    return heap[0];
}

void imprimirArvoreHuffman(Huffman *huffman, int tamanho){
    cout << '\n';
    for (int i = 0; i < tamanho; i++){
        cout << "HuffmanTree " << i <<" : " << huffman[i].elem << ", " << huffman[i].freq 
        << "| " << huffman[i].esq << ", " << huffman[i].dir << endl;
    }
}


#endif