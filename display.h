#ifndef display_h
#define display_h

// Tampilan menu utama
void displayMenuUtama(int selectedUtama);

// Tampilan menu encode
void displayMenuEncode(int selectedEncode);

// Tampilan menu decode
void displayMenuDecode(int selectedDecode);

// Pilihan menu utama
int selectMenuUtama();

// Pilihan menu encode
int selectMenuEncode();
	
// Pilihan menu decode
int selectMenuDecode();

// Menunggu user menekan spasi untuk melanjutkan
void spaceToContinue();

//
void moveToLine(int line, int column);


void displayMenuWriteToFile(int selected);


int selectMenuWriteToFile();


void header();

void hideCursor();

void showCursor();
#endif
