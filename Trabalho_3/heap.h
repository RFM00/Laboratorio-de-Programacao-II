#ifndef HEAP_H
#define HEAP_H

using namespace std;

struct Heap{
    unsigned long long int freq;
    int indice = -1;
};

void swap(Heap &a, Heap &b){
    Heap aux;
    aux = a;
    a = b;
    b = aux;
}

void minHeapify(Heap *heap, int i, int tamanho){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int min = i;

    if (l < tamanho && heap[l].freq <= heap[i].freq)
        min = l;
    if (r < tamanho && heap[r].freq <= heap[min].freq)
        min = r;
    if (min != i){
        swap(heap[i], heap[min]);
        minHeapify(heap, min, tamanho);
    }
}

void buildMinHeap(Heap *heap, int tamanho){
    for(int i = tamanho / 2; i >= 0; i--)
        minHeapify(heap, i, tamanho);
}

Heap removerMin(Heap *heap, int &tamanho){
    swap(heap[0], heap[tamanho - 1]);
    tamanho--;
    buildMinHeap(heap, tamanho);
    return heap[tamanho];
}

void imprimirHeap(Heap *heap, int tamanho){
    cout << '\n';
    for (int i = 0; i < tamanho; i++){
        cout << "Heap " << i <<" : " << heap[i].freq << " | " << heap[i].indice << endl;
    }
}

#endif