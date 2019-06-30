#include <iostream>
#include <fstream>

using namespace std;

struct Huffman{
    unsigned char elem;
    unsigned long long int freq;
    // short int dir = -1;
    // short int esq = -1;
};

void print_byte_as_bits(char val) {
  for (int i = 7; 0 <= i; i--) {
    printf("%c", (val & (1 << i)) ? '1' : '0');
  }
  cout << endl;
}


bool getBit(unsigned char byte, int position) // position in range 0-7
{
    return (byte >> position) & 0x1;
}

int main(){
    // ofstream out("bytes.txt", ios::binary);

    // unsigned char byte;
    // for(int i = 0; i < 256; i++){
    //     byte = i;
    //     out.write((char*)&byte, sizeof(byte));
    // }
    // out.close();

    // ifstream in("bytes.txt", ios::binary);

    // for (int i = 0; i < 256; i++){
    //     if (in.get() == i)
    //         cout << "o caracter " << (unsigned char)i << " eh o byte: " << i << endl;
    // }

    // unsigned char byte;
    // while (in.eof())
    // {
    //     byte = in.get();
    //     cout << byte << endl;
    // }
    
    // in.close();

    Huffman noh;
    cout << sizeof(noh) << endl;

    return 0;
}

//g++ -Wall -Wextra -std=c++17 -pedantic -o gerador gerador.cpp