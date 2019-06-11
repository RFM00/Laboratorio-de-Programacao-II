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
        Noh *esq = nullptr;
        Noh *dir = nullptr;
    };

    Noh *raiz;

public:
    class Iterador
    {
    private:
        Noh *n;

    public:
        Iterador(Noh *noh) : n(noh) {}

        void operator++() { n = n->prox; }

        TV operator*() { return n->valor; }

        bool operator!=(const Iterador &i) { return n != i.n; }
    };

    Dicio() : raiz(nullptr) {}

    Iterador adicionar(TC c, TV v)
    {
        Noh *n = new Noh;
        n->chave = c;
        n->valor = v;

        if(raiz == nullptr) // verifica se a árvore está vazia
			raiz = n; // cria um novo nó
		else{
            Noh *aux = raiz;
			while(raiz != nullptr){
                if(v < raiz->valor){
                    if(raiz->esq == nullptr){
                        raiz->esq = n;
                        break;
                    }
                    else
                        raiz = raiz->esq;
                }
                else{
                    if(raiz->dir == nullptr){
                        raiz->dir = n;
                        break;
                    }
                    else
                        raiz = raiz->dir;
                }
            }
            raiz = aux;
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
        Iterador i(raiz);
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
        elemAdicionado = D.adicionar('a', 1.1);
        elemAdicionado = D.adicionar('b', 2.2);
        // D.adicionar('c', 3.3);

        cout << *elemAdicionado << '\n';

        // Dicio<char, double>::Iterador fim = D.fim(); // ou "auto fim ..."

        // for (auto i = D.inicio(); i != fim; ++i)
        //     cout << *i << '\n';
    }
    catch (const exception &e)
    {
        cout << "EXCEÇÃO: " << e.what() << '\n';

        return 1;
    }
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o executavel_trabalho_4 trabalho_4.cpp