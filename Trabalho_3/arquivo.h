#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
#include "huffman.h"

using namespace std;

// São 2 fluxos 

// Compactar

void CompactarLeitura(string nomeArquivo, unsigned long long int frequencia[256], int &numeroElementos, int &totalCaracteresOriginal){
    // Abrir arquivo
    ifstream in("inputs/" + nomeArquivo, ios::binary);
    // Identificador do byte
    unsigned char byte;
    // Inicializando variáveis recebidas
    for (int i = 0; i < 256; i++) frequencia[i] = 0;
    numeroElementos = 0, totalCaracteresOriginal = 0;
    // Leitor de arquivo
    while(!in.eof()){ // Enquanto nao for o fim do arquivo
        byte = in.get();
        if(frequencia[byte] == 0)
            numeroElementos++;
        ++frequencia[byte];
        ++totalCaracteresOriginal;
    }
    // Fim do arquivo.
    in.close();
}

void BFS(string code[256], string &aux, Huffman *huffman, int i){
    if (!(huffman[i].dir == -1 && huffman[i].esq == -1)){
        aux += '0';
        BFS(code, aux, huffman, (huffman + i)->esq);
        aux += '1';
        BFS(code, aux, huffman, (huffman + i)->dir);
    } else 
        code[huffman[i].elem].append(aux);
    aux.pop_back();
}

void codificador(string code[256], Huffman *huffman, int numeroElementos){
    string aux;

    BFS(code, aux, huffman, 2 * numeroElementos - 2);

    for (int i = 0; i < 256; i++)
        if(!code[i].empty())
            cout << "Byte: " << (unsigned char)i << " Code: " << code[i] << endl;
}



void CompactarEscrita(string nomeArquivoOriginal, string nomeArquivoCompactado){
    // Vetor de frequências por bytes
    unsigned long long int frequencia[256];
    // Variáveis com tamanhos correspondentes as estruturas utilizadas
    int numeroElementos, tamanhoHuffman, totalCaracteresOriginal;

    // Ler arquivo a ser compactado
    // Preencherá as variáveis enviadas como parâmetros com respectivos valores
    CompactarLeitura(nomeArquivoOriginal, frequencia, numeroElementos, totalCaracteresOriginal);
    
    // Criar Árvore de Huffman com tamanho adequado
    // Tamanho da arvore é 2 * heap - 1 nohs no total
    tamanhoHuffman = 2 * numeroElementos - 1;
    Huffman *huffman = new Huffman[tamanhoHuffman];
    criarArvore(huffman, frequencia);
    
    // Criar heap contendo os elementos da árvore de huffman, com tamanho sendo o numero de elementos
    Heap *heap = new Heap[numeroElementos];
    criarHeap(heap, huffman, numeroElementos);

    // Utilizar algoritmo de Huffman para construir a Árvore desejada
    algoritmoHuffman(huffman, heap, numeroElementos);
    imprimirArvoreHuffman(huffman, tamanhoHuffman);

    // Criar arquivo
    ifstream in("inputs/" + nomeArquivoOriginal, ios::binary);
    ofstream out("hufs/" + nomeArquivoCompactado, ios::binary);

    // Tamanho da árvore em inteiro
    out.write((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    // Árvore de Huffman
    out.write((char*)huffman, tamanhoHuffman * sizeof(Huffman));
    // Total original de Bits
    out.write((char*)&totalCaracteresOriginal, sizeof(totalCaracteresOriginal));

    // Codificador, BFS 
    string code[256];
    codificador(code, huffman, numeroElementos);

    unsigned char b, buffer = 0; // buffer = 00000000 bits
    unsigned count = 0;
    while(!in.eof()){
        b = in.get();
        for (unsigned int i = 0; i < code[b].size(); i++){
            buffer <<= 1; // Espaço para o proximo bit
            if (code[b][i] == '1') 
                buffer |= 1; // Se for 1, altera.
            count++;
            if (count == 8) {
                out.write((char*)&buffer, sizeof(buffer));
                buffer = 0;
                count = 0;
            }
        }
    }
    if (count != 0) {
        buffer <<= (8 - count);
        out.write((char*)&buffer, sizeof(buffer));
    }

    in.close();
    out.close();
}


// Descompactar

bool getBit(unsigned char byte, int posicao){
    return (byte >> posicao) & 0x1;
}

void Descompactar(string nomeArquivoCompactado, string nomeArquivoOriginal){
    ifstream in("hufs/" + nomeArquivoCompactado, ios::binary);
    ofstream out("outputs/" + nomeArquivoOriginal, ios::binary);

    int tamanhoHuffman, totalCaracteresOriginal;

    // Ler a primeira informação do arquivo, que é o tamanho da arvore
    in.read((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    // Ler Árvore
    Huffman *huffman = new Huffman[tamanhoHuffman];
    in.read((char*)huffman, tamanhoHuffman * sizeof(Huffman));
    // Ler total Original de Bits
    in.read((char *)&totalCaracteresOriginal, sizeof(totalCaracteresOriginal));

    // Ler parte compactada
    Huffman *raiz = huffman + tamanhoHuffman - 1;
    unsigned char byte;
    int totalCaracteresGravados = 0, posicao = 0;
    byte = in.get();

    while(totalCaracteresGravados < totalCaracteresOriginal - 1){
        if (!(raiz->dir == -1 && raiz->esq == -1)){
            if (!getBit(byte, 7 - posicao))
                raiz = huffman + raiz->esq;
            else
                raiz = huffman + raiz->dir;
            posicao++;
            if (posicao == 8){
                byte = in.get();     
                posicao = 0;
            }
        } else {
            out.write((char *)&raiz->elem, sizeof(raiz->elem));
            raiz = huffman + tamanhoHuffman - 1;
            totalCaracteresGravados++;
        }
    }
    
    in.close();
    out.close();
}


#endif