#include <iostream>
#include "../Trabalho_2/gerador.h"
#include "../Trabalho_2/buscador.h"

using namespace std;

struct huffman_no{
    char elem = '\0';
    int freq = 0;
    int dir = -1;
    int esq = -1;
};

struct heap_no{
    int freq;
    int indice;
};

void trocar(heap_no *a, heap_no *b){
    heap_no aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void heapfy(heap_no *heap, int i, int last){
    while(i < last/2){
        if(heap[i].freq > heap[(2*i) + 1].freq){
            trocar(&heap[i], &heap[(2 * i) + 1]);
        }
        if(heap[i].freq > heap[(2*i) + 2].freq){
            trocar(&heap[i], &heap[(2 * i) + 2]);
        }
        heapfy(heap, (2*i) + 1, last);
        i = (2*i) + 2;
    }
}


int ocorrencias(int *saida){
    int ocr = 0;
    while (*saida != -1){
        ocr++;
        saida++;
    }
    return ocr;
}

int *frequencias(const char *texto, int tamanho, int variedade){
    char *padrao = new char[2];
    padrao[1] = '\0';

    int *frequencia = new int[variedade];
    int *saida = new int[tamanho];
    
    for(int i = 0; i < variedade; i++) *(frequencia + i) = 0;
    for(int i = 0; i < tamanho; i++) *(saida + i) = -1;
    
    for(int i = 0; i < variedade; i++){
        padrao[0] = v[i];
        buscar_KMP(texto, padrao, saida);
        frequencia[i] = ocorrencias(saida);
        for(int i = 0; i < tamanho; i++) *(saida + i) = -1;
    }
    delete saida;
    return frequencia;
}

void imprimirArvoreHuffman(huffman_no *no, int tamanho){
    for (int i = 0; i < tamanho; i++){
        cout << "\nElemento: " << no[i].elem;
        cout << "\nFrequencia: " << no[i].freq;
    }
}

void imprimirHeap(heap_no *no, int tamanho){
    for (int i = 0; i < tamanho; i++){
        cout << "\nIndice: " << no[i].indice;
        cout << "\nFrequencia: " << no[i].freq;
    }
}

int main() {

    int tamanho = 10, variedade = 6;
    // huffman_no *huffman_tree = new huffman_no[2*tamanho - 1];
    // heap_no *heap_min = new heap_no[tamanho];

    // 1ª gerar sequencia aleatório
    // 2ª contar a frequencia
    // 3ª preencher n da huffman_tree e heap_min com a frequencia obtida
    // 4ª completar a huffman_tree com a estratégia da remoção dupla no
    // heap_min

    // 1ª

    const char *texto = gerador_aleatorio(tamanho, variedade);
    int *frequencia = frequencias(texto, tamanho, variedade);
    
    cout << "Texto" << endl;
    for (int i = 0; i < tamanho; i++) cout << *(texto + i) << " ";
    cout << endl;

    cout << "Frequencia" << endl;
    for (int i = 0; i < variedade; i++) cout << *(frequencia + i) << " ";
    cout << endl;

    int num_elem = 0;
    for (int i = 0; i < variedade; i++) 
        if (*(frequencia + i) != 0)
            num_elem++;


    cout << "Num Elem: " << num_elem << endl;

    huffman_no *arvore_huffman = new huffman_no[2 * num_elem - 1];
    
    int j = 0;
    for (int i = 0; i < variedade; i++){
        if (frequencia[i] != 0){
            arvore_huffman[j].elem = v[i];
            arvore_huffman[j].freq = frequencia[i];
            j++;
        }
    }

    // Perfeito, comportamento esperado.
    imprimirArvoreHuffman(arvore_huffman, 2 * num_elem - 1);

    heap_no *heap = new heap_no[num_elem];
    j = 0;
    for (int i = 0; i < variedade; i++){
        if (frequencia[i] != 0){
            heap[j].indice = j;
            heap[j].freq = frequencia[i];
            j++;
        }
    }

    // Perfeito, comportamento esperado.
    imprimirHeap(heap, num_elem);
    heapfy(heap, num_elem, num_elem);
    cout << "\nHeap Após heapfy\n";
    imprimirHeap(heap, num_elem);
    
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_3 trabalho_3.cpp