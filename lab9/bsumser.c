#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int array[10];
	int sum = 0;
	srand(0);

	for (int i = 0; i < 10; i++)
	{
		array[i] = rand();
		sum += array[i];
	}
	printf("%d",sum);
}
