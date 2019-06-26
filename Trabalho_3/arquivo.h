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

bool CompactarEscrita(string nomeArquivoOriginal, string nomeArquivoCompactado, Huffman *huffman, int tamanhoHuffman, int totalOriginalBits){
    // Criar arquivo
    ifstream in("inputs/" + nomeArquivoOriginal);
    ofstream out("inputs/" + nomeArquivoCompactado, ios::binary);
    // Dizer onde começa a leitura e até onde vai
    // Tamanho da árvore em inteiro
    cout << "Tamanho do huffman original = " << tamanhoHuffman << endl;
    out.write((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    // Árvore de Huffman
    out.write((char*)&huffman, tamanhoHuffman * sizeof(Huffman));
    // Total original de Bits
    out.write((char*)&totalOriginalBits, sizeof(totalOriginalBits));
    
    // Arquivo Compactado
    // Codificador
    string code[256];
    string aux;
    Huffman *pai, *raiz = huffman + tamanhoHuffman - 1;
    int count = 0;
    while (count <= (tamanhoHuffman - 1) / 2 ){
        if (raiz->esq != -1){
            aux += '0';
            pai = raiz;
            raiz = huffman + raiz->esq;
        }else if (raiz->dir != -1){
            aux += '1';
            pai = raiz;
            raiz = huffman + raiz->dir;
        }else {
            if (huffman[pai->esq].elem == raiz->elem)
                pai->esq = -1;
            else
                pai->dir = -1;

            if (raiz->elem == '\0'){
                raiz = huffman + tamanhoHuffman - 1;
                aux.clear();
                continue;
            }
            code[raiz->elem].append(aux);
            aux.clear();
            raiz = huffman + tamanhoHuffman - 1;
            count++;
        }
    }

    cout << "Codificacao" << endl;
    for (int i = 0; i < 256; i++){
        if(!code[i].empty())
            cout << (unsigned char)i << ": " << code[i] << endl;
    }
    cout << endl;

    
    unsigned char bit;
    while(!in.eof()){
        bit = in.get();
        for (unsigned int i = 0; i < code[bit].size(); i++){
            out.write((char *)&code[bit][i], sizeof(code[bit][i]));
            cout << code[bit][i] << ": " << sizeof(code[bit][i]) << endl;
        }
    }
    cout << endl;

    in.close();
    out.close();
    return true;
}


// Descompactar

void Descompactar(string nomeArquivoCompactado, string nomeArquivoOriginal){
    ifstream in("inputs/" + nomeArquivoCompactado);
    ofstream out(nomeArquivoOriginal, ios::binary);


    int tamanhoHuffman, totalOriginalBits;
    // Ler a primeira informação do arquivo, que é o tamanho da arvore
    in.read((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    cout << "Tamanho do huffman recuperado = " << tamanhoHuffman << endl;

    // Criar a árvore do tamanho da árvore referente
    Huffman *huffman = new Huffman[tamanhoHuffman];
    // Ler para arvore
    in.read((char*)&huffman, tamanhoHuffman * sizeof(Huffman));
    
    cout << "Arvore recuperada do arquivo" << endl;
    cout << "Tamanho do huffman recuperado = " << tamanhoHuffman << endl;
    imprimirArvoreHuffman(huffman, tamanhoHuffman);

    // Ler total Original de Bits
    in.read((char *)&totalOriginalBits, sizeof(totalOriginalBits));
    // Ler parte compactada
    Huffman *raiz = huffman + tamanhoHuffman - 1;
    unsigned char bit;
    int count = 0;
    while(!in.eof() && count < totalOriginalBits){
        bit = in.get();
        if(raiz->elem == '\0'){
            if(bit == 0)
                raiz = huffman + raiz->esq;
            else
                raiz = huffman + raiz->dir;
        }else
            out.write((char *)&raiz->elem, sizeof(raiz->elem));
        count++;
    }

    in.close();
    out.close();
}


#endif