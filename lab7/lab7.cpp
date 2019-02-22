#include <iostream>
#include <random>


int main()
{
	std::vector<int> v;

	std::default_random_engine generator;

	std::uniform_int_distribution<int> distribution(1,100);
	for(int i = 0; i < 15; i++) {
		int number = distribution(generator);
		v.push_back(number);
	}	
	
	return 0;
}
