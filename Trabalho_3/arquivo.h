#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
#include "huffman.h"

using namespace std;

// São 2 fluxos 

// Compactar

void CompactarLeitura(string nomeArquivo, unsigned long long int frequencia[256], int &tamanhoHeap, int &totalOriginalBits){
    // Abrir arquivo
    ifstream in("inputs/" + nomeArquivo);
    // Identificador do byte
    unsigned char byte;
    // Inicializando variáveis recebidas
    for (int i = 0; i < 256; i++) frequencia[i] = 0;
    tamanhoHeap = 0, totalOriginalBits = 0;
    // Leitor de arquivo
    while(!in.eof()){ // Enquanto nao for o fim do arquivo
        byte = in.get();
        //Contador de frequência
        if(frequencia[byte] == 0)
            tamanhoHeap++;
        ++frequencia[byte];
        ++totalOriginalBits; // Contador do total bits
    }
    // Fim do arquivo.
    in.close();
}

bool CompactarEscrita(string nomeArquivo, Huffman *huffman, int tamanhoHuffman){
    // Criar arquivo
    ofstream out(nomeArquivo, ios::binary);
    // Dizer onde começa a leitura e até onde vai
    // Tamanho da árvore em inteiro
    out.write((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    // Árvore de Huffman
    out.write((char*)&huffman, ((2 * tamanhoHuffman) - 1) * sizeof(Huffman));
    
    out.close();
    return true;
}


// Descompactar

void DescompactarLeitura(string nomeArquivo, Huffman *huffman){
    ifstream in("inputs/" + nomeArquivo);

    // Identificador do byte
    // unsigned char byte;
    // Contador de quantidade de diferentes bytes
    int tamanhoHuffman;

    // Ler a primeira informação do arquivo, que é o tamanho da arvore
    in.read((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    cout << "Tamanho Huffman " << tamanhoHuffman << endl;

    // Criar a árvore do tamanho da árvore referente
    huffman = new Huffman[tamanhoHuffman];
    // Ler para arvore
    in.read((char*)&huffman, ((2 * tamanhoHuffman) - 1) * sizeof(Huffman));
    
    cout << "Arvore recuperada do arquivo" << endl;
    imprimirArvoreHuffman(huffman, tamanhoHuffman);
    
    in.close();
}

// void DescompactarEscrita(string nomeArquivo, Huffman *huffman){

// }


#endif