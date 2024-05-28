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
    extern top, left;
	char cipher;
	char* message;
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode, selectedMenuWriteToFile, selectedMenuAfterWriteToFile;
    address morseTree = buildMorseTree();
    header();
    
	moveToLine(top+10, left);
    spaceToContinue();
    system("cls");
	header();
	clearDisplay(top);
    do{
    	selectedMenuUtama = selectMenuUtama();
    	switch(selectedMenuUtama){
	    	clearDisplay(13);
    		case 0:
    			do{
    				clearDisplay(25);
	    			selectedMenuEncode = selectMenuEncode();
	    			switch(selectedMenuEncode){
	    				case 0:
	    					do{
							    char* inputan = readMorseInput();
							    
								char* hasil = decodeMorse(morseTree, inputan);
								
								hideCursor();
								
								moveToLine(top+4, left);
							    
								printf("Text: %s", hasil);
							    
    
							    selectedMenuWriteToFile = selectMenuWriteToFile();
							    
                                switch(selectedMenuWriteToFile) {
                                    case 0:
                                        break;
                                    case 1:
										clearDisplay(top+8);
                                        handleFileSaving(hasil);
										moveToLine(top+15, left);
                                        spaceToContinue();
                                        hideCursor();
										clearDisplay(top+8);
                                        selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
                                        break;
                                    case 2:
                                    	beepMorse(inputan);
                                    	break;
                                        
                                }
							}while(selectedMenuAfterWriteToFile != 1 && selectedMenuWriteToFile != 3 );
							clearDisplay(25);
							break;
							
	    				case 1:
	    					clearDisplay(25);
	    					moveToLine(top,left);
                            printf("Input file name: ");
                            char filenameDecode[255];
	    					showCursor();
                            fgets(filenameDecode, sizeof(filenameDecode), stdin);
                            hideCursor();
                            filenameDecode[strcspn(filenameDecode, "\n")] = 0; // Menghapus newline di akhir
                            appendTxtExtension(filenameDecode); // Tambahkan ekstensi .txt jika belum ada
                            decodeFromFileMorse(morseTree, filenameDecode);
							moveToLine(top+10, left);
						    spaceToContinue();
	    					clearDisplay(25);
                            break;
					}	
//	    			break;
				}while(selectedMenuEncode != 2);
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
    							
//                                inputMessage(message); // Panggil fungsi untuk input pesan
                                
                                hideCursor();
                                
                                char* morseResult = translateToMorse(morseTree, message);
                                
								moveToLine(top+4, left);
								
                                printf("Morse code: %s\n", morseResult);

                                selectedMenuWriteToFile = selectMenuWriteToFile();
							    
                                switch(selectedMenuWriteToFile) {
                                    case 0:
                                        break;
                                    case 1:
										clearDisplay(top+8);
                                        handleFileSaving(morseResult);
										moveToLine(top+10, left);
                                        spaceToContinue();
                                        hideCursor();
										clearDisplay(top+8);
                                        selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
                                        break;
                                    case 2:
                                    	beepMorse(morseResult);
                                    	break;
                                        
                                }
							}while(selectedMenuAfterWriteToFile != 1 && selectedMenuWriteToFile != 3 );
							clearDisplay(25);
							break;
                            
                        case 1:
	    					clearDisplay(25);
	    					moveToLine(top,left);
                            printf("Input file name: ");
                            char filenameEncode[255];
	    					showCursor();
                            fgets(filenameEncode, sizeof(filenameEncode), stdin);
                            hideCursor();
                            filenameEncode[strcspn(filenameEncode, "\n")] = 0; // Menghapus newline di akhir
                            appendTxtExtension(filenameEncode); // Tambahkan ekstensi .txt jika belum ada
                            encodeFromFileMorse(morseTree, filenameEncode);
							moveToLine(top+10, left);
						    spaceToContinue();
	    					clearDisplay(25);
                            break;
                    }
                } while(selectedMenuDecode != 2);
                break;
            case 2:{
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
        }
    } while(selectedMenuUtama != 3);
	
	moveToLine(38, 0);
//	printf("ty");
    return 0;
}

