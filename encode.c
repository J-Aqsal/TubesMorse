#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "encode.h"

// Fungsi rekursif untuk mencari karakter dalam pohon Morse dan mengkodekannya
int encodeMorse(address root, char ch, char* morseCode, int depth) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == ch) {
        morseCode[depth] = '\0';
        return 1;
    }
    if (encodeMorse(root->left, ch, morseCode, depth + 1)) {
        morseCode[depth] = '.';
        return 1;
    }
    if (encodeMorse(root->right, ch, morseCode, depth + 1)) {
        morseCode[depth] = '-';
        return 1;
    }
    return 0;
}

// Fungsi untuk mengubah kata menjadi sandi Morse dan mengembalikannya sebagai string
char* translateToMorse(address morseTree, const char* message) {
    char morseCode[100];
    char* result = (char*)malloc(1000 * sizeof(char)); // Alokasi memori untuk hasil Morse
    result[0] = '\0'; // Inisialisasi string kosong

    int i;
    for (i = 0; message[i] != '\0'; i++) {
        if (message[i] == ' ') {
            strcat(result, "/ ");
        } else {
            if (encodeMorse(morseTree, toupper(message[i]), morseCode, 0)) {
                strcat(result, morseCode);
                strcat(result, " ");
            } else {
                strcat(result, "? "); // jika karakter tidak ditemukan
            }
        }
    }
    return result;
}

