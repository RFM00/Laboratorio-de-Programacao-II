#include <exception>
#include <iostream>

using std::exception;
using std::cout;

template <typename TC, typename TV>
class Dicio
{
private:
    struct Noh
    {
        TC chave;
        TV valor;
        Noh *pai = nullptr;
        Noh *esq = nullptr;
        Noh *dir = nullptr;
    };

    Noh *raiz;
    Noh *primeiro;
    Noh *ultimo;

public:
    class Iterador
    {
    private:
        Noh *n;

    public:
        Iterador(Noh *noh) : n(noh) {}

        void operator++() {
            TV valor = n->valor;
            while (true){
                if (n->dir != nullptr){
                    n = n->dir;
                        while (n->esq != nullptr)
                            n = n->esq;
                        break;
                }else{
                    
                    while (n->valor < valor){

                    }
                }
                
                if(n->valor < valor){
                    if (n->pai != nullptr){
                        n = n->pai;
                    }else{
                        n = nullptr;
                        break;
                    }
                }else if(n->dir == nullptr){

                }
                
                if(n->valor < valor)
                    continue;
                else 
                    else{
                        
                    }
            }
        }

        TV operator*() { return n->valor; }

        bool operator!=(const Iterador &i) { return n != i.n; }
    };

    Dicio() : raiz(nullptr), primeiro(nullptr) {}

    Iterador inserir(TC c, TV v)
    {
        Noh *n = new Noh;
        n->chave = c;
        n->valor = v;

        if(raiz == nullptr){
			raiz = n;
            primeiro = raiz;
            ultimo = raiz;
        }
		else{
            Noh *nohAtual = raiz;
			while(true){
                if(n->valor < nohAtual->valor){
                    if(nohAtual->esq == nullptr){
                        nohAtual->esq = n;
                        if(n->valor < primeiro->valor)
                            primeiro = nohAtual->esq;
                        n->pai = nohAtual;
                        break;
                    }
                    else
                        nohAtual = nohAtual->esq;
                }
                else{
                    if(nohAtual->dir == nullptr){
                        nohAtual->dir = n;
                        if(n->valor > ultimo->valor)
                            ultimo = nohAtual->dir;
                        n->pai = nohAtual;
                        break;
                    }
                    else
                        nohAtual = nohAtual->dir;
                }
            }
        }
        Iterador i(n);
        return i;
    }

    Iterador procurar (TC c)
    {
        Iterador i(nullptr);
        return i;
    }

    void remover (Iterador i)
    {

    }

    Iterador inicio()
    {
        Iterador i(primeiro);
        return i;
    }

    Iterador fim()
    {
        Iterador i(ultimo);
        return i;
    }
};

int main()
{
    try
    {
        Dicio<char, double> D;

        Dicio<char, double>::Iterador elemAdicionado = nullptr;
        elemAdicionado = D.inserir('a', 2);
        // cout << *elemAdicionado << '\n';

        elemAdicionado = D.inserir('b', 4);
        // cout << *elemAdicionado << '\n';
        
        elemAdicionado = D.inserir('c', 1);
        // cout << *elemAdicionado << '\n';
        
        elemAdicionado = D.inserir('d', 3);
        // cout << *elemAdicionado << '\n';

        auto inicio = D.inicio();
        auto fim = D.fim();
        cout << "Primeiro: " << *inicio << '\n';
        cout << "Ultimo: " << *fim << '\n';

        // Dicio<char, double>::Iterador fim = D.fim(); // ou "auto fim ..."
        
        // auto fim = D.fim();
        for (auto i = inicio; i != fim; ++i)
            cout << *i << '\n';
    }
    catch (const exception &e)
    {
        cout << "EXCEÇÃO: " << e.what() << '\n';

        return 1;
    }
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o dic dicionario.cpp