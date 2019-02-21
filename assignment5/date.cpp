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
	int cnt = 0;

	for(int i = 0; i != len; ++i) {
		if (text[i] == ' ')
			continue;
		textNum += date[cnt];
		text[i] = text[i + textNum[i]];

		cnt++;
		if (cnt == 7)
			cnt = 0;
	}
	return textNum;

}
std::string
DateCipher::decrypt( std::string &inputText ) {

}
