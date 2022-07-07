/*
 * Token.c
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

//Libraries:
#include "Token.hpp"

using namespace std;

//Constructor:
Token::Token(const string& inputWord, const TokenType& inputType) {
	word = inputWord;
	type = inputType;
	index = 0;
}
Token::Token(const string& inputWord, const TokenType& inputType, const int& inputIndex) {
	word = inputWord;
	type = inputType;
	index = inputIndex;
}

//Destructor:
Token::~Token() {

}

//Setters:
void Token::setWord(const string& inputWord) {
	word = inputWord;
}
void Token::setType(const TokenType& inputType) {
	type = inputType;
}
void Token::setIndex(const int& inputIndex) {
	index = inputIndex;
}

//Getters:
const string Token::getWord() {
	return word;
}
const TokenType Token::getType() {
	return type;
}const int Token::getIndex() {
	return index;
}

const string Token::toString() {
	string s = "{";
	s += typeToString(type) + "," + word + "," + to_string(index) + "}";
	return s;
}


