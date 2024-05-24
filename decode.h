#ifndef decode_h
#define decode_h

// Address pointer ke node
typedef struct TreeNode* address;

// Struktur binary tree morse
struct TreeNode {
    char data;
    address left;
    address right;
};

// Fungsi untuk membuat simpul baru
address createNode(char data);

// Fungsi untuk membangun pohon Morse
address buildMorseTree();

// Fungsi mengubah morse ke char
char decodePerMorse(address root, char* morseCode);

// Fungsi mengubah morse ke string
char* decodeMorse(address Tree, char* morse);

// user input morse
char* readMorseInput();
#endif
