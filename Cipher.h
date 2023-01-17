#pragma once

#define ASCII_OFFSET_LOWER	0x61

#include <iostream>
#include <random>
#include <string>

std::string
cipher_main(std::string content) {
	std::string ciph;
	int offset1;
	int offset2;
	int offset_counter = 0;


	srand((unsigned)time(NULL));
	int random = (rand() % 10);

	offset1 = random + 2;
	offset2 = (random + 2) / 2;

	char offset_str[] = {
		(char)(offset1 + ASCII_OFFSET_LOWER),
		(char)(offset2 + ASCII_OFFSET_LOWER),
		'\0'
	};

	ciph = offset_str;

	for (
		std::string::iterator it = content.begin();
		it != content.end();
		it++) {

		if (offset_counter % 2) {
			ciph.insert(ciph.end(), ((char)(*it)) + offset1);
		}

		else {
			ciph.insert(ciph.end(), ((char)(*it)) + offset2);
		}

		offset_counter++;
	}

	return ciph;
}

std::string
decipher_main(std::string ciph) {

	if (ciph.length() < 2) {
		std::string error_str = "This is not a valid cipher++ encoded string";
		return error_str;
	}

	int offset1 = (int)ciph[0] - ASCII_OFFSET_LOWER;
	int offset2 = (int)ciph[1] - ASCII_OFFSET_LOWER;
	int offset_counter = 0;
	std::string deciph;

	std::string content = ciph.c_str() + 2;

	for (
		std::string::iterator it = content.begin(); 
		it != content.end(); 
		it++) {
		
		if (offset_counter % 2) {
			deciph.insert(deciph.end(), ((char)(*it)) - offset1);
		}

		else {
			deciph.insert(deciph.end(), ((char)(*it)) - offset2);
		}

		offset_counter++;
	}

	return deciph;
}
