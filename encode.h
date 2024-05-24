#ifndef ENCODE_H
#define ENCODE_H

#include "decode.h"

// Fungsi rekursif untuk mencari karakter dalam pohon Morse dan mengkodekannya
int encodeMorse(address root, char ch, char* morseCode, int depth);

// Fungsi untuk mengubah kata menjadi sandi Morse dan mengembalikannya sebagai string
char* translateToMorse(address morseTree, const char* message);

#endif // ENCODE_H

