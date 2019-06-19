#include <iostream>
#include <fstream>

using namespace std;

struct Huffman{
    unsigned int elem = '\0';
    int freq = 0;
    int dir = -1;
    int esq = -1;
};

struct Noh{
    int freq;
    int indice;
};

void trocar(Noh *a, Noh *b){
    Noh aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void heapfy(Noh *heap, int i, int last){
    Noh aux;
    while(i < last/2){
        if(heap[i].freq > heap[(2*i) + 1].freq){
            aux.freq = heap[i].freq; aux.indice = heap[i].indice;
            heap[i].freq = heap[(2*i) + 1].freq; heap[i].indice = heap[(2*i) + 1].indice;  
            heap[(2*i) + 1].freq = aux.freq; heap[(2*i) + 1].indice = aux.indice;
        }
        if(heap[i].freq > heap[(2*i) + 2].freq){
            aux.freq = heap[i].freq; aux.indice = heap[i].indice;
            heap[i].freq = heap[(2*i) + 2].freq; heap[i].indice = heap[(2*i) + 2].indice;  
            heap[(2*i) + 2].freq = aux.freq; heap[(2*i) + 2].indice = aux.indice;
        }
        heapfy(heap, (2*i) + 1, last);
        i = (2*i) + 2;
    }
}

void imprimirArvoreHuffman(Huffman *noh, int tamanho){
    for (int i = 0; i < tamanho; i++){
        cout << "\nElemento: " << noh[i].elem;
        cout << "\nFrequencia: " << noh[i].freq;
    }
}

void imprimirHeap(Noh *noh, int tamanho){
    for (int i = 0; i < tamanho; i++){
        cout << "\nIndice: " << noh[i].indice;
        cout << "\nFrequencia: " << noh[i].freq;
    }
}

int main() {

    // Huffman *huffmanTree = new Huffman[2*tamanho - 1];
    // Noh *Heap_min = new Noh[tamanho];

    // 2ª contar a frequencia
    // 3ª preencher n da huffmanTree e Heap_min com a frequencia obtida
    // 4ª completar a huffmanTree com a estratégia da remoção dupla noh
    // Heap_min

    // 1ª

    unsigned long long int O[256];
    for (int i = 0; i < 256; i++) O[i] = 0;

    ifstream e("text.txt");                                                                                                                                                                                                                                                                            

    unsigned long long int b;
    int count = 0;

    while(!e.eof()){
        b = e.get();

        if(O[b] == 0)
            count++;
        ++O[b];
    }

    e.close();

    Huffman *huffmanTree = new Huffman[2 * count - 1];
    int j = 0;
    for (int i = 0; i < 256; i++){
        if (O[i] != 0){
            huffmanTree[j].elem = i;
            huffmanTree[j].freq = O[i];
            cout << "HuffmanTree: " << huffmanTree[j].elem << ", " << huffmanTree[j].freq << endl;
            j++;
        }
    }

    // // Perfeito, comportamento esperado.
    // imprimirArvoreHuffman(huffmanTree, 2 * num_elem - 1);

    Noh *Heap = new Noh[count];
    j = 0;
    for (int i = 0; i < count; i++){
        Heap[i].indice = i;
        Heap[i].freq = huffmanTree[i].freq;
    }

    heapfy(Heap, 0, count);

    for (int i = 0; i < count; i++)
        cout << "Heap: " << Heap[i].freq << ", " << Heap[i].indice << endl;



    // // Perfeito, comportamento esperado.
    // imprimirHeap(Heap, num_elem);
    // Heapfy(Heap, num_elem, num_elem);
    // cout << "\nHeap Após Heapfy\n";
    // imprimirHeap(Heap, num_elem);
    
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_3 trabalho_3.cpp