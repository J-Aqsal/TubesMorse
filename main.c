#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "encode.h"
#include "decode.h"
#include "fromToFile.h"
#include "display.h"

int main() {
    char cipher;
    char message[1000];
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode, selectedMenuWriteToFile, selectedMenuAfterSave;
    address morseTree = buildMorseTree();
    
    header();
    spaceToContinue();
    system("cls");
    header();

    do {
        selectedMenuUtama = selectMenuUtama();
        switch(selectedMenuUtama) {
            case 0:
                do {
                    selectedMenuEncode = selectMenuEncode();
                    switch(selectedMenuEncode) {
                        case 0:
                            system("cls");
                            header();
                            moveToLine(15, 80);
                            char* inputan = readMorseInput();
                            
                            printf("\n");
                            char* hasil = decodeMorse(morseTree, inputan);
                            printf("%s", hasil);

                            do {
                                selectedMenuWriteToFile = selectMenuWriteToFile();
                                switch(selectedMenuWriteToFile) {
                                    case 0:
                                        break;
                                    case 1:
                                        handleFileSaving(hasil);
                                        spaceToContinue();
                                        system("cls");
                                        header();
                                        break;
                                }
                            } while(selectedMenuWriteToFile != 0);
                            
                            system("cls");
                            header();
                            break;
                            
                        case 1:
                            system("cls");
                            header();
                            printf("input nama file: ");
                            scanf(" %c", &cipher); //encodeFromFileMorse();
                            break;
                    }
                } while(selectedMenuEncode != 2);
                break;
                
            case 1:
                do {
                    selectedMenuDecode = selectMenuDecode();
                    switch(selectedMenuDecode) {
                        case 0:
                            do {
                                inputMessage(message); // Panggil fungsi untuk input pesan
                                
                                char* morseResult = translateToMorse(morseTree, message);
                                moveToLine(17, 80);
                                printf("Hasil Morse: %s\n", morseResult);

                                do {
                                    selectedMenuWriteToFile = selectMenuWriteToFile();
                                    switch(selectedMenuWriteToFile) {
                                        case 0:
                                        	inputMessage(message);
                                            break;
                                        case 1:
                                        	handleFileSaving(morseResult);
	                                        break;
                                    }
                                } while (selectedMenuWriteToFile != 2);

                                free(morseResult); // Bebaskan memori yang dialokasikan
                            } while (selectedMenuWriteToFile != 2);
                            
                            system("cls");
                            header();
                            break;
                            
                        case 1:
                            system("cls");
                            header();
                            printf("input nama file: ");
                            scanf(" %c", &cipher); //decodeFromFileMorse();
                            break;
                    }
                } while(selectedMenuDecode != 2);
                break;
        }
    } while(selectedMenuUtama != 2);
    return 0;
}
