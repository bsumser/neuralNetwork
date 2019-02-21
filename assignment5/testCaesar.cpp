#include <iostream>
#include "cipher.hpp"
#include "caesar.hpp"

int main() 
{
	CaesarCipher test;

	std::string message = "original text";

	std::string encryptText = test.encrypt(message);

	std::cout << encryptText << std::endl;

	std::string decryptText = test.decrypt(encryptText);
	
	std::cout << decryptText << std::endl;

	return 0;
}
