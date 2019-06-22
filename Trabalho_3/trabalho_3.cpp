#include <iostream>
#include <fstream>
#include "heap.h"
#include "huffman.h"

using namespace std;

int main() {
    // Vetor de frequências por bytes
    unsigned long long int frequencia[256];
    for (int i = 0; i < 256; i++) frequencia[i] = 0;

    // Abrir arquivo
    ifstream file("text.txt");                                                                                                                                                                                                                                                                            

    // Identificador do byte
    unsigned long long int byte;

    // Contador de quantidade de diferentes bytes
    int tamanhoHeap = 0, tamanhoHuffman = 0;

    // Leitor de arquivo
    while(!file.eof()){
        byte = file.get();
        //Contador de frequência
        if(frequencia[byte] == 0)
            tamanhoHeap++;
        ++frequencia[byte];
    }

    // Fim do arquivo.
    file.close();

    tamanhoHuffman = 2 * tamanhoHeap - 1;

    // Criar Árvore de Huffman
    Huffman *huffman = new Huffman[tamanhoHuffman];
    criarArvore(huffman, frequencia);

    // Criar heap contendo os elementos da árvore de huffman
    Heap *heap = new Heap[tamanhoHeap];
    criarHeap(heap, huffman, tamanhoHeap);


    // Remove os 2 minimos do heap
    // Insere na arvore com freq = soma das freqs dos nos que entraram
    // e filho esquerdo e direito referentes a quem foi removido,
    // Cria um novo no para inserir no heap, onde a freq é a soma, 
    // e o indice é o indice que foi inserido na arvore de huffman

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
        huffman[indiceHuffmanAtual].esq = min[0].indice;
        huffman[indiceHuffmanAtual].dir = min[1].indice;
        tamanhoHeap++;
        buildMinHeap(heap, tamanhoHeap);
        imprimirHeap(heap, tamanhoHeap);
    }
    imprimirArvoreHuffman(huffman, tamanhoHuffman);
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_3 trabalho_3.cpp