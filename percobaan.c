#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
int main() {
    char ch;
    clock_t start, end;
    double duration;
	
    printf("Tekan spasi untuk memulai...\n");

    while (getch() != ' '); // Menunggu spasi ditekan

    start = clock(); // Memulai waktu ketika spasi pertama ditekan
    printf("Spasi ditekan, tekan Enter untuk berhenti...\n");

    while ((ch = getch()) != '\r') {
        if (ch == ' ') {
            end = clock(); // Menghentikan waktu ketika spasi dilepas
            duration = (double)(end - start) / CLOCKS_PER_SEC; // Menghitung durasi tekanan spasi
            
            if(duration <= 0.03){ // Jika jarak kurang dari 0.03 detik
            	printf("\b\b \b\b - ");
			}
            start = clock(); // Memulai waktu untuk spasi berikutnya
	        
        }
        if(duration > 0.1){
        	printf(" .");
        	
		}
    }
    return 0;
	}
