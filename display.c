#include <stdio.h>
int selectedUtama;
// Tampilan menu utama
void displayMenuUtama(int selectedUtama) {
    system("cls");
    printf("=== MENU ===\n");
    printf("%s Morse to Character\n", (selectedUtama == 0) ? "[>]" : "[ ]");
    printf("%s Character to Morse\n", (selectedUtama == 1) ? "[>]" : "[ ]");
}

// Tampilan menu encode
void displayMenuEncode(int selectedEncode) { // morse to char
    system("cls");
    printf("=== ENCODE ===\n");
    
    printf("%s Input morse\n", (selectedEncode == 0) ? "[>]" : "[ ]");
    printf("%s Input file contain morse\n", (selectedEncode == 1) ? "[>]" : "[ ]");
}

// Tampilan menu decode
void displayMenuDecode(int selectedDecode) {
    system("cls");
    printf("=== DECODE ===\n");
    printf("%s Input character\n", (selectedDecode == 0) ? "[>]" : "[ ]");
    printf("%s Input file contain character\n", (selectedDecode == 1) ? "[>]" : "[ ]");
}

int selectMenuUtama(){
    int ch;

    while (1) {
        displayMenuUtama(selectedUtama);
        ch = getch();
        if (ch == 72) { // Enter
            selectedUtama = (selectedUtama == 0) ? 1 : 0;
        } else if (ch == 80) { // Kanan
            selectedUtama = (selectedUtama == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        } else if (ch == 77) { // Kanan
            break;
        }else if (ch == 75) { // Kiri
        	selectedUtama = 2;
            break;
        }
        
    }
    return selectedUtama;
	
}

int selectMenuEncode(){
    int ch;
int selectedEncode = 0;

    while (1) {
        displayMenuEncode(selectedEncode);
        ch = getch();
        if (ch == 72) { // Enter
            selectedEncode = (selectedEncode == 0) ? 1 : 0;
        } else if (ch == 80) { // Kanan
            selectedEncode = (selectedEncode == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        }else if (ch == 77) { // Kanan
            break;
        }else if (ch == 75) { // Kiri
        	selectedEncode = 2;
            break;
        }
    }
    return selectedEncode;
	
}
int selectMenuDecode(){
    int ch;
int selectedDecode = 0;

    while (1) {
        displayMenuDecode(selectedDecode);
        ch = getch();
        if (ch == 72) { // Enter
            selectedDecode = (selectedDecode == 0) ? 1 : 0;
        } else if (ch == 80) { // Kanan
            selectedDecode = (selectedDecode == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        }else if (ch == 77) { // Kanan
            break;
        }else if (ch == 75) { // Kiri
        	selectedDecode = 2;
            break;
        }
    }
    return selectedDecode;
	
}

// Menunggu user menekan spasi untuk melanjutkan
void spaceToContinue(){
	printf("\n\nTekan spasi untuk melanjutkan");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
    system("cls");
}
