#ifndef ENCODE_H
#define ENCODE_H

#include "decode.h"

// Fungsi rekursif untuk mencari karakter dalam pohon Morse dan mengkodekannya
int encodeMorse(address root, char ch, char* morseCode, int depth);

// Fungsi untuk mengubah kata menjadi sandi Morse dan mengembalikannya sebagai string
char* translateToMorse(address morseTree, const char* message);
int fileExists(const char* filename);
void saveMorseResultToFile(const char* filename, const char* morseResult);
void handleFileSaving(const char* morseResult);
// Prototipe fungsi untuk input pesan
void inputMessage(char *message);

// Prototipe fungsi untuk menyimpan hasil Morse ke file
void saveMorseResult(address morseTree, const char *message);

#endif // ENCODE_H

