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
void decodeFromFileMorse(address morseTree, char* filenames) {
    int selectedMenuWriteToFile, selectedMenuAfterWriteToFile;
    char filename[100] = "files_input/";
    strcat(filename, filenames);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        moveToLine(top + 2, left);
        fprintf(stderr, "File %s Tidak Ditemukan\n", filename);
        showCursor();
        int selection = selectMenuFormToFile();
        if (selection == 1) {
            return;
        } else if (selection == 0) {
            clearDisplay(25);
            moveToLine(top + 2, left);
            printf("Input file name: ");
            char newFilename[255];
            showCursor();
            fgets(newFilename, sizeof(newFilename), stdin);
            hideCursor();
            newFilename[strcspn(newFilename, "\n")] = 0;
            appendTxtExtension(newFilename);
            decodeFromFileMorse(morseTree, newFilename);
        }
    } else {
        char morseLine[1024];
        int lineCount = 0;
        while (fgets(morseLine, sizeof(morseLine), file) != NULL) {
            size_t len = strlen(morseLine);
            if (len > 0 && morseLine[len - 1] == '\n') {
                morseLine[len - 1] = '\0';
            }

            if (!isValidMorse(morseLine)) {
                moveToLine(top + 2, left);
                printf("File bukan morse\n");
                fclose(file);
                showCursor();
                int selection = selectMenuFormToFile();
                if (selection == 1) {
                    return;
                } else if (selection == 0) {
                    clearDisplay(25);
                    moveToLine(top + 2, left);
                    printf("Input file name: ");
                    char newFilename[255];
                    showCursor();
                    fgets(newFilename, sizeof(newFilename), stdin);
                    hideCursor();
                    newFilename[strcspn(newFilename, "\n")] = 0;
                    appendTxtExtension(newFilename);
                    decodeFromFileMorse(morseTree, newFilename);
                }
                break;
            }

            moveToLine(top + 15 + lineCount, -1);
            printf("File Name: %s\n\n", filenames);
            
            printf("Line: %s", morseLine);

	    	char* morseInputFile = malloc(strlen(morseLine) + 1);
	    	strcpy(morseInputFile, morseLine);
            char* plainText = decodeMorse(morseTree, morseLine);
//            moveToLine(top + 20 + lineCount, 0);
            printf("\n\nDecoded: %s\n", plainText);
            do {
                selectedMenuWriteToFile = selectMenuWriteToFile();

                switch (selectedMenuWriteToFile) {
                    hideCursor();
                    case 0:
                    	system("cls");
                    	header();
	                    moveToLine(top + 2, left);
	                    printf("Input file name: ");
	                    char newFilename[255];
	                    showCursor();
	                    fgets(newFilename, sizeof(newFilename), stdin);
	                    hideCursor();
	                    newFilename[strcspn(newFilename, "\n")] = 0;
	                    appendTxtExtension(newFilename);
	                    decodeFromFileMorse(morseTree, newFilename);
                        break;
                    case 1:
                        clearDisplay(top + 8);
                        handleFileSaving(plainText);
                        moveToLine(top + 14, left);
                        spaceToContinue();
                        hideCursor();
                        clearDisplay(top + 8);
                        do {
                            selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
                            if (selectedMenuAfterWriteToFile == 1) {
                                clearDisplay(top + 8);
                                moveToLine(top + 8, left);
                                printf("Playing...");
                                beepMorse(morseInputFile);  // Memperbaiki tanda kurung
                                moveToLine(top + 8, left);
                                spaceToContinue();
                            }
                        } while (selectedMenuAfterWriteToFile == 1);
                        break;
                    case 2:
                        clearDisplay(top + 8);
                        moveToLine(top + 8, left);
                        printf("Playing...");
                        beepMorse(morseInputFile);  // Memperbaiki tanda kurung
                        moveToLine(top + 8, left);
                        spaceToContinue();
                        break;
                }
            } while (selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile != 3);
            lineCount += 2;
        }
        fclose(file);
    }
}

// Fungsi untuk membaca teks dari file dan mengencode ke Morse
void encodeFromFileMorse(address morseTree, char* filenames) {
    int selectedMenuWriteToFile, selectedMenuAfterWriteToFile;
	char filename[100] = "files_input/";
	strcat(filename, filenames);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        moveToLine(top+2, left);
        fprintf(stderr, "FILE %s Tidak Ditemukan\n", filename);
        showCursor();
        int selection = selectMenuFormToFile();
        if (selection == 1) {
            return;
        }
        else if (selection == 0) {
            clearDisplay(25);
            moveToLine(top+2, left);
            printf("Input file name: ");
            char newFilename[255];
            showCursor();
            fgets(newFilename, sizeof(newFilename), stdin);
            hideCursor();
            newFilename[strcspn(newFilename, "\n")] = 0;
            appendTxtExtension(newFilename);
            encodeFromFileMorse(morseTree, newFilename);
        }
    } else {
        char line[1024];
        int lineCount = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            moveToLine(top + 15 + lineCount, -1);
            printf("File Name: %s\n\n", filenames);
            printf("Line: %s\n\n", line);

            
            char* morseCode = translateToMorse(morseTree, line);
            printf("Encode: %s\n", morseCode);
            do {
                selectedMenuWriteToFile = selectMenuWriteToFile();

                switch (selectedMenuWriteToFile) {
                    hideCursor();
                    case 0:
                    	system("cls");
                    	header();
	                    moveToLine(top + 2, left);
	                    printf("Input file name: ");
	                    char newFilename[255];
	                    showCursor();
	                    fgets(newFilename, sizeof(newFilename), stdin);
	                    hideCursor();
	                    newFilename[strcspn(newFilename, "\n")] = 0;
	                    appendTxtExtension(newFilename);
	                    decodeFromFileMorse(morseTree, newFilename);
                        break;
                    case 1:
                        clearDisplay(top + 8);
                        handleFileSaving(morseCode);
                        moveToLine(top + 14, left);
                        spaceToContinue();
                        hideCursor();
                        clearDisplay(top + 8);
                        do {
                            selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
                            if (selectedMenuAfterWriteToFile == 1) {
                                clearDisplay(top + 8);
                                moveToLine(top + 8, left);
                                printf("Playing...");
                                beepMorse(morseCode);  // Memperbaiki tanda kurung
                                moveToLine(top + 8, left);
                                spaceToContinue();
                            }
                        } while (selectedMenuAfterWriteToFile == 1);
                        break;
                    case 2:
                        clearDisplay(top + 8);
                        moveToLine(top + 8, left);
                        printf("Playing...");
                        beepMorse(morseCode);  // Memperbaiki tanda kurung
                        moveToLine(top + 8, left);
                        spaceToContinue();
                        break;
                }
            } while (selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile != 3);
            lineCount += 2;
        }
        fclose(file);
    }
}

// Fungsi untuk menambahkan ekstensi .txt jika belum ada
void appendTxtExtension(char* filename) {
    if (strlen(filename) <= 4 || strcmp(filename + strlen(filename) - 4, ".txt") != 0) {
        strcat(filename, ".txt");
    }
}
