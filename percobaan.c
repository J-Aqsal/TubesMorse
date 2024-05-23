#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Address pointer ke node
typedef struct TreeNode* address;

// Struktur binary tree morse
struct TreeNode {
    char data;
    address left;
    address right;
};

// Fungsi untuk membuat simpul baru
address createNode(char data) {
    address newNode = (address)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fungsi untuk membangun pohon Morse
address buildMorseTree() {
    address root = createNode(' ');
    root->left = createNode('E');
    root->right = createNode('T');
    root->left->left = createNode('I');
    root->left->right = createNode('A');
    root->right->left = createNode('N');
    root->right->right = createNode('M');
    root->left->left->left = createNode('S');
    root->left->left->right = createNode('U');
    root->left->right->left = createNode('R');
    root->left->right->right = createNode('W');
    root->right->left->left = createNode('D');
    root->right->left->right = createNode('K');
    root->right->right->left = createNode('G');
    root->right->right->right = createNode('O');
    root->left->left->left->left = createNode('H');
    root->left->left->left->right = createNode('V');
    root->left->left->right->left = createNode('F');
    root->left->right->left->left = createNode('L');
    root->left->right->right->left = createNode('P');
    root->left->right->right->right = createNode('J');
    root->right->left->left->left = createNode('B');
    root->right->left->left->right = createNode('X');
    root->right->left->right->left = createNode('C');
    root->right->left->right->right = createNode('Y');
    root->right->right->left->left = createNode('Z');
    root->right->right->left->right = createNode('Q');
//    root->left->right->right->right->right = createNode('1');
//    root->left->left->right->right->right = createNode('2');
//    root->left->left->left->right->right = createNode('3');
//    root->left->left->left->left->right = createNode('4');
//    root->left->left->left->left->left = createNode('5');
//    root->right->left->left->left->left = createNode('6');
//    root->right->right->left->left->left = createNode('7');
//    root->right->right->right->left->left = createNode('8');
//    root->right->right->right->right->left = createNode('9');
//    root->right->right->right->right->right = createNode('0');
    
//    root->left->right->left->right->left->right = createNode('.');
//    root->right->right->left->left->right->right = createNode(',');
//    root->left->left->right->right->left->left = createNode('?');
//    root->right->left->right->left->right->right = createNode('!');
//    root->right->right->right->right->left->left->left = createNode(':');
//    root->right->left->left->left->right = createNode('=');
//    root->left->right->left->left->right->left = createNode('"');
    return root;
}

// Fungsi untuk mencari karakter dari pohon Morse
char decodeMorse(address root, char* morseCode) {
    if (root == NULL || morseCode == NULL) {
        return '\0';
    }
    int i = 0;
    while (morseCode[i] != '\0') {
        if (morseCode[i] == '.') {
            root = root->left;
        } else if (morseCode[i] == '-') {
            root = root->right;
        } else {
            return '\0'; // Jika karakter tidak valid, kembalikan null
        }
        i++;
    }
    return root->data; // Kembalikan karakter saat ini jika sudah selesai dengan kode Morse
}

int main() {
    address morseTree = buildMorseTree();

    printf("Masukkan pesan Morse (gunakan z untuk titik dan x untuk strip, spasi antara karakter, dua spasi untuk kata baru):\n");
    char morseInput[100];
    int j = 0;
    char ch;
    bool prevSpace = false; // Untuk mendeteksi dua spasi berturut-turut

    // Membaca input karakter demi karakter menggunakan getch
    while ((ch = getch()) != '\r'){
        if (ch == 'z') {
            morseInput[j++] = '.';
            printf(".");
        } else if (ch == 'x') {
            morseInput[j++] = '-';
            printf("-");
        } else if (ch == ' ') {
            morseInput[j++] = ' ';
            printf(" ");
        } else if (ch == '\b') {
            morseInput[j++] = '\b';
            printf("\b");
        }else if (ch == '/') {
            morseInput[j++] = '/';
            printf("/");
        }
        else{
        	continue;
		}
    }
    printf("\n");

    // Proses setiap kata Morse dalam pesan secara terpisah
    char* token = strtok(morseInput, " ");
    while (token != NULL) {
        if (strcmp(token, "/") == 0) {
            printf(" ");
        } else {
            printf("%c", decodeMorse(morseTree, token));
        }
        token = strtok(NULL, " ");
    }

    printf("\n");

    return 0;
}

