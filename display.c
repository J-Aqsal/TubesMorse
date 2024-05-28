#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "decode.h"

int spaceTop = 10;
int spaceLeft = 20;

int top = 10 + 15;
int left = 20 + 80;

void setFullScreen() {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_F11; // Tombol F11

    SendInput(1, &input, sizeof(INPUT));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void moveToLine(int line, int column) {
    printf("\033[%d;1H", line);
    printf("\033[%dC", column);
}

void hideCursor() {
    printf("\033[?25l");
    fflush(stdout);
}

void showCursor() {
    printf("\033[?25h");
    fflush(stdout);
}

void header() {
    char line;
    char* filename = "HEADER.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Gagal membuka file %s.\n", filename);
        exit(1);
    }
    int i;
    int j = 0;
    while ((line = fgetc(file)) != EOF) {
        moveToLine(spaceTop + j, spaceLeft + i);
        if (line == '\n') {
            j++;
            i = 0;
        }
        printf("%c", line);
        i++;
    }
    fclose(file);
}

void displayMenuUtama(int selectedUtama) {
    moveToLine(top, left);
    printf("=== MENU ===     ");
    moveToLine(top + 1, left);
    printf("%s Morse to Character", (selectedUtama == 0) ? "[>]" : "[ ]");
    moveToLine(top + 2, left);
    printf("%s Character to Morse                      ", (selectedUtama == 1) ? "[>]" : "[ ]");
    moveToLine(top + 3, left);
    printf("%s Display Tree                      ", (selectedUtama == 2) ? "[>]" : "[ ]");
    hideCursor();
}

void displayMenuEncode(int selectedEncode) {
    moveToLine(top, left);
    printf("=== DECODE ===");
    moveToLine(top + 1, left);
    printf("%s Input morse                                             ", (selectedEncode == 0) ? "[>]" : "[ ]");
    moveToLine(top + 2, left);
    printf("%s Input file contain morse                                             \n", (selectedEncode == 1) ? "[>]" : "[ ]");
}

void displayMenuDecode(int selectedDecode) {
    moveToLine(top, left);
    printf("=== ENCODE ===");
    moveToLine(top + 1, left);
    printf("%s Input character                                             ", (selectedDecode == 0) ? "[>]" : "[ ]");
    moveToLine(top + 2, left);
    printf("%s Input file contain character                                             \n", (selectedDecode == 1) ? "[>]" : "[ ]");
}

void displayMenuWriteToFile(int selected) {
    moveToLine(top + 8, left);
    printf("%s Input again", (selected == 0) ? "[>]" : "[ ]");
    moveToLine(top + 9, left);
    printf("%s Write result into file\n", (selected == 1) ? "[>]" : "[ ]");
    moveToLine(top + 10, left);
    printf("%s Morse Beep\n", (selected == 2) ? "[>]" : "[ ]");
    moveToLine(top + 11, left);
    printf("%s Back to menu\n", (selected == 3) ? "[>]" : "[ ]");
}

void displayMenuAfterWriteToFile(int selected) {
    moveToLine(top + 8, left);
    printf("%s Input again                                     ", (selected == 0) ? "[>]" : "[ ]");
    moveToLine(top + 9, left);
    printf("%s Morse Beep\n", (selected == 1) ? "[>]" : "[ ]");
    moveToLine(top + 10, left);
    printf("%s Back to menu\n", (selected == 2) ? "[>]" : "[ ]");
}

void displayMenuFormToFile(int selected) {
    moveToLine(top + 8, left);
    printf("%s Input again", (selected == 0) ? "[>]" : "[ ]");
    moveToLine(top + 9, left);
    printf("%s Back to menu\n", (selected == 1) ? "[>]" : "[ ]");
}

int selectMenuAfterWriteToFile() {
    int ch;
    int selected = 0;

    displayMenuAfterWriteToFile(selected);
    while (1) {
        ch = getch();
        if (ch == 72) {
            selected = (selected == 0) ? 2 : --selected;
        } else if (ch == 80) {
            selected = (selected == 2) ? 0 : ++selected;
        } else if (ch == 13 || ch == 77) {
            break;
        } else if (ch == 75) {
            selected = 3;
            break;
        }
        displayMenuAfterWriteToFile(selected);
    }
    return selected;
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

int selectedUtama = 0;
int selectMenuUtama() {
    int ch;

    while (1) {
        displayMenuUtama(selectedUtama);
        ch = getch();
        if (ch == 72) {
            selectedUtama = (selectedUtama == 0) ? 2 : --selectedUtama;
        } else if (ch == 80) {
            selectedUtama = (selectedUtama == 2) ? 0 : ++selectedUtama;
        } else if (ch == 13) {
            break;
        } else if (ch == 77) {
            break;
        } else if (ch == 75) {
            selectedUtama = 3;
            break;
        }
    }
    return selectedUtama;
}

int selectMenuEncode() {
    int ch;
    int selectedEncode = 0;

    while (1) {
        displayMenuEncode(selectedEncode);
        ch = getch();
        if (ch == 72) {
            selectedEncode = (selectedEncode == 0) ? 1 : 0;
        } else if (ch == 80) {
            selectedEncode = (selectedEncode == 1) ? 0 : 1;
        } else if (ch == 13) {
            break;
        } else if (ch == 77) {
            break;
        } else if (ch == 75) {
            selectedEncode = 2;
            break;
        }
    }
    return selectedEncode;
}

int selectMenuDecode() {
    int ch;
    int selectedDecode = 0;

    while (1) {
        displayMenuDecode(selectedDecode);
        ch = getch();
        if (ch == 72) {
            selectedDecode = (selectedDecode == 0) ? 1 : 0;
        } else if (ch == 80) {
            selectedDecode = (selectedDecode == 1) ? 0 : 1;
        } else if (ch == 13) {
            break;
        } else if (ch == 77) {
            break;
        } else if (ch == 75) {
            selectedDecode = 2;
            break;
        }
    }
    return selectedDecode;
}

void clearDisplay(int headerTop) {
    int i;
    moveToLine(13, left);
    for (i = 0; i <= 20; i++) {
        moveToLine(headerTop + i, left);
        printf("                                                                                                              ");
    }
}

void spaceToContinue() {
    printf("Tekan spasi untuk melanjutkan");
    while (getch() != ' ');
}

void displayTree(address root, int depth, bool *path, bool isRight) {
    const int spaces = 8;
    int i, j;

    if (root == NULL)
        return;

    depth++;
    displayTree(root->right, depth, path, true);

    if (depth - 2 >= 0) {
        path[depth - 2] = false;
    }

    if (isRight) {
        path[depth - 2] = true;
    }

    if (root->left) {
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
