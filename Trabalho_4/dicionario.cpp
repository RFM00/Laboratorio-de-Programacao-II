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
    Noh *primeiro;

public:
    class Iterador
    {
    private:
        Noh *n;

    public:
        Iterador(Noh *noh) : n(noh) {}

        void operator++() { 
            // if (n->dir != nullptr){
            //     n = n->dir;
            // }else{
            //     Noh *aux = raiz;
            //     while (true) {
            //         if(n->valor < raiz->valor){
            //             if(raiz->esq == n){
            //                 n = raiz->esq;
            //                 break;
            //             }else{
            //                 raiz = raiz->esq;
            //             }
            //         }else{
            //             if(raiz->dir == n){
            //                 n = raiz->dir;
            //                 break;
            //             }else{
            //                 raiz = raiz->dir;
            //             }
            //         }
            //     }
            //     raiz = aux;
            // }
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
            Noh *aux = raiz;
			while(true){
                if(v < raiz->valor){
                    if(raiz->esq == nullptr){
                        raiz->esq = n;
                        primeiro = n;
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
        elemAdicionado = D.inserir('a', 1.1);
        elemAdicionado = D.inserir('b', 2.2);
        elemAdicionado = D.inserir('c', 3.3);

        cout << *elemAdicionado << '\n';

        auto primeiro = D.inicio();
        cout << "Primeiro: " << *primeiro << '\n';

        // Dicio<char, double>::Iterador fim = D.fim(); // ou "auto fim ..."
        
        // auto fim = D.fim();
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