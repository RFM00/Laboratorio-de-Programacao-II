#ifndef HUFFMAN_H
#define HUFFMAN_H

using namespace std;

struct Huffman{
    unsigned int elem = '\0';
    int freq = 0;
    int dir = -1;
    int esq = -1;
};

void criarArvore(Huffman *noh, unsigned long long int *frequencia){
    int j = 0;
    for (int i = 0; i < 256; i++){
        // Apenas elementos que ocorrem
        if (frequencia[i] != 0){
            noh[j].elem = i;
            noh[j].freq = frequencia[i];
            cout << "HuffmanTree " << j <<" : " << noh[j].elem << ", " << noh[j].freq << endl;
            j++;
        }
    }
}

void imprimirArvoreHuffman(Huffman *noh, int tamanho){
    cout << '\n';
    for (int i = 0; i < tamanho; i++){
        cout << "HuffmanTree " << i <<" : " << noh[i].elem << ", " << noh[i].freq 
        << "| " << noh[i].esq << ", " << noh[i].dir << endl;
    }
}

#endif