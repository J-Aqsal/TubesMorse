#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "fromToFile.h"
#include "display.h"

extern int top, left;
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
        moveToLine(top+2, left);
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
        	moveToLine(top+2, left);
            printf("file bukan morse\n");
            fclose(file);
            return;
        }
        
        // Debugging output
        moveToLine(top+3, left);
        printf("Membaca baris: %s", morseLine);

        // Mendekode baris kode Morse
        char* plainText = decodeMorse(morseTree, morseLine);
        moveToLine(top+5, left);
        printf("Decoded: %s\n", plainText);
        free(plainText);
    }
    
    fclose(file);
}

// Fungsi untuk membaca teks dari file dan mengencode ke Morse
void encodeFromFileMorse(address morseTree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        	moveToLine(top+2, left);
        fprintf(stderr, "FILE %s Tidak Ditemukan\n", filename);
        return;
    }
    
    char line[255];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Menghapus karakter newline jika ada
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        moveToLine(top+3, left);
        printf("Membaca baris: %s\n", line);

        // Encode baris teks ke Morse
        moveToLine(top+5, left);
        char* morseCode = translateToMorse(morseTree, line);
        printf("Encode: %s\n", morseCode);
        free(morseCode);
    }
    
    fclose(file);
}

// Fungsi untuk menambahkan ekstensi .txt jika belum ada
void appendTxtExtension(char* filename) {
    if (strlen(filename) <= 4 || strcmp(filename + strlen(filename) - 4, ".txt") != 0) {
        strcat(filename, ".txt");
    }
}
