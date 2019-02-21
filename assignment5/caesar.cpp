#include "cipher.hpp"

//single arguement constructor
CaesarCipher::CaesarCipher() : Cipher(), shift(x) {

}

std::string
CaesarCipher::encrypt( std::string &inputText ) {
	std::string text = inputText;
	std::string::size_type len = text.length();

	for(int i = 0; i != len; ++i) {


	}
	
}
