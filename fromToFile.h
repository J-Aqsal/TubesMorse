#ifndef fromToFile_h
#define fromToFile_h

#include <stdbool.h>
#include "decode.h"

// Fungsi untuk membaca kode Morse dari file dan mendekodenya
void decodeFromFileMorse(address morseTree, const char* filename);


// Fungsi untuk memeriksa apakah sebuah string hanya berisi karakter Morse yang valid
bool isValidMorse(const char* str);

void encodeFromFileMorse(address morseTree, const char* filename);


// Fungsi untuk menambahkan ekstensi .txt jika belum ada
void appendTxtExtension(char* filename);
#endif
