#include <stdio.h>
#include <conio.h>
#include <windows.h> // Untuk fungsi Sleep()

void displayMenuUtama(int selected) {
    system("cls"); // Membersihkan layar
    printf("=== MENU ===\n");
    printf("%s Morse to Character\n", (selected == 0) ? "[>]" : "[ ]");
    printf("%s Character to Morse\n", (selected == 1) ? "[>]" : "[ ]");
}

void displayMenuEncode(int selected) { // morse to char
    system("cls"); // Membersihkan layar
    printf("=== ENCODE ===\n");
    printf("%s Input morse\n", (selected == 0) ? "[>]" : "[ ]");
    printf("%s Input file contain morse\n", (selected == 1) ? "[>]" : "[ ]");
}

void displayMenuDecode(int selected) {
    system("cls"); // Membersihkan layar
    printf("=== DECODE ===\n");
    printf("%s Input character\n", (selected == 0) ? "[>]" : "[ ]");
    printf("%s Input file contain character\n", (selected == 1) ? "[>]" : "[ ]");
}

int selectMenuUtama(){
    int selected = 0; // 0 untuk pilihan pertama, 1 untuk pilihan kedua
    int ch;

    while (1) {
        displayMenuUtama(selected);
        ch = getch();
        if (ch == 72) { // Enter
            selected = (selected == 0) ? 1 : 0;
        } else if (ch == 80) { // Kanan
            selected = (selected == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        } else if (ch == 77) { // Kanan
            break;
        }
        
    }
    return selected;
	
}
int selectMenuEncode(){
    int selected = 0; // 0 untuk pilihan pertama, 1 untuk pilihan kedua
    int ch;

    while (1) {
        displayMenuEncode(selected);
        ch = getch();
        if (ch == 72) { // Enter
            selected = (selected == 0) ? 1 : 0;
        } else if (ch == 80) { // Kanan
            selected = (selected == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        }else if (ch == 77) { // Kanan
            break;
        }
    }
    return selected;
	
}
int selectMenuDecode(){
    int selected = 0; // 0 untuk pilihan pertama, 1 untuk pilihan kedua
    int ch;

    while (1) {
        displayMenuDecode(selected);
        ch = getch();
        if (ch == 72) { // Enter
            selected = (selected == 0) ? 1 : 0;
        } else if (ch == 80) { // Kanan
            selected = (selected == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        }else if (ch == 77) { // Kanan
            break;
        }
    }
    return selected;
	
}
int main() {
    int selectedMenuUtama, selectedMenuEncode, selectedMenuDecode;
	selectedMenuUtama = selectMenuUtama();
	
    system("cls");
    if (selectedMenuUtama == 0) {
    	selectedMenuEncode = selectMenuEncode();
    	system("cls");
    	if(selectedMenuEncode == 0){
    		printf("encodeMorse()");
		}
		else{
			printf("inputFileMorse()");
		}
    } else {
    	selectedMenuDecode = selectMenuDecode();
    	system("cls");
    	if(selectedMenuDecode == 0){
    		printf("encodeChar()");
		}
		else{
			printf("inputFileChar()");
		}
    }

    return 0;
}

