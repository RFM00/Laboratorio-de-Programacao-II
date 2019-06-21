#ifndef HUFFMAN_H
#define HUFFMAN_H

using namespace std;

struct Huffman{
    unsigned int elem = '\0';
    int freq = 0;
    int dir = -1;
    int esq = -1;
};

void imprimirArvoreHuffman(Huffman *noh, int tamanho){
    for (int i = 0; i < tamanho; i++){
        cout << "\nElemento: " << noh[i].elem;
        cout << "\nFrequencia: " << noh[i].freq;
    }
}

#endif