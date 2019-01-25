#include "power.h"
#include <stdio.h>

int main(){
	printf("%f", power(2,2));
}

double power(double a, double b) {
	for (int i = 1; i < b; i++)
		a *= a;
	return a;
}
