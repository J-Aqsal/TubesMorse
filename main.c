#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "encode.h"
#include "decode.h"
#include "fromToFile.h"
#include "display.h"



int main() {
	char cipher;
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode;
    address morseTree = buildMorseTree();
    
    do{
    	system("cls");
    	selectedMenuUtama = selectMenuUtama();
    	switch(selectedMenuUtama){
	    	system("cls");
    		case 0:
    			do{
	    			selectedMenuEncode = selectMenuEncode();
	    			switch(selectedMenuEncode){
	    				case 0:
	    					system("cls");
							printf("Masukkan pesan Morse (gunakan z untuk titik dan x untuk strip, spasi antara karakter, garis miring untuk kata baru):\n");
    
						    char* inputan = readMorseInput();
						    printf("\n");
						
						    
							char* hasil = decodeMorse(morseTree, inputan);
						    printf("%s", hasil);
						    
						    spaceToContinue();
							break;
	    				case 1:
	    					system("cls");
	    					printf("input nama file: ");scanf(" %c", &cipher); //encodeFromFileMorse();
	    					break;
					}	
	    			break;
				}while(selectedMenuEncode != 2);
				break;
			case 1:
				do{
					selectedMenuDecode = selectMenuDecode();
    				switch(selectedMenuDecode){
	    				case 0:
                            system("cls");
                            printf("Masukkan pesan yang ingin diterjemahkan ke sandi Morse:\n");
                            char message[100];
                            fgets(message, sizeof(message), stdin);
                            message[strcspn(message, "\n")] = 0; // Hapus newline

                            char* morseResult = translateToMorse(morseTree, message);
                            printf("Hasil Morse: %s\n", morseResult);

                            free(morseResult); // Membebaskan memori yang dialokasikan

                            spaceToContinue();
	    					break;
	    				case 1:
	    					system("cls");
	    					printf("input nama file: ");scanf(" %c", &cipher); //decodeFromFileMorse();
	    					break;
					}
	    			break;
				}while(selectedMenuDecode != 2);
				break;
		}
	}while(selectedMenuUtama != 2);
    return 0;
}

