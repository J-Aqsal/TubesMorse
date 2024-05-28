#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decode.h"
#include "fromToFile.h"
#include "display.h"

extern int top, left;

bool isValidMorse(const char* str) {
    while (*str) {
        if (*str != '.' && *str != '-' && *str != ' ' && *str != '/') {
            return false;
        }
        str++;
    }
    return true;
}

void decodeFromFileMorse(address morseTree, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        moveToLine(top+2, left);
        fprintf(stderr, "File %s Tidak Ditemukan\n", filename);
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
            decodeFromFileMorse(morseTree, newFilename);
        }
    } else {
        char morseLine[255];
        int lineCount = 0;
        while (fgets(morseLine, sizeof(morseLine), file) != NULL) {
            size_t len = strlen(morseLine);
            if (len > 0 && morseLine[len - 1] == '\n') {
                morseLine[len - 1] = '\0';
            }

            if (!isValidMorse(morseLine)) {
                moveToLine(top+2, left);
                printf("File bukan morse\n");
                fclose(file);
                showCursor();
                int selection = selectMenuFormToFile();
                if (selection == 1) {
                    return;
                } else if (selection == 0) {
                    clearDisplay(25);
                    moveToLine(top+2, left);
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

            moveToLine(top + 15 + lineCount, left);
            printf("Membaca baris: %s", morseLine);

            char* plainText = decodeMorse(morseTree, morseLine);
            moveToLine(top + 16 + lineCount, left);
            printf("Decoded: %s\n", plainText);
            free(plainText);
            lineCount += 2;
        }
        fclose(file);
    }
}

void encodeFromFileMorse(address morseTree, const char* filename) {
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
        char line[255];
        int lineCount = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            moveToLine(top + 15 + lineCount, left);
            printf("Membaca baris: %s\n", line);

            char* morseCode = translateToMorse(morseTree, line);
            moveToLine(top + 16 + lineCount, left);
            printf("Encode: %s\n", morseCode);
            free(morseCode);
            lineCount += 2;
        }
        fclose(file);
    }
}

void appendTxtExtension(char* filename) {
    if (strlen(filename) <= 4 || strcmp(filename + strlen(filename) - 4, ".txt") != 0) {
        strcat(filename, ".txt");
    }
}
