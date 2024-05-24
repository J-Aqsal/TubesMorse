#include <stdio.h>
#include <windows.h>
int top = 20;
int right = 80;


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

    // Membaca karakter demi karakter dari file dan mencetaknya
    while ((line = fgetc(file)) != EOF) {
        printf("%c", line);
    }

    // Menutup file setelah selesai membacanya
    fclose(file);
}

// Tampilan menu utama
void displayMenuUtama(int selectedUtama) {
	moveToLine(top, right);
    printf("=== MENU ===");
	moveToLine(top+1, right);
    printf("%s Morse to Character", (selectedUtama == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, right);
    printf("%s Character to Morse\n", (selectedUtama == 1) ? "[>]" : "[ ]");
    hideCursor();
}

// Tampilan menu encode
void displayMenuEncode(int selectedEncode) { // morse to char
	moveToLine(top, right);
    printf("=== ENCODE ===");
	moveToLine(top+1, right);
    printf("%s Input morse                                             ", (selectedEncode == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, right);
    printf("%s Input file contain morse                                             \n", (selectedEncode == 1) ? "[>]" : "[ ]");
}

// Tampilan menu decode
void displayMenuDecode(int selectedDecode) {
	moveToLine(top, right);
    printf("=== DECODE ===");
	moveToLine(top+1, right);
    printf("%s Input character                                             ", (selectedDecode == 0) ? "[>]" : "[ ]");
	moveToLine(top+2, right);
    printf("%s Input file contain character                                             \n", (selectedDecode == 1) ? "[>]" : "[ ]");
}

void displayMenuWriteToFile(int selected) {
	moveToLine(35, 0);

    // Menampilkan menu dengan pilihan yang disorot
    printf("\n%s Input Morse Again\n", (selected == 0) ? "[>]" : "[ ]");
    printf("%s Write result into file\n", (selected == 1) ? "[>]" : "[ ]");
    printf("%s Back to menu\n", (selected == 2) ? "[>]" : "[ ]");
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

    while (1) {// Mendapatkan handle dari jendela CMD
    HWND hwnd = GetConsoleWindow();
    
    // Menyetel jendela CMD agar tetap di atas
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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

// Menunggu user menekan spasi untuk melanjutkan
void spaceToContinue(){
	printf("\n\nTekan spasi untuk melanjutkan");
    while(getch() != ' '); // menunggu user menekan spasi untuk melanjutkan
    system("cls");
}

