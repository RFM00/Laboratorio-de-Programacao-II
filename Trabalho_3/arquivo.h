#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
#include "huffman.h"

using namespace std;

int lerArquivo(unsigned long long int frequencia[256]){
    // Abrir arquivo
    ifstream file("inputs/text.txt");

    // Identificador do byte
    unsigned long long int byte;

    // Contador de quantidade de diferentes bytes
    int tamanhoHeap = 0;

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
    return tamanhoHeap;
}

bool escreverArquivo(Huffman *huffman, string file_name){
    
    ofstream out(file_name, ios::binary);

    out.write((char*)&huffman, sizeof(huffman));

    // Writing the file folowing the huffman tree
    ifstream in(file_name);
    unsigned long long int b;

    while(!in.eof()){
        b = in.get();
        out.write((char*)&b, sizeof(b));
    }
    
    in.close();
    out.close();
    return true;
}

#endif