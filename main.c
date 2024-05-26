#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "fromToFile.h"
#include "display.h"

// Fungsi untuk menambahkan ekstensi .txt jika belum ada
void appendTxtExtension(char* filename) {
    if (strlen(filename) <= 4 || strcmp(filename + strlen(filename) - 4, ".txt") != 0) {
        strcat(filename, ".txt");
    }
}

int main() {
    char cipher;
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode, selectedMenuWriteToFile;
    address morseTree = buildMorseTree();
    header();
    spaceToContinue();
    header();

    do {
        selectedMenuUtama = selectMenuUtama();
        switch (selectedMenuUtama) {
            case 0:
                do {
                    selectedMenuEncode = selectMenuEncode();
                    switch (selectedMenuEncode) {
                        case 0:
                            do {
                                moveToLine(30, 0);
                                char* inputan = readMorseInput();
                                
                                printf("\n");
                                
                                char* hasil = decodeMorse(morseTree, inputan);
                                printf("%s", hasil);
                                
                                selectedMenuWriteToFile = selectMenuWriteToFile();
                                switch (selectedMenuWriteToFile) {
                                    case 0:
                                        break;
                                    case 1:
                                        printf("\ndisini input nama file dan nulis ke file");
                                        spaceToContinue();
                                        break;
                                }
                            } while (selectedMenuWriteToFile != 2 && selectedMenuWriteToFile != 1);
                            system("cls");
                            header();
                            break;

                        case 1:
                            system("cls");
                            printf("input nama file: ");
                            char filenameDecode[255];
                            fgets(filenameDecode, sizeof(filenameDecode), stdin);
                            filenameDecode[strcspn(filenameDecode, "\n")] = 0; // Menghapus newline di akhir
                            appendTxtExtension(filenameDecode); // Tambahkan ekstensi .txt jika belum ada
                            decodeFromFileMorse(morseTree, filenameDecode);
                            spaceToContinue();
                            break;
                    }
                } while (selectedMenuEncode != 2);
                break;
            case 1:
                do {
                    selectedMenuDecode = selectMenuDecode();
                    switch (selectedMenuDecode) {
                        case 0:
                            system("cls");
                            printf("input char: ");
                            scanf(" %c", &cipher);
                            // Panggil fungsi decodeMorse() di sini jika diperlukan
                            break;
                        case 1:
                            system("cls");
                            printf("input nama file: ");
                            char filenameEncode[255];
                            fgets(filenameEncode, sizeof(filenameEncode), stdin);
                            // filenameDecode[strcspn(filenameDecode, "\n")] = 0; // Menghapus newline di akhir
                            // appendTxtExtension(filenameDecode); // Tambahkan ekstensi .txt jika belum ada
                            // decodeFromFileMorse(morseTree, filenameDecode);
                            spaceToContinue();
                            break;
                    }
                } while (selectedMenuDecode != 2);
                break;
        }
    } while (selectedMenuUtama != 2);
    return 0;
}
