#include <exception>

using std::exception;

#include <iostream>

using std::cout;

template <typename T>
class Conj
{
    private:

    struct Noh { T elem; Noh *prox; };

    Noh *primeiro;

    public:

    class Iterador
    {
        private:

        Noh *n;

        public:

        Iterador (Noh *noh) : n(noh) { }

        void operator++ () { n = n->prox; }

        T operator* () { return n->elem;}

        bool operator!= (const Iterador &i) { return n != i.n; }
    };

    Conj() : primeiro(nullptr) { }

    void adicionar (T e)
    {
        Noh *n = new Noh;  n->elem = e;  n->prox = primeiro;

        primeiro = n;
    }

    Iterador inicio () { Iterador i(primeiro); return i; }

    Iterador fim () { Iterador i(nullptr); return i; }
};

int main ()
{
try
{
    Conj<double> C;

    C.adicionar(1.1);
    C.adicionar(2.2);
    C.adicionar(3.3);

    Conj<double>::Iterador fim = C.fim(); // ou "auto fim ..."

    for (auto i = C.inicio(); i != fim; ++i)
    cout << *i << '\n';
}
catch (const exception &e)
{
    cout << "EXCEÇÃO: " << e.what() << '\n';

    return 1;
}
}