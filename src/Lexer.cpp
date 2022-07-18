/*
 * Lexer.cpp
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

//Libraries:
#include "Lexer.hpp"

using namespace std;

//Constructor:
Lexer::Lexer(const string& inputText) {
	text = inputText;
}

//Destructor:
Lexer::~Lexer() {}

//Setters:
/*
 * Function: 	readTokens
 * Summary: 	Converts the text into a vector of tokens.
 * Arguments: 	None
 * Return: 		The vector of tokens
 */
vector<Token> Lexer::readTokens() {
	//Declare local variables.
	stringstream ss;
	string word = "";
	bool isComment = false;
	bool isString = false;
	bool isNew = true;
	int l = text.size();
	char c;

	//Input the text into the stream.
	ss << text;

	//For each letter in the text, tokenise add it to the word.
	for (int i = 0; i < l; i++) {
		//Declare local varibles.
		int glue;
		int datIndex = 0;
		string suffix = "", stem = "";
		c = text[i];

		/*
		 * Find special characters. If the character is a special punctuation character, e.g. commenting
		 * brackets, quotation marks for strings, inverted commas for characters, etc. New line characters are
		 * ignored.
		 */

		//If the character is a line-feed or carriage-return, then pass to the next.
		if ((c == '\n') || (c == '\r'))
			continue;

		//If the characters are of a comment, then pass to the next.
		if (isComment) {
			//If it is the closing bracket, then the comment has ended.
			if (c == ']')
				isComment = false;
			continue;
		}

		//If it is the opening bracket, then the following are of a comment.
		if (c == '[') {
			isComment = true;
			//Continue to discount the current character, i.e. '['.
			continue;
		}
		//If it is double quotes, then see whether it is opening or closing.
		else if (c == '"') {
			//If the current word is nothing, then it is opening, and the following are of a string.
			if (word == "") isString = true;
			//Else, if the word's last letter is not '\', then it is closing, and string has ended.
			else if (word[word.size()-1] != '\\') isString = false;

			//Else, it is escaped, i.e. '\"', and add it to the word.
			word += '"';

			continue;
		}
		//If it is a stop, then see whether it is a decimal place or punctuation.
		else if (c == '.') {
			//If  the current word is an integer, and the next letter is a digit,
			//then it is a decimal place, and add it to the word.
			if ((word != "") && (i != l-1) && (isInt(word)) && (isdigit(text[i+1]) != 0)) {
				word += c;
				continue;
			}
			//Else, then it is punctuation.
			//If the current word is something, i.e. the stop is next to the letter before,
			//then step the index back so that the word is read as token and is cleared after.
			else if (word != "")
				i--;
			//Else, i.e. the stop is not next to a letter before, then make it the new word.
			else
				word = c;
		}
		//If it is a comma, then see whether it is next to a letter before.
		else if (c == ',') {
			/*
			 * If it is next to a letter before, then step the index back so that the word is read and is
			 * cleared after.
			 */
			if (word != "")
				i--;
			//Else, make it the new word.
			else
				word = c;
		}
		//If the letter is of a string, or the character is not a whitespace, then add the next letter.
		else if ((isString) || (c != ' ')) {
			word += c;
			continue;
		}

		/*
		 * If the code above has not continued, then read the word and determine its type of token and parse
		 * its suffix if needed.
		 */
		//Punctuations:
		if (word == ".")                tokens.push_back(Token(word, stop));
		else if (word == ",")           tokens.push_back(Token(word, comma));
		//Subordinating conjunctions and their correlating adverbs:
		else if (word == "if")          tokens.push_back(Token(word, IF));
		else if (word == "then")        tokens.push_back(Token(word, THEN));
		else if (word == "else")        tokens.push_back(Token(word, ELSE));
		else if (word == "elseif")      tokens.push_back(Token(word, ELSEIF));
		else if (word == "aslongas")    tokens.push_back(Token(word, ASLONGAS));
		else if (word == "while")       tokens.push_back(Token(word, WHILE));
		else if (word == "first")       tokens.push_back(Token(word, FIRST));
		else if (word == "sothat")      tokens.push_back(Token(word, SOTHAT));
		else if (word == "given")       tokens.push_back(Token(word, GIVEN));
		else if (word == "as")          tokens.push_back(Token(word, AS));
		else if (word == "unless")      tokens.push_back(Token(word, UNLESS));
		else if (word == "until")       tokens.push_back(Token(word, UNTIL));
		else if (word == "lest")        tokens.push_back(Token(word, LEST));
		else if (word == "hence")       tokens.push_back(Token(word, HENCE));
		else if (word == "hither")      tokens.push_back(Token(word, HITHER));
		//Correlating conjunctions:
		else if (word == "not")        	tokens.push_back(Token(word, NOT));
		else if (word == "both")       	tokens.push_back(Token(word, BOTH));
		else if (word == "and")        	tokens.push_back(Token(word, AND));
		else if (word == "maybe")      	tokens.push_back(Token(word, MAYBE));
		else if (word == "either")		tokens.push_back(Token(word, EITHER));
		else if (word == "or")          tokens.push_back(Token(word, OR));
		else if (word == "neither")  	tokens.push_back(Token(word, NEITHER));
		else if (word == "nor")  		tokens.push_back(Token(word, NOR));
		//Imperatives:
		else if ((word == "grow") || (word == "shrink") || (word == "make") || (word == "pass")
		|| (word == "end") || (word == "give") || (word == "use") || (word == "do"))
			tokens.push_back(Token(word, imperative));
		//Subjunctives:
		else if ((word == "bealike") || (word == "beunalike") || (word == "besmaller") || (word == "bebigger")
				 || (word == "beatmost") || (word == "beatleast"))
			tokens.push_back(Token(word, subjunctive));
		//Common participles:
		else if ((word.substr(0,5) == (stem = "added")) || (word.substr(0,5) == (stem = "taken"))
		|| (word.substr(0,8) == (stem = "differed")) || (word.substr(0,10) == (stem = "multiplied"))
		|| (word.substr(0,7) == (stem = "divided")) || (word.substr(0,7) == (stem = "matched"))
		|| (word.substr(0,6) == (stem = "pushed")) || (word.substr(0,8) == (stem = "inverted"))
		|| (word.substr(0,6) == (stem = "filled")) || (word.substr(0,7) == (stem = "growing"))
		|| (word.substr(0,5) == (stem = "grown")) || (word.substr(0,9) == (stem = "shrinking"))
		|| (word.substr(0,8) == (stem = "shrunken"))) {
			//Parse the suffix.
			if (word.length() == stem.length())
				//Accusative:
				tokens.push_back(Token(stem, participle, 0));
			else if (word.substr(0,stem.length()+2) == stem+"en") {
				//Dative:
				if (word.length() == stem.length()+2)
					tokens.push_back(Token(stem, participle, 1));
				else if (isInt(word.substr(stem.length()+2,string::npos))) {
					datIndex = stoi(word.substr(stem.length()+2,string::npos));
					tokens.push_back(Token(stem, participle, 1 + datIndex));
				}
			}
		}
		//Whether:
		else if (word == "whether")
			//Accusative:
			tokens.push_back(Token(word, WHETHER, 0));
		else if (word.substr(0,7) == (stem ="whethen")) {
			//Dative:
			if (word.length() == stem.length())
				tokens.push_back(Token(stem, WHETHER, 1));
			else if (isInt(word.substr(stem.length()+2,string::npos))) {
				datIndex = stoi(word.substr(stem.length()+2,string::npos));
				tokens.push_back(Token(stem, WHETHER, 1 + datIndex));
			}
		}
		//Stead:
		else if (word == "stead")
			tokens.push_back(Token(word, STEAD, 0));
		else if (word.substr(0,7) == (stem ="steaden")) {
			if (word.length() == stem.length())
				tokens.push_back(Token(stem, STEAD, 1));
			else if (isInt(word.substr(stem.length()+2,string::npos))) {
				datIndex = stoi(word.substr(stem.length()+2,string::npos));
				tokens.push_back(Token(stem, STEAD, 1 + datIndex));
			}
		}
		//Worth:
		else if (word == "worth")
			tokens.push_back(Token(word, WORTH, 0));
		else if (word.substr(0,7) == (stem ="worthen")) {
			if (word.length() == stem.length())
				tokens.push_back(Token(stem, WORTH, 1));
			else if (isInt(word.substr(stem.length()+2,string::npos))) {
				datIndex = stoi(word.substr(stem.length()+2,string::npos));
				tokens.push_back(Token(stem, WORTH, 1 + datIndex));
			}
		}
		//If the word is not a keyword, then parse it as either a noun, literal, adjective, or participle.
		else {
			//Find the '-' in the word.
			glue = word.find_last_of('-');

			//If the word does not have a suffix, then continue.
			if (glue == string::npos)
				continue;
			//Else, read it and the stem, i.e. stem-suffix.
			suffix = word.substr(glue+1);
			stem = word.substr(0, glue);

			//If the word is a dative noun, and the suffix has an integer at the end, then set the index as it.
			if (((suffix.substr(0,2) == "en") || (suffix.substr(0,2) == "in"))
				&& (suffix.length() > 2) && isInt(suffix.substr(2,string::npos))) {
				datIndex = stoi(suffix.substr(2,string::npos));
				suffix = suffix.substr(0,2);
			}
			/*
			 * Else, if the word is a dative participle or dative cardinal, and the suffix has an integer at
			 * the end, then set the index as it.
			 */
			else if (((suffix.substr(0,3) == "den") || (suffix.substr(0,3) == "ten"))
				&& (suffix.length() > 3) && isInt(suffix.substr(3,string::npos))) {
				datIndex = stoi(suffix.substr(3,string::npos));
				suffix = suffix.substr(0,3);
			}

			//Parse the suffix.
			if (suffix == "o") 			tokens.push_back(Token(stem, subjunctive));
			else if (suffix == "u") 	tokens.push_back(Token(stem, imperative));
			else if (suffix == "ly") 	tokens.push_back(Token(stem, adverb));
			else if (suffix == "e") 	tokens.push_back(Token(stem, singular, 0));
			else if (suffix == "en") 	tokens.push_back(Token(stem, singular, 1 + datIndex));
			else if (suffix == "es") 	tokens.push_back(Token(stem, singular, gen));
			else if (suffix == "a") 	tokens.push_back(Token(stem, plural, 0));
			else if (suffix == "an") 	tokens.push_back(Token(stem, plural, 1 + datIndex));
			else if (suffix == "as") 	tokens.push_back(Token(stem, plural, gen));
			else if (suffix == "i") 	tokens.push_back(Token(stem, adjective, 0));
			else if (suffix == "in") 	tokens.push_back(Token(stem, adjective, 1 + datIndex));
			else if (suffix == "de") 	tokens.push_back(Token(stem, participle, 0));
			else if (suffix == "den") 	tokens.push_back(Token(stem, participle, 1 + datIndex));
			else if (suffix == "te") 	tokens.push_back(Token(stem, ordinal, 0));
			else if (suffix == "ten") 	tokens.push_back(Token(stem, ordinal, 1 + datIndex));
			else if (suffix == "tes") 	tokens.push_back(Token(stem, ordinal, gen));
		}

		//Clear the word.
		word = "";
	}

	//Add an end-of-file.
	tokens.push_back(Token("", ende));

	//Return the tokens.
	return tokens;
}


