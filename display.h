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

int selectMenuAfterWriteToFile();

// Menunggu user menekan spasi untuk melanjutkan
void spaceToContinue();

//
void moveToLine(int line, int column);


void displayMenuWriteToFile(int selected);


void displayMenuAfterWriteToFile(int selected);
	

int selectMenuWriteToFile();


void header();

void hideCursor();

void showCursor();


void setFullScreen();

void clearDisplay(int headerTop);
#endif
