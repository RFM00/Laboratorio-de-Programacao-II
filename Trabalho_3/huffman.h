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

void criarHeap(Heap *A, Huffman *H, int tamanhoHeap){
    for (int i = 0; i < tamanhoHeap; i++){
        A[i].freq = H[i].freq;
        A[i].indice = i;
    }
    buildMinHeap(A, tamanhoHeap);
}

void criarCodificacao(Huffman *huffman, int tamanhoHuffman){
    string code[256];
    string aux;
    Huffman *pai, *raiz = huffman + tamanhoHuffman - 1;
    int count = 0;
    while (count <= (tamanhoHuffman - 1) / 2 ){
        if (raiz->esq != -1){
            aux += '0';
            pai = raiz;
            raiz = huffman + raiz->esq;
        }else if (raiz->dir != -1){
            aux += '1';
            pai = raiz;
            raiz = huffman + raiz->dir;
        }else {
            if (huffman[pai->esq].elem == raiz->elem)
                pai->esq = -1;
            else
                pai->dir = -1;

            if (raiz->elem == '\0'){
                raiz = huffman + tamanhoHuffman - 1;
                aux.clear();
                continue;
            }
            code[raiz->elem].append(aux);
            aux.clear();
            raiz = huffman + tamanhoHuffman - 1;
            count++;
        }
    }

    cout << "Codificacao" << endl;
    for (int i = 0; i < 256; i++){
        if(!code[i].empty())
            cout << (unsigned char)i << ": " << code[i] << endl;
    }
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
    // imprimirHeap(heap, tamanhoHeap);
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
        // imprimirHeap(heap, tamanhoHeap);
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