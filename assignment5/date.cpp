#include "cipher.hpp"
#include "date.hpp"

//single arguement constructor
DateCipher::DateCipher() : Cipher(), date("101592") {

}

std::string
DateCipher::encrypt( std::string &inputText ) {
	std::string text = inputText;
	std::string::size_type len = text.length();

	std::string textNum = "";

	for(int i = 0; i != len; ++i) {
		int cnt = 1;
		if(text[i] == ' ')
			continue;
		text[i] = date[cnt];

		cnt++;
		if (cnt == 7)
			cnt = 1;
	}
	return textNum;

}
std::string
DateCipher::decrypt( std::string &inputText ) {

}
