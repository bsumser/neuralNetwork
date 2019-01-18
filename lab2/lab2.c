#include <stdio.h>
#include <stdbool.h>
#define ROW 2
#define COL 2

bool arrayEqual(int a[ROW][COL], int b[ROW][COL], int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != b[i][j]) {
				printf("element %d of a is not eqaul to element %d of b", a[i][j], b[i][j]);
				return false;
			}
		}
	}
	printf("elements are equal");
	return true;
}

int main() {
	int a[ROW][COL] = {2,2,2,3};
	int b[ROW][COL] = {2,2,2,2};

	arrayEqual(a, b, 2, 2);
	return 0;
}
