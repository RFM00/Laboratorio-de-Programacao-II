#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream out("bytes.txt", ios::binary);

    unsigned char byte;
    for(int i = 0; i < 256; i++){
        byte = i;
        out.write((char*)&byte, sizeof(byte));
    }
    out.close();

    ifstream in("bytes.txt", ios::binary);

    for (int i = 0; i < 256; i++){
        if (in.get() == i)
            cout << "o caracter \\0 eh o byte: " << i << endl;
    }
    in.close();

    return 0;
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o gerador gerador.cpp