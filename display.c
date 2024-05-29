#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "decode.h"
int spaceTop = 10;
int spaceLeft = 20;

int top = 10 + 15;
int left = 20 + 80;

void setFullScreen() {
    // Menyiapkan struktur INPUT untuk mensimulasikan penekanan tombol
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_F11; // Tombol F11

    // Mensimulasikan penekanan tombol F11
    SendInput(1, &input, sizeof(INPUT));

    // Mensimulasikan pelepasan tombol F11
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

// koordinat untuk nentuin tulisan ditulis dimana
void moveToLine(int line, int column) {
    // Menggerakkan kursor ke baris lineNumber
    printf("\033[%d;1H", line);printf("\033[%dC", column);

}

// Untuk nyembunyiin kursor yang kedip kedip
void hideCursor() {
    printf("\033[?25l");
    fflush(stdout);
}

// Untuk nampilin kursor yang kedip kedip
void showCursor() {
    printf("\033[?25h");
    fflush(stdout);
}

// Print Header
void header(){
    char line;

    // Nama file
    char* filename = "HEADER.txt";

    // Membuka file
    FILE *file = fopen(filename, "r");

    // Memeriksa apakah file berhasil dibuka
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", filename);
        exit(1);
    }
    int i;
    int j = 0;
//	moveToLine(spaceTop, spaceLeft);
    // Membaca karakter demi karakter dari file dan mencetaknya
    while ((line = fgetc(file)) != EOF) {
    	moveToLine(spaceTop+j, spaceLeft+i);
    	if(line == '\n'){
    		j++;
    		i=0;
		}
        printf("%c", line);
		i++;
    }

    // Menutup file setelah selesai membacanya
    fclose(file);
}


void displayMenuFormToFile(int selected) {
    moveToLine(top + 8, left);
    printf("%s Input again", (selected == 0) ? "[>]" : "[ ]");
    moveToLine(top + 9, left);
    printf("%s Back to menu\n", (selected == 1) ? "[>]" : "[ ]");
}


int selectMenuWriteToFile() {
    int ch;
    int selected = 0;

    displayMenuWriteToFile(selected);
    while (1) {
        ch = getch();
        if (ch == 72) {
            selected = (selected == 0) ? 3 : --selected;
        } else if (ch == 80) {
            selected = (selected == 3) ? 0 : ++selected;
        } else if (ch == 13 || ch == 77) {
            break;
        } else if (ch == 75) {
            selected = 4;
            break;
        }
        displayMenuWriteToFile(selected);
    }
    return selected;
}

