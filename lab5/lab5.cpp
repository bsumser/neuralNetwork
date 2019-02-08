#include <stdio.h>



int main()
{
	int x = 5;
	int y = 6;

	increment1(x,y);
	std::cout << x << " " << y << std::endl;
	increment2(x,y);
	std::cout << x << " " << y << std::endl;
	increment3(x,y);
	std::cout << x << " " << y << std::endl;
		
	return 0;
}

void increment1(int x, int y);
void increment2(int &x, int &y);
void increment3(int *x, int *y);
