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
                if (n->dir != nullptr && n->dir->valor > valor){
                    n = n->dir;
                    while (n->esq != nullptr)
                        n = n->esq;
                    break;
                    
                }else{
                    if (n->pai != nullptr){
                        if(n->pai->esq == n){
                            n = n->pai;
                            break;
                        }else{
                            n = n->pai;
                        }
                    }else{
                        n = nullptr;
                        break;
                    }
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
        Iterador i(nullptr);
        return i;
    }
};

int main()
{
    try
    {
        Dicio<char, double> D;

        Dicio<char, double>::Iterador elemAdicionado = nullptr;
        elemAdicionado = D.inserir('a', 8);
        elemAdicionado = D.inserir('b', 9);
        elemAdicionado = D.inserir('c', 4);
        elemAdicionado = D.inserir('d', 6);
        elemAdicionado = D.inserir('a', 5);
        elemAdicionado = D.inserir('b', 7);
        elemAdicionado = D.inserir('a', 2);
        elemAdicionado = D.inserir('b', 3);
        elemAdicionado = D.inserir('b', 1);

        auto inicio = D.inicio();
        auto fim = D.fim();
        cout << "Primeiro: " << *inicio << '\n';
        // cout << "Ultimo: " << *fim << '\n';

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