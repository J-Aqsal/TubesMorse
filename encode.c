#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
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
    showCursor();
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

// Fungsi untuk meminta input pesan dari pengguna
void inputMessage(char *message) {
    system("cls");
    header();
    moveToLine(15, 80);
    printf("Masukkan pesan yang ingin diterjemahkan ke sandi Morse:\n");
    moveToLine(16, 80);
    fgets(message, 100, stdin);
    message[strcspn(message, "\n")] = 0; // Hapus newline
}

// Fungsi untuk memeriksa apakah file sudah ada di folder
int fileExists(const char* filename) {
    FILE* file;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return 1; // file ditemukan
    }
    return 0; // file tidak ditemukan
}

// Fungsi untuk menyimpan hasil Morse ke dalam file
void saveMorseResultToFile(const char* filename, const char* morseResult) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "%s", morseResult);
    fclose(file);

    printf("Hasil Morse telah disimpan dalam file %s\n", filename);
}

// Fungsi untuk membuat folder jika belum ada
void createDirectoryIfNotExists(const char* dirName) {
    struct stat st = {0};
    if (stat(dirName, &st) == -1) {
        mkdir(dirName);
    }
}

// Fungsi untuk menangani penyimpanan file
void handleFileSaving(const char* morseResult) {
    char filename[100];
    char newFilename[100];
    char filePath[150];
    char newFilePath[150];
    char choice;

    const char* folderName = "files_input";
    createDirectoryIfNotExists(folderName);

    // Cek apakah hasil Morse mengandung karakter '?'
    if (strstr(morseResult, "?") != NULL) {
        printf("Hasil Morse mengandung karakter yang tidak dikenali. Tidak bisa menyimpan file.\n");
        return;
    }

    printf("Masukkan nama file untuk menyimpan hasil Morse: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // Menghapus karakter newline

    // Tambahkan ekstensi .txt jika tidak ada
    if (strstr(filename, ".txt") == NULL) {
        strcat(filename, ".txt");
    }

    snprintf(filePath, sizeof(filePath), "%s/%s", folderName, filename);

    // Jika file sudah ada, tanyakan apakah ingin menyimpan ke file yang sama atau file baru
    if (fileExists(filePath)) {
        printf("File dengan nama '%s' sudah ada di dalam folder.\n", filePath);
        printf("Apakah Anda ingin menyimpan ke file yang sama? (y) atau file baru? (n): ");
        scanf(" %c", &choice);
        getchar(); // Membersihkan karakter newline setelah scanf

        if (choice == 'n' || choice == 'N') {
            do {
                printf("Masukkan nama file baru: ");
                fgets(newFilename, sizeof(newFilename), stdin);
                newFilename[strcspn(newFilename, "\n")] = 0; // Menghapus karakter newline

                // Tambahkan ekstensi .txt jika tidak ada
                if (strstr(newFilename, ".txt") == NULL) {
                    strcat(newFilename, ".txt");
                }

                snprintf(newFilePath, sizeof(newFilePath), "%s/%s", folderName, newFilename);

                // Cek apakah nama file baru sama dengan nama file lama
                if (strcmp(newFilePath, filePath) == 0) {
                    printf("Nama file baru tidak boleh sama dengan nama file sebelumnya. Silakan masukkan nama file yang berbeda.\n");
                }
            } while (strcmp(newFilePath, filePath) == 0);

            strcpy(filePath, newFilePath); // Salin path file baru ke variabel filePath
        } else {
            // Jika pengguna memilih untuk menyimpan ke file yang sama, buka dalam mode append
            FILE* file = fopen(filePath, "a");
            if (file == NULL) {
                printf("Gagal membuka file.\n");
                return;
            }

            // Tambahkan satu baris kosong sebelum menulis hasil Morse baru
            fprintf(file, "\n%s", morseResult);
            fclose(file);

            printf("Hasil Morse telah disimpan dalam file %s\n", filePath);
            return;
        }
    }

    // Jika file tidak ada atau pengguna memilih file baru
    saveMorseResultToFile(filePath, morseResult);
}

