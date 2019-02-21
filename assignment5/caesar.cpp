#include "cipher.hpp"
#include "caesar.hpp"

//single arguement constructor
CaesarCipher::CaesarCipher() : Cipher(), shift(12) {

}

std::string
CaesarCipher::encrypt( std::string &inputText ) {
	std::string text = inputText;
	std::string::size_type len = text.length();

	std::string output = "";

	for(int i = 0; i != len; ++i) {
		if (text[i] > 64 && text[i] < 91) {
			//encrypt uppercase
			output += char(int(text[i]+shift -65)%26 +65);
		}
		else if (text[i] > 96 && text[i] < 123) {
			//encrypt lowercase
			output += char(int(text[i]+shift -97)%26 +97);
		}
		else {
			//encrypt space
		}
	}
	return output;
}

std::string
CaesarCipher::decrypt(std::string &inputText) {
	std::string text = inputText;
	std::string::size_type len = text.length();

	std::string output = "";

	for(int i = 0; i != len; ++i) {
		if (text[i] > 64 && text[i] < 91) {
			//encrypt uppercase
			output += char(int(text[i]-shift -65)%26 +65);
		}
		else if (text[i] > 96 && text[i] < 123) {
			//encrypt lowercase
			output += char(int(text[i]-shift -97)%26 +97);
		}
		else {
			//encrypt space
		}
	}
	return output;
}
