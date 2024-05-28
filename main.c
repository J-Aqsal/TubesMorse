#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include "encode.h"
#include "decode.h"
#include "fromToFile.h"
#include "display.h"

int main() {
    setFullScreen();
    hideCursor();
    extern int top, left;
    char* message;
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode, selectedMenuWriteToFile, selectedMenuAfterWriteToFile;
    address morseTree = buildMorseTree();
    header();

    moveToLine(top+10, left);
    spaceToContinue();
    system("cls");
    header();
    clearDisplay(top);

    do {
        selectedMenuUtama = selectMenuUtama();
        switch(selectedMenuUtama) {
            case 0:
                do {
                    clearDisplay(25);
                    selectedMenuEncode = selectMenuEncode();
                    switch(selectedMenuEncode) {
                        case 0:
                            do {
                                char* inputan = readMorseInput();
                                char* morseInput = inputan;
                                char* hasil = decodeMorse(morseTree, inputan);
                                printf("\n%s", morseInput);
                                hideCursor();
                                moveToLine(top+4, left);
                                printf("Text: %s", hasil);
    
                                do {
                                    selectedMenuWriteToFile = selectMenuWriteToFile();
                                    switch(selectedMenuWriteToFile) {
                                        case 0:
                                            break;
                                        case 1:
                                            clearDisplay(top+8);
                                            handleFileSaving(inputan);
                                            moveToLine(top+14, left);
                                            spaceToContinue();
                                            hideCursor();
                                            clearDisplay(top+8);
                                            do {
                                                selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
                                                if(selectedMenuAfterWriteToFile == 1) {
                                                    clearDisplay(top+8);
                                                    moveToLine(top+8, left);
                                                    printf("Playing...");
                                                    beepMorse(morseInput);
                                                    moveToLine(top+8, left);
                                                    spaceToContinue();
                                                }
                                            } while(selectedMenuAfterWriteToFile == 1);
                                            break;
                                        case 2:
                                            clearDisplay(top+8);
                                            moveToLine(top+8, left);
                                            printf("Playing...");
                                            beepMorse(morseInput);
                                            moveToLine(top+8, left);
                                            spaceToContinue();
                                            break;
                                    }
                                } while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile == 2);
                            } while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile != 3 );
                            clearDisplay(25);
                            break;
                            
                        case 1:
                            clearDisplay(25);
                            moveToLine(top, left);
                            printf("Input file name: ");
                            char filenameDecode[255];
                            showCursor();
                            fgets(filenameDecode, sizeof(filenameDecode), stdin);
                            hideCursor();
                            filenameDecode[strcspn(filenameDecode, "\n")] = 0;
                            appendTxtExtension(filenameDecode);
                            decodeFromFileMorse(morseTree, filenameDecode);
                            moveToLine(top+27, 0);
                            spaceToContinue();
                            system("cls");
                            header();
                            break;
                    }
                } while(selectedMenuEncode != 2);
                break;
            case 1:
                do {
                    clearDisplay(25);
                    selectedMenuDecode = selectMenuDecode();
                    switch(selectedMenuDecode) {
                        case 0:
                            do {
                                showCursor();
                                message = inputMessage();
                                hideCursor();
                                char* morseResult = translateToMorse(morseTree, message);
                                moveToLine(top+4, left);
                                printf("Morse code: %s\n", morseResult);
                                do {
                                    selectedMenuWriteToFile = selectMenuWriteToFile();
                                    switch(selectedMenuWriteToFile) {
                                        case 0:
                                            break;
                                        case 1:
                                            clearDisplay(top+8);
                                            handleFileSaving(morseResult);
                                            moveToLine(top+14, left);
                                            spaceToContinue();
                                            hideCursor();
                                            clearDisplay(top+8);
                                            do {
                                                selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
                                                if(selectedMenuAfterWriteToFile == 1) {
                                                    clearDisplay(top+8);
                                                    moveToLine(top+8, left);
                                                    printf("Playing...");
                                                    beepMorse(morseResult);
                                                    moveToLine(top+8, left);
                                                    spaceToContinue();
                                                }
                                            } while(selectedMenuAfterWriteToFile == 1);
                                            break;
                                        case 2:
                                            clearDisplay(top+8);
                                            moveToLine(top+8, left);
                                            printf("Playing...");
                                            beepMorse(morseResult);
                                            moveToLine(top+8, left);
                                            spaceToContinue();
                                            break;
                                    }
                                } while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile == 2);
                            } while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile != 3 );
                            clearDisplay(25);
                            break;
                            
                        case 1:
                            clearDisplay(25);
                            moveToLine(top, left);
                            printf("Input file name: ");
                            char filenameEncode[255];
                            showCursor();
                            fgets(filenameEncode, sizeof(filenameEncode), stdin);
                            hideCursor();
                            filenameEncode[strcspn(filenameEncode, "\n")] = 0;
                            appendTxtExtension(filenameEncode);
                            encodeFromFileMorse(morseTree, filenameEncode);
                            moveToLine(top+27, 0);
                            spaceToContinue();
                            system("cls");
                            header();
                            break;
                    }
                } while(selectedMenuDecode != 2);
                break;
            case 2:
                system("cls");
                bool *path = (bool *)calloc(10000, sizeof(bool));
                if (!path) {
                    printf("Memory allocation failed\n");
                    return 1;
                }
                displayTree(morseTree, 0, path, false);
                spaceToContinue();
                system("cls");
                header();
                break;
        }
    } while(selectedMenuUtama != 3);

    moveToLine(38, 0);
    return 0;
}
