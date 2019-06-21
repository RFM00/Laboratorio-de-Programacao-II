#include <exception>
#include <iostream>

using std::exception;
using std::cout;

typedef double TC; typedef float TV;
struct Noh
{
    TC chave;
    TV valor;
    Noh *esq, *dir, *pai;
    int h;
};

struct DicAVL { 
    Noh *raiz; 
};

void inicializar (DicAVL &D){
    D.raiz = nullptr;
}

Noh* inserir (DicAVL &D, TC c, TV v){
    if (D.raiz != nullptr)
        return inserir(D.raiz, c, v);
    else{
        D.raiz = new Noh;
        D.raiz->chave = c;
        D.raiz->valor = v;
        return D.raiz;
    }
}

Noh* inserir(Noh *n, TC c, TV v) {
    if (n == nullptr) {
        n = new Noh;
        n->chave = c;
        n->valor = v;
        cout << c << " Chave" << '\n';
        cout << v << " Valor" << '\n';
        return n;
    } else if (v < n->valor) {
        n->esq = inserir(n->esq, c, v);
        // n = balancear(n);
    } else if (v >= n->valor) {
        n->dir = inserir(n->dir, c, v);
        // n = balancear(n);
    }
    return n;
}

Noh* procurar (DicAVL &D, TC c){
    if (D.raiz != nullptr)
        return procurar(D.raiz, c);
    else
        return nullptr;
}

Noh* procurar(Noh *n, TC c){
    if (n == nullptr || c == n->chave)
        return n;
    if (c < n->valor)
        return procurar(n->esq, c);
    else
        return procurar(n->dir, c);
}

void remover (DicAVL &D, Noh *n);

void terminar (DicAVL &D);

int main(){
    // DicAVL D;
    // inicializar(D);

    // cout << inserir(D, 1, 10) << '\n';
    // cout << inserir(D, 2, 20) << '\n';
    // cout << procurar(D, 2) << '\n';
    // remover(D, procurar(D, 2));

    // terminar(D);
}

// g++ -Wall -Wextra -std=c++17 -pedantic -o avl avl.cpp