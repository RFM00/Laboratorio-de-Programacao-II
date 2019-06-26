#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
#include "huffman.h"

using namespace std;

// São 2 fluxos 

// Compactar

void CompactarLeitura(string nomeArquivo, unsigned long long int frequencia[256], int &numeroElementos, int &totalOriginalBits){
    // Abrir arquivo
    ifstream in("inputs/" + nomeArquivo);
    // Identificador do byte
    unsigned char byte;
    // Inicializando variáveis recebidas
    for (int i = 0; i < 256; i++) frequencia[i] = 0;
    numeroElementos = 0, totalOriginalBits = 0;
    // Leitor de arquivo
    while(!in.eof()){ // Enquanto nao for o fim do arquivo
        byte = in.get();
        //Contador de frequência
        if(frequencia[byte] == 0)
            numeroElementos++;
        ++frequencia[byte];
        ++totalOriginalBits; // Contador do total bits
    }
    // Fim do arquivo.
    in.close();
}

void codificador(string code[256], Huffman *huffman, int numeroElementos){
    int tamanhoHuffman = 2 * numeroElementos - 1;
    string aux;
    Huffman *pai, *raiz = huffman + tamanhoHuffman - 1;
    int count = 0;
    while (count < numeroElementos){
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
    // cout << "Codificacao" << endl;
    // for (int i = 0; i < 256; i++){
    //     if(!code[i].empty())
    //         cout << (unsigned char)i << ": " << code[i] << endl;
    // }
    // cout << endl;
}

void CompactarEscrita(string nomeArquivoOriginal, string nomeArquivoCompactado){
    // Vetor de frequências por bytes
    unsigned long long int frequencia[256];
    // Variáveis com tamanhos correspondentes as estruturas utilizadas
    int numeroElementos, tamanhoHuffman, totalOriginalBits;

    // Ler arquivo a ser compactado
    // Preencherá as variáveis enviadas como parâmetros com respectivos valores
    CompactarLeitura("text.txt", frequencia, numeroElementos, totalOriginalBits);
    
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
    ifstream in("inputs/" + nomeArquivoOriginal);
    ofstream out("inputs/" + nomeArquivoCompactado, ios::binary);

    // Tamanho da árvore em inteiro
    // cout << "Tamanho do huffman original = " << tamanhoHuffman << endl;
    out.write((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));
    // Árvore de Huffman
    out.write((char*)huffman, tamanhoHuffman * sizeof(Huffman));
    // Total original de Bits
    out.write((char*)&totalOriginalBits, sizeof(totalOriginalBits));

    // Codificador, BFS 
    string code[256];
    codificador(code, huffman, numeroElementos);
    
    // Arquivo codificado
    cout << "Codificacao" << endl;
    unsigned char bit;
    while(!in.eof()){
        bit = in.get();
        for (unsigned int i = 0; i < code[bit].size(); i++){
            // Bit a Bit
            out.write((char *)&code[bit][i], sizeof(code[bit][i]));
            cout << (unsigned char)code[bit][i];
        }
    }
    cout << endl;

    in.close();
    out.close();

    cout << "Compactacao Completa" << endl;
    cout << "Tamanho da Arvore de Huffman: " << tamanhoHuffman << endl;
    cout << "Arvore de Huffman" << endl;
    imprimirArvoreHuffman(huffman, tamanhoHuffman);
    cout << "Numero de Bits Original: " << totalOriginalBits << endl;
    cout << "Codificao do arquivo: " << endl;
    
    cout << endl;
}


// Descompactar

void Descompactar(string nomeArquivoCompactado, string nomeArquivoOriginal){
    ifstream in("inputs/" + nomeArquivoCompactado, ifstream::binary);
    ofstream out(nomeArquivoOriginal, ios::binary);

    int tamanhoHuffman, totalOriginalBits;
    // Ler a primeira informação do arquivo, que é o tamanho da arvore
    in.read((char*)&tamanhoHuffman, sizeof(tamanhoHuffman));

    // Criar a árvore do tamanho da árvore referente
    Huffman *huffman = new Huffman[tamanhoHuffman];
    // Ler para arvore
    // Lendo a arvore errado.
    in.read((char*)huffman, tamanhoHuffman * sizeof(Huffman));
    cout << "Tamanho da Arvore de Huffman Recuperado: " << tamanhoHuffman << endl;

    cout << "Arvore Recuperada" << endl;
    imprimirArvoreHuffman(huffman, tamanhoHuffman);
    cout << endl;
    // Ler total Original de Bits
    in.read((char *)&totalOriginalBits, sizeof(totalOriginalBits));
    cout << "Numero de Bits Original Recuperado: " << totalOriginalBits << endl;

    // Ler parte compactada
    Huffman *raiz = huffman + tamanhoHuffman - 1;
    unsigned char bit;
    int count = 0;
    cout << "Codificacao Recuperada: " << endl;
    while(!in.eof()){ // && count < totalOriginalBits
        bit = in.get();
        cout << "Bit: "<< (unsigned char)bit << endl;;

        if(raiz->elem == '\0'){
            if(bit == '0'){
                raiz = huffman + raiz->esq;
                cout << "Foi para esquerda" << endl;
            }
            else{
                raiz = huffman + raiz->dir;
                cout << "Foi para direita" << endl;
            }
        }else{
            out.write((char *)&raiz->elem, sizeof(raiz->elem));
            raiz = huffman + tamanhoHuffman - 1;
            // cout << (char)raiz->elem;
        }
        count++;
    }

    in.close();
    out.close();
}


#endif