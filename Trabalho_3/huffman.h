#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"

using namespace std;

struct Huffman{
    unsigned int elem = '\0';
    int freq = 0;
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

void criarHeap(Heap *A, Huffman *H, int tamanho){
    for (int i = 0; i < tamanho; i++){
        A[i].freq = H[i].freq;
        A[i].indice = i;
    }
    buildMinHeap(A, tamanho);
}



// Remove os 2 minimos do heap
// Insere na arvore com freq = soma das freqs dos nos que entraram
// e filho esquerdo e direito referentes a quem foi removido,
// Cria um novo no para inserir no heap, onde a freq é a soma, 
// e o indice é o indice que foi inserido na arvore de huffman

Heap algoritmoHuffman(Huffman *huffman, Heap *heap, int tamanhoHeap){
    int peso = 0;
    Heap min[2];
    int indiceHuffmanAtual = tamanhoHeap - 1;
    imprimirHeap(heap, tamanhoHeap);
    while (tamanhoHeap > 1){
        // Remove os 2 nohs minimos;
        min[0] = removerMin(heap, tamanhoHeap);
        min[1] = removerMin(heap, tamanhoHeap);
        
        // Cria um noh que é a soma dos 2 minimos e adiciona na heap
        peso = min[0].freq + min[1].freq;
        heap[tamanhoHeap].freq = peso;
        heap[tamanhoHeap].indice = indiceHuffmanAtual + 1;
        indiceHuffmanAtual++;
        
        // Adiciona o novo noh na arvore
        huffman[indiceHuffmanAtual].freq = peso;
        huffman[indiceHuffmanAtual].dir = min[0].indice;
        huffman[indiceHuffmanAtual].esq = min[1].indice;
        tamanhoHeap++;
        buildMinHeap(heap, tamanhoHeap);
        imprimirHeap(heap, tamanhoHeap);
    }

    return heap[0];
}

void imprimirArvoreHuffman(Huffman *noh, int tamanho){
    cout << '\n';
    for (int i = 0; i < tamanho; i++){
        cout << "HuffmanTree " << i <<" : " << noh[i].elem << ", " << noh[i].freq 
        << "| " << noh[i].esq << ", " << noh[i].dir << endl;
    }
}


#endif