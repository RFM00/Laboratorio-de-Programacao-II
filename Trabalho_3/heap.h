#ifndef HEAP_H
#define HEAP_H
#include "huffman.h"

using namespace std;

struct Heap{
    int freq = -1;
    int indice = -1;
};

void swap(Heap &a, Heap &b){
    Heap aux;
    aux = a;
    a = b;
    b = aux;
}

void maxHeapify(Heap *A, int i, int tamanho){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;

    if (l < tamanho && A[l].freq > A[i].freq)
        max = l;
    if (r < tamanho && A[r].freq > A[max].freq)
        max = r;
    if (max != i){
        swap(A[i], A[max]);
        maxHeapify(A, max, tamanho);
    }
}

void minHeapify(Heap *A, int i, int tamanho){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int min = i;

    if (l < tamanho && A[l].freq <= A[i].freq)
        min = l;
    if (r < tamanho && A[r].freq <= A[min].freq)
        min = r;
    if (min != i){
        swap(A[i], A[min]);
        maxHeapify(A, min, tamanho);
    }
}

void buildMinHeap(Heap *A, int tamanho){
    for(int i = tamanho / 2; i >= 0; i--)
        minHeapify(A, i, tamanho);
}

Heap removerMin(Heap *A, int &tamanho){
    swap(A[0], A[tamanho - 1]);
    tamanho--;
    buildMinHeap(A, tamanho);
    return A[tamanho];
}

void criarHeap(Heap *A, Huffman *H, int tamanho){
    for (int i = 0; i < tamanho; i++){
        A[i].freq = H[i].freq;
        A[i].indice = i;
    }
    buildMinHeap(A, tamanho);
}

void imprimirHeap(Heap *A, int tamanho){
    cout << '\n';
    for (int i = 0; i < tamanho; i++){
        cout << "Heap " << i <<" : " << A[i].freq << " | " << A[i].indice << endl;
    }
}

#endif