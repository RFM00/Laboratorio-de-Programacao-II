#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
#include "huffman.h"

using namespace std;

// São 2 fluxos 

// Compactar

int lerArquivoCompactar(unsigned long long int frequencia[256], string nomeArquivo){
    // Abrir arquivo
    ifstream in("inputs/" + nomeArquivo);
    // Identificador do byte
    unsigned long long int byte;
    // Contador de quantidade de diferentes bytes
    int tamanhoHeap = 0;
    // Leitor de arquivo
    while(!in.eof()){
        byte = in.get();
        //Contador de frequência
        if(frequencia[byte] == 0)
            tamanhoHeap++;
        ++frequencia[byte];
    }
    // Fim do arquivo.
    in.close();
    return tamanhoHeap;
}

bool escreverArquivoCompactado(Huffman *huffman, string nomeArquivo, int tamanhoHuffman){
    // Criar arquivo
    ofstream out(nomeArquivo, ios::binary);
    // Dizer onde começa a leitura e até onde vai
    // Tem os detalhes dos tamanhos ainda
    out.write((const char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    out.write((const char*)&huffman, sizeof(huffman));

    // Writing the file folowing the huffman tree
    // ifstream in(nomeArquivo);
    // unsigned long long int b;

    // while(!in.eof()){
    //     b = in.get();
    //     out.write((char*)&b, sizeof(b));
    // }
    
    // in.close();
    out.close();
    return true;
}


// Descompactar

void lerArquivoDescompactar(){

}

void escreverArquivoDescompactado(){

}


#endif