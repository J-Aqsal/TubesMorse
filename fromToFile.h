#ifndef fromToFile_h
#define fromToFile_h

#include "decode.h"
#include <stdbool.h>

// Fungsi untuk membaca kode Morse dari file dan mendekodenya
void decodeFromFileMorse(address morseTree, const char* filename);

// Fungsi untuk memeriksa apakah sebuah string hanya berisi karakter Morse yang valid
bool isValidMorse(const char* str);

void encodeFromFileMorse(address morseTree, const char* filename);

#endif
