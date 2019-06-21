#ifndef HEAP_H
#define HEAP_H

using namespace std;

struct Noh{
    int freq = -1;
    int indice = -1;
};

void swap(Noh &a, Noh &b){
    Noh aux;
    aux = a;
    a = b;
    b = aux;
}

void maxHeapify(Noh *A, int i, int tamanho){
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

void minHeapify(Noh *A, int i, int tamanho){
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

void buildMinHeap(Noh *A, int tamanho){
    for(int i = tamanho / 2; i >= 0; i--)
        minHeapify(A, i, tamanho);
}

void removerMin(Noh *A, int &tamanho){
    swap(A[0], A[tamanho - 1]);
    tamanho--;
    buildMinHeap(A, tamanho);
}

void imprimirHeap(Noh *noh, int tamanho){
    cout << '\n';
    for (int i = 0; i < tamanho; i++){
        cout << noh[i].freq << " ";
    }
}

#endif