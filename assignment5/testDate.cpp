#include <iostream>
#include "cipher.hpp"
#include "date.hpp"

int main() 
{
	DateCipher test;

	std::string message = "test test";

	std::string encryptText = test.encrypt(message);

	std::cout << encryptText << std::endl;

	return 0;
}
