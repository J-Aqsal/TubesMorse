#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "fromToFile.h"

// Fungsi untuk membaca kode Morse dari file dan mendekodenya
void decodeFromFileMorse(address morseTree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Gagal membuka file %s\n", filename);
        return;
    }

    printf("Berhasil membuka file: %s\n", filename); // Debugging output

    char morseLine[255];
    while (fgets(morseLine, sizeof(morseLine), file) != NULL) {
        // Menghapus karakter newline jika ada
        size_t len = strlen(morseLine);
        if (len > 0 && morseLine[len - 1] == '\n') {
            morseLine[len - 1] = '\0';
        }

        // Debugging output
        printf("Membaca baris: %s\n", morseLine);

        // Mendekode baris kode Morse
        char* plainText = decodeMorse(morseTree, morseLine);
        printf("Decoded: %s\n", plainText);
        free(plainText);
    }

    fclose(file);
    printf("Selesai mendekode file.\n"); // Debugging output
}
