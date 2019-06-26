#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"
#include <string>

using namespace std;

struct Huffman{
    unsigned char elem = '\0';
    unsigned long long int freq = 0;
    int dir = -1;
    int esq = -1;
};

void criarArvore(Huffman *noh, unsigned long long int *frequencia){
    int j = 0;
    for (int i = 0; i < 256; i++){
        // Apenas elementos que ocorrem
        if (frequencia[i] != 0){
            noh[j].elem = i;
            noh[j].freq = frequencia[i];
            j++;
        }
    }
}

void criarHeap(Heap *A, Huffman *H, int numeroElementos){
    for (int i = 0; i < numeroElementos; i++){
        A[i].freq = H[i].freq;
        A[i].indice = i;
    }
    buildMinHeap(A, numeroElementos);
}

// Remove os 2 minimos do heap
// Insere na arvore com freq = soma das freqs dos nos que entraram
// e filho esquerdo e direito referentes a quem foi removido,
// Cria um novo no para inserir no heap, onde a freq é a soma, 
// e o indice é o indice que foi inserido na arvore de huffman

Heap algoritmoHuffman(Huffman *huffman, Heap *heap, int numeroElementos){
    int peso = 0;
    Heap min[2];
    int indiceHuffmanAtual = numeroElementos - 1;
    // imprimirHeap(heap, numeroElementos);
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
        // imprimirHeap(heap, numeroElementos);
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