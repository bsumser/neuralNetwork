#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#define BUF_LEN 256

int main() {
	char buf[BUF_LEN] = {0};
	time_t rawtime = time(NULL);

	struct tm *ptm = localtime(&rawtime);

	strftime(buf, BUF_LEN, "%R", ptm);
	puts(buf);
}
