#include <exception>
#include <iostream>

using std::exception;
using std::cout;

struct Noh {
    int valor;
    int fatorBalanco;
    Noh *esq = nullptr;
    Noh *dir = nullptr;
    Noh *pai = nullptr;
};

class AVL
{
private:
    Noh *raiz = nullptr;
public:
    AVL() : raiz(nullptr) {};
    ~AVL() { delete raiz; }

    int getAltura() {
        
    }

    void rotacaoEsquerda(Noh *n){
        Noh *nDir = n->dir;
    }

    void inserir(int v){
        if (raiz != nullptr)
            inserir(raiz, v);
        else{
            raiz = new Noh;
            raiz->valor = v;
        }
    }

    Noh *inserir(Noh *n, int v) {
        if (n == nullptr) {
            n = new Noh;
            n->valor = v;
            cout << v << " Inserido" << '\n';
            return n;
        } else if (v < n->valor) {
            n->esq = inserir(n->esq, v);
            // n = balancear(n);
        } else if (v >= n->valor) {
            n->dir = inserir(n->dir, v);
            // n = balancear(n);
        }
        return n;
    }


    Noh *procurar(int v){
        if (raiz != nullptr)
            return procurar(raiz, v);
        else
            return nullptr;
    }

    Noh *procurar(Noh *n, int v){
        if (n == nullptr || v == n->valor)
            return n;
        if (v < n->valor)
            return procurar(n->esq, v);
        else
            return procurar(n->dir, v);
    }

};



int main(){
    AVL avl;

    avl.inserir(3);
    avl.inserir(5);
    avl.inserir(1);
    avl.inserir(4);
    avl.inserir(2);
    avl.inserir(6);

    Noh *n = avl.procurar(1);

    cout << n->valor;

}

// g++ -Wall -Wextra -std=c++17 -pedantic -o avl avl.cpp