#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "fromToFile.h"

// Fungsi untuk memeriksa apakah sebuah string hanya berisi karakter Morse yang valid
bool isValidMorse(const char* str) {
    while (*str) {
        if (*str != '.' && *str != '-' && *str != ' ' && *str != '/') {
            return false;
        }
        str++;
    }
    return true;
}

// Fungsi untuk membaca kode Morse dari file dan mendekodenya
void decodeFromFileMorse(address morseTree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File %s Tidak Ditemukan\n", filename);
        return;
    }
    
    char morseLine[255];
    while (fgets(morseLine, sizeof(morseLine), file) != NULL) {
        // Menghapus karakter newline jika ada
        size_t len = strlen(morseLine);
        if (len > 0 && morseLine[len - 1] == '\n') {
            morseLine[len - 1] = '\0';
        }
        
        // Periksa apakah baris hanya berisi karakter Morse yang valid
        if (!isValidMorse(morseLine)) {
            printf("file bukan morse\n");
            fclose(file);
            return;
        }
        
         // Debugging output
        printf("Membaca baris: %s\n", morseLine);

        // Mendekode baris kode Morse
        char* plainText = decodeMorse(morseTree, morseLine);
        printf("Decoded: %s\n", plainText);
        free(plainText);
    }
    
    fclose(file);
}
