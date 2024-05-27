#include <stdio.h>
#include <windows.h>

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

// Tampilan menu utama
void displayMenuUtama(int selectedUtama) {
	moveToLine(top, left);
    printf("=== MENU ===     ");
	moveToLine(top+1, left);
    printf("%s Morse to Character", (selectedUtama == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, left);
    printf("%s Character to Morse                      ", (selectedUtama == 1) ? "[>]" : "[ ]");
    hideCursor();
}

// Tampilan menu encode
void displayMenuEncode(int selectedEncode) { // morse to char
	moveToLine(top, left);
    printf("=== DECODE ===");
	moveToLine(top+1, left);
    printf("%s Input morse                                             ", (selectedEncode == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, left);
    printf("%s Input file contain morse                                             \n", (selectedEncode == 1) ? "[>]" : "[ ]");
}

// Tampilan menu decode
void displayMenuDecode(int selectedDecode) {
	moveToLine(top, left);
    printf("=== ENCODE ===");
	moveToLine(top+1, left);
    printf("%s Input character                                             ", (selectedDecode == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, left);
    printf("%s Input file contain character                                             \n", (selectedDecode == 1) ? "[>]" : "[ ]");
}

void displayMenuWriteToFile(int selected) {
	moveToLine(top+8, left);
    printf("%s Input again", (selected == 0) ? "[>]" : "[ ]");
    
	moveToLine(top+9, left);
    printf("%s Write result into file\n", (selected == 1) ? "[>]" : "[ ]");
    
	moveToLine(top+10, left);
    printf("%s Back to menu\n", (selected == 2) ? "[>]" : "[ ]");
}

void displayMenuAfterWriteToFile(int selected) {
	moveToLine(top+8, left);
    printf("%s Input again", (selected == 0) ? "[>]" : "[ ]");
    
    
	moveToLine(top+9, left);
    printf("%s Back to menu\n", (selected == 1) ? "[>]" : "[ ]");
}

int selectMenuAfterWriteToFile(){
    int ch;
	int selected = 0;

    while (1) {
        displayMenuAfterWriteToFile(selected);
        ch = getch();
        if (ch == 72) { // bawah
            selected = (selected == 0) ? 1 : 0;
        } else if (ch == 80) { // atas
            selected= (selected == 1) ? 0 : 1;
        }else if (ch == 13) { // Enter
            break;
        }else if (ch == 77) { // Kanan
            break;
        }else if (ch == 75) { // Kiri
        	selected = 2;
            break;
        }
    }
    return selected;
	
}

int selectMenuWriteToFile() {
    int ch;
    int selected = 0;

    // Tampilkan pertama kali
    displayMenuWriteToFile(selected);

    while (1) {
        ch = getch();
        if (ch == 72) { // atas
            selected = (selected == 0) ? 2 : --selected;
        } else if (ch == 80) { // bawah
            selected = (selected == 2) ? 0 : ++selected;
        } else if (ch == 13 || ch == 77) { // Enter
            break;
        } else if (ch == 75) { // Kiri
            selected = 3;
            break;
        }
        // Perbarui tampilan menu dengan pilihan yang diperbarui
        displayMenuWriteToFile(selected);
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
            selectedUtama = (selectedUtama == 0) ? 1 : 0;
        } else if (ch == 80) { // atas
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
	printf("Tekan spasi untuk melanjutkan");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
//    clearDisplay(13);
}

