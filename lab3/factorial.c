#include <stdio.h>
#include "factorial.h"

int main() {
	printf("%d",factorial(5)); 
}

int factorial(int n) {
	int result = n;
	for (int i = 1; i < n; i++)
		result = result * i;
	return result;
}
