#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
	time_t ltime;

	time(&ltime);

	printf("the time is %s", ctime(&ltime));
}
