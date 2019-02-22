#include <iostream>
#include <random>

int printVector(const std::vector<int> &v);

int main()
{
	std::vector<int> v;

	std::default_random_engine generator;

	std::uniform_int_distribution<int> distribution(1,100);
	for(int i = 0; i < 15; i++) {
		int number = distribution(generator);
		v.push_back(number);
	}
	printVector(v);	
	return 0;
}

int printVector(const std::vector<int> &v)
{
	std::vector<int>::const_iterator it; 
	for (it = v.begin(); it != v.end(); ++it)
			std::cout << "\t" << *it;
	return 0;	
}