// Tampilan menu utama
void displayMenuUtama(int selectedUtama) {
	moveToLine(top, left);
    printf("=== MENU ===     ");
	moveToLine(top+1, left);
    printf("%s Morse to Character", (selectedUtama == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, left);
    printf("%s Character to Morse                      ", (selectedUtama == 1) ? "[>]" : "[ ]");
	moveToLine(top+3, left);
    printf("%s Display Tree                      ", (selectedUtama == 2) ? "[>]" : "[ ]");
    hideCursor();
}

// Tampilan menu encode
void displayMenuEncode(int selectedEncode) { // morse to char
	moveToLine(top, left);
    printf("=== ENCODE ===");
	moveToLine(top+1, left);
    printf("%s Input character                                             ", (selectedEncode == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, left);
    printf("%s Input file contain character                                             \n", (selectedEncode == 1) ? "[>]" : "[ ]");
}

// Tampilan menu decode
void displayMenuDecode(int selectedDecode) {
	moveToLine(top, left);
    printf("=== DECODE ===");
	moveToLine(top+1, left);
    printf("%s Input morse                                             ", (selectedDecode == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, left);
    printf("%s Input file contain morse                                             \n", (selectedDecode == 1) ? "[>]" : "[ ]");
}

void displayMenuWriteToFile(int selected) {
	moveToLine(top+8, left);
    printf("%s Input again                                     ", (selected == 0) ? "[>]" : "[ ]");
    
	moveToLine(top+9, left);
    printf("%s Write result into file\n", (selected == 1) ? "[>]" : "[ ]");
    
    moveToLine(top+10, left);
    printf("%s Morse Beep\n", (selected == 2) ? "[>]" : "[ ]");
    
	moveToLine(top+11, left);
    printf("%s Back to menu\n", (selected == 3) ? "[>]" : "[ ]");
}

void displayMenuAfterWriteToFile(int selected) {
	moveToLine(top+8, left);
    printf("%s Input again                                     ", (selected == 0) ? "[>]" : "[ ]");
    
    moveToLine(top+9, left);
    printf("%s Morse Beep\n", (selected == 1) ? "[>]" : "[ ]");
    
	moveToLine(top+10, left);
    printf("%s Back to menu\n", (selected == 2) ? "[>]" : "[ ]");
}

int selectMenuAfterWriteToFile(){
    int ch;
	int selected = 0;

    displayMenuAfterWriteToFile(selected);
    while (1) {
        ch = getch();
        if (ch == 72) { // atas
            selected = (selected == 0) ? 3 : --selected;
        } else if (ch == 80) { // bawah
            selected = (selected == 3) ? 0 : ++selected;
        } else if (ch == 13 || ch == 77) { // Enter
            break;
        } else if (ch == 75) { // Kiri
            selected = 4;
            break;
        }
    displayMenuAfterWriteToFile(selected);
	}
    return selected;
	
}
int selectMenuFormToFile() {
    int ch;
    int selected = 0;

    displayMenuFormToFile(selected);
    while (1) {
        ch = getch();
        if (ch == 72) { // atas
            selected = (selected == 0) ? 1 : --selected;
        } else if (ch == 80) { // bawah
            selected = (selected == 1) ? 0 : ++selected;
        } else if (ch == 13 || ch == 77) { // Enter
            break;
        }
        displayMenuFormToFile(selected);
    }
    return selected;
}
int selectedUtama = 0;
int selectMenuUtama(){
    int ch;

    while (1) {
        displayMenuUtama(selectedUtama);
        ch = getch();
        if (ch == 72) { // bawah
            selectedUtama = (selectedUtama == 0) ? 2 : --selectedUtama;
        } else if (ch == 80) { // atas
            selectedUtama = (selectedUtama == 2) ? 0 : ++selectedUtama;
        }else if (ch == 13) { // Enter
            break;
        } else if (ch == 77) { // Kanan
            break;
        }else if (ch == 75) { // Kiri
        	selectedUtama = 3;
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
        if (ch == 72) { // bawah
            selectedEncode = (selectedEncode == 0) ? 1 : 0;
        } else if (ch == 80) { // atas
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
        if (ch == 72) { // bawah
            selectedDecode = (selectedDecode == 0) ? 1 : 0;
        } else if (ch == 80) { // atas
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

void clearDisplay(int headerTop){
	int i;
	moveToLine(13, left);
	for(i = 0 ; i<=20 ; i++){
		
		moveToLine(headerTop+i, left);printf("                                                                                                              ");
	}
}

// Menunggu user menekan spasi untuk melanjutkan
void spaceToContinue(){
	printf("\033[38;2;200;100;255mPress space to continue\033[0m");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
}

void displayTree(address root, int depth, bool *path, bool isRight) {
    const int spaces = 8;
    int i,j;

    if (root == NULL)
        return;

    depth++;

    displayTree(root->right, depth, path, true);
	
    if (depth - 2 >= 0){
		path[depth - 2] = false;
	}


    if(isRight){
        path[depth - 2] = true;
	}

    if(root->left){
        path[depth - 1] = true;
	}


    printf("\n");

    for (i = 0; i < depth - 1; i++) {
        if (i == depth - 2)
            printf("%c", isRight ? 218 : 192);
        else if (path[i])
            printf("%c", 179);
        else
            printf(" ");

        for (j = 1; j < spaces; j++)
            if (i < depth - 2)
                printf(" ");
            else
                printf("%c", 196);
    }

    printf(" %c\n", root->data);

    for (i = 0; i < depth; i++) {
        if (path[i])
            printf("%c", 179);
        else
            printf(" ");

        for (j = 1; j < spaces; j++)
            printf(" ");
    }

    displayTree(root->left, depth, path, false);
}

void opening(){
	
    moveToLine(top, left);printf("\033[38;2;200;100;255mWelcome to DotDashApp");
    moveToLine(top+2, left);printf("here's a brief tutorial:");
    moveToLine(top+3, left);printf("1. use up and down arrow to select the menu options");
    moveToLine(top+4, left);printf("2. use enter or right arrow to confirm your selection");
    moveToLine(top+5, left);printf("3. use left arrow to go to previous menu");
    moveToLine(top+7, left);printf("Enjoyy!!");
}
