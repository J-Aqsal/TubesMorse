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
	char* inputanFile;
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode, selectedMenuWriteToFile, selectedMenuAfterWriteToFile;
    address morseTree = buildMorseTree();
    header();
    
    opening();
    
	moveToLine(top+10, left);
    spaceToContinue();
    system("cls");
	header();
	clearDisplay(top);
    do{
    	clearDisplay(25);
    	selectedMenuUtama = selectMenuUtama();
    	switch(selectedMenuUtama){
	    	clearDisplay(13);
    		case 0:
    			do{
    				clearDisplay(25);
	    			selectedMenuDecode = selectMenuDecode();
	    			switch(selectedMenuDecode){
	    				case 0:
	    					do{
							    char* inputan = readMorseInput();
	    						char* morseInput = malloc(strlen(inputan) + 1);
							    if (morseInput == NULL) {
							        perror("malloc failed");
							        free(inputan);
							        exit(EXIT_FAILURE);
							    }
							    strcpy(morseInput, inputan);
							    
								char* hasil = decodeMorse(morseTree, inputan);
							    
								hideCursor();
								
								moveToLine(top+4, left);
							    
								printf("Text: %s", hasil);							    
    
							    do{
									selectedMenuWriteToFile = selectMenuWriteToFile();
							    
	                                switch(selectedMenuWriteToFile) {
	                                	hideCursor();
	                                    case 0:
	                                        break;
	                                    case 1:
											clearDisplay(top+8);
	                                        handleFileSaving(hasil);
											moveToLine(top+14, left);
	                                        spaceToContinue();
	                                        hideCursor();
											clearDisplay(top+8);
											do{
	                                        	selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
												if(selectedMenuAfterWriteToFile == 1){
													
													clearDisplay(top+8);
													moveToLine(top+8, left);
													printf("Playing...");
			                                    	
			                                    	beepMorse(morseInput);
													moveToLine(top+8, left);
													spaceToContinue();
												}
											}while(selectedMenuAfterWriteToFile == 1);
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
								}while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile == 2);
                                
							}while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile != 3 );
							clearDisplay(23);
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
							moveToLine(top+27, 0);
							hideCursor();
						    spaceToContinue();
	    					system("cls");
	    					header();
                            break;
					}	
//	    			break;
				}while(selectedMenuDecode != 2);
				break;
			case 1:
                do {
    				clearDisplay(25);
                    selectedMenuEncode = selectMenuEncode();
                    switch(selectedMenuEncode) {
                        case 0:
                            do {
    							showCursor();
    							message = inputMessage();
                                
                                hideCursor();
                                
                                char* morseResult = translateToMorse(morseTree, message);
                                
								moveToLine(top+4, left);
								
                                printf("Morse code: %s\n", morseResult);
								
								do{
									selectedMenuWriteToFile = selectMenuWriteToFile();
							    
	                                switch(selectedMenuWriteToFile) {
	                                	hideCursor();
	                                    case 0:
	                                        break;
	                                    case 1:
											clearDisplay(top+8);
	                                        handleFileSaving(morseResult);
											moveToLine(top+14, left);
	                                        spaceToContinue();
	                                        hideCursor();
											clearDisplay(top+8);
											do{
	                                        	selectedMenuAfterWriteToFile = selectMenuAfterWriteToFile();
												if(selectedMenuAfterWriteToFile == 1){
													
													clearDisplay(top+8);
													moveToLine(top+8, left);
													printf("Playing...");
			                                    	
			                                    	beepMorse(morseResult);
													moveToLine(top+8, left);
													spaceToContinue();
												}
											}while(selectedMenuAfterWriteToFile == 1);
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
								}while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile == 2);
                                
							}while(selectedMenuAfterWriteToFile != 2 && selectedMenuWriteToFile != 3 );
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
							moveToLine(top+27, 0);
							hideCursor();
						    spaceToContinue();
	    					system("cls");
	    					header();
                            break;
                    }
                } while(selectedMenuEncode != 2);
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
			case 3:{
				clearDisplay(25);
				moveToLine(top,left);
				inorderTraversal(morseTree);
				moveToLine(top+8, left);
				spaceToContinue();
			
				break;
			}
        }
    } while(selectedMenuUtama != 4);
	
	moveToLine(38, 0);
//	printf("ty");
    return 0;
}

