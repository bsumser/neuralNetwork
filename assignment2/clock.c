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
}

int main() {
	char buf[BUF_LEN] = {0};
	time_t rawtime = time(NULL);

	struct tm *ptm = localtime(&rawtime);

	strftime(buf, BUF_LEN, "%R", ptm);
	
	//char timeString[5];
	char timeString[5] = {buf[0],buf[1],buf[2],buf[3],buf[4]};

	puts(buf);

	printf("%c%c%c%c%c", timeString[0],timeString[1],timeString[2],timeString[3],timeString[4]);
}
