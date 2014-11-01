/*
 * string_tokenizer.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Erik Ashcraft
 */

#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include <string>
#include <vector>
#include <sstream>

class StringTokenizer {
	private:
		std::vector<std::string*>* stringbuffer;
		int tokennum;

	public:
		StringTokenizer(std::string* bufferstring, char dlmtr) {
			stringbuffer = new std::vector<std::string*>();
			tokennum = 0;

			std::string s = (*bufferstring);
			std::istringstream buffer(s);

			for(std::string token; getline(buffer, token, dlmtr); ){
				stringbuffer->push_back(new std::string(token));
			}
		}
		~StringTokenizer();

		std::string* getNextToken(){
			std::string* token = stringbuffer->at(tokennum);
			tokennum++;
			return token;
		}

		bool hasNextToken(){
			return tokennum < stringbuffer->size();
		}
};

#endif /* STRING_TOKENIZER_H_ */
