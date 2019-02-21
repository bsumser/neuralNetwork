#ifndef DATE_HPP_
#define DATE_HPP_

#include "cipher.hpp"

class DateCipher: public Cipher {
public:
	DateCipher(); //constructor

	virtual std::string encrypt( std::string &inputText);
	virtual std::string decrypt( std::string &inputText);

private:
	std::string date;
};

#endif /*DATE_HPP_*/
