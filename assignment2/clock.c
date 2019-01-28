#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#define BUF_LEN 256
#define HEIGHT 8
#define WIDTH 30 

void printClock() {
	char clock[HEIGHT][WIDTH];
	
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 14; j++) {
				clock[i][j] = ' ';
		}
	}

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j<= 5; j++) {
			if (i == 1 && j == 3)
				clock[i][j] = '$';
			if (i == 2 && ((j == (2)) || (j == 3)))
				clock[i][j] = '$';
			if (i == 3 && j == 3)
				clock[i][j] = '$';
			if (i == 4 && j == 3)
				clock[i][j] = '$';
			if (i == 5 && j == 3)
				clock[i][j] = '$';
			if (i == 6 && j == 3)
				clock[i][j] = '$';
			if (i == 7 && j == 3)
				clock[i][j] = '$';
			if (i == 8 && ((j == 2) || (j == 3) || (j == 4)))
				clock[i][j] = '$';
		}
	}
	for (int i = 1; i <= 8; i++) {
		for (int j = 6; j<= 9; j++) {
			if (i == 1 && ((j == 7) || (j == 8) || (j == 9)))
				clock[i][j] = '$';
			if (i == 2 && ((j == (6)) || (j == 9)))
				clock[i][j] = '$';
			if (i == 3 && j == 9)
				clock[i][j] = '$';
			if (i == 4 && j == 9)
				clock[i][j] = '$';
			if (i == 5 && j == 8)
				clock[i][j] = '$';
			if (i == 6 && j == 7)
				clock[i][j] = '$';
			if (i == 7 && j == 6)
				clock[i][j] = '$';
			if (i == 8 && ((j == 6) || (j == 7) || (j == 8) || (j == 9)))
				clock[i][j] = '$';
		}
	}
	for (int i = 1; i <= 8; i++) {
		for (int j = 11; j<= 14; j++) {
			if (i == 1 && ((j == 11) || (j == 13) || (j == 14) || (j == 15)))
				clock[i][j] = '$';
			if (i == 2 && (j == (14)))
				clock[i][j] = '$';
			if (i == 3 && j == 14)
				clock[i][j] = '$';
			if (i == 4 && ((j == 11) || (j == 12) || (j == 13) || (j == 14)))
				clock[i][j] = '$';
			if (i == 5 && j == 14)
				clock[i][j] = '$';
			if (i == 6 && j == 14)
				clock[i][j] = '$';
			if (i == 7 && j == 14)
				clock[i][j] = '$';
			if (i == 8 && ((j == 11) || (j == 12) || (j == 13) || (j == 14)))
				clock[i][j] = '$';
		}
	}
	
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j<= 14; j++) {
			printf("%c", clock[i][j]);
		}
		printf("\n");
	}
}

int main() {
	//char buf[BUF_LEN] = {0};
	//time_t rawtime = time(NULL);

	//struct tm *ptm = localtime(&rawtime);

	//strftime(buf, BUF_LEN, "%R", ptm);
	//
	////char timeString[5];
	//char timeString[5] = {buf[0],buf[1],buf[2],buf[3],buf[4]};

	//puts(buf);

	//printf("%c%c%c%c%c", timeString[0],timeString[1],timeString[2],timeString[3],timeString[4]);


	//printf("\n");
	printClock();
}
