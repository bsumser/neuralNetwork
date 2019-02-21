#ifndef CAESARCIPHER_HPP_
#define CAESARCIPHER_HPP_

#include "cipher.hpp"

class CaesarCipher: public Cipher {
public:
	CaesarCipher(int s); //constructor

	virtual std::string encrypt( std::string &text );
	virtual std::string decrypt( std::string &text );

private:
	int shift;
};

#endif /* CAESARCIPHER_HPP_ */
