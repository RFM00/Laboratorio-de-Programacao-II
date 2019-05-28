#include <iostream>
#include "../Trabalho_2/gerador.h"
#include "../Trabalho_2/buscador.h"

using namespace std;

struct huffman_no{
    char elem = '\0';
    int freq;
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

// i = numero de nos
void heapfy(heap_no *heap, int m){
    int i = m;
    while (i >= 2 && heap[i / 2].freq > heap[i].freq){
        trocar(&heap[1/2], &heap[i]);
        i = i / 2;
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

int *frequencias(char *texto, int tamanho, int variedade){
    char *padrao = new char[2];
    padrao[1] = '\0';

    int *frequencia = new int[variedade];
    int *saida = new int[tamanho];
    
    for(int i = 0; i < variedade; i++) *(frequencia + i) = 0;
    for(int i = 0; i < tamanho; i++) *(saida + i) = -1;
    
    for(int i = 0; i < variedade; i++){
        padrao[0] = dicionario(i);
        buscar_KMP(texto, padrao, saida);
        frequencia[i] = ocorrencias(saida);
        for(int i = 0; i < tamanho; i++) *(saida + i) = -1;
    }
    delete saida;
    return frequencia;
}

int main() {

    int tamanho = 10, variedade = 26;
    // huffman_no *huffman_tree = new huffman_no[2*tamanho - 1];
    // heap_no *heap_min = new heap_no[tamanho];

    // 1ª gerar sequencia aleatório
    // 2ª contar a frequencia
    // 3ª preencher n da huffman_tree e heap_min com a frequencia obtida
    // 4ª completar a huffman_tree com a estratégia da remoção dupla no
    // heap_min

    // 1ª

    char *texto = gerador_aleatorio(tamanho, variedade);
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
    
    huffman_no *arvore_huffman = new huffman_no[2*num_elem - 1];
    
    int j = 0;
    for (int i = 0; i < variedade; i++){
        if (frequencia[i] != 0){
            arvore_huffman[j].elem = dicionario(i);
            arvore_huffman[j].freq = frequencia[i];
            j++;
        }
    }

    heap_no *heap = new heap_no[num_elem];

    for (int i = 0; i < variedade; i++){
        if (frequencia[i] != 0)
            heap[i].freq = frequencia[i];
    }
    
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_3 trabalho_3.cpp