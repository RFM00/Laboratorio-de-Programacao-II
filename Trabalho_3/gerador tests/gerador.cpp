#include <iostream>
#include <fstream>

using namespace std;

struct Noh
{
    int num;
};


int main(){
    // ofstream out("bytes.txt", ios::binary);

    // unsigned char byte;
    // for(int i = 0; i < 256; i++){
    //     byte = i;
    //     out.write((char*)&byte, sizeof(byte));
    // }
    // out.close();

    ifstream in("bytes.txt", ios::binary);

    for (int i = 0; i < 256; i++){
        if (in.get() == i)
            cout << "o caracter " << (unsigned char)i << " eh o byte: " << i << endl;
    }

    unsigned char byte;
    while (in.eof())
    {
        byte = in.get();
        cout << byte << endl;
    }
    
    in.close();

    return 0;
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o gerador gerador.cpp