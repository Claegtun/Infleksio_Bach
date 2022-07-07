/*
 * Lexer.h
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#ifndef LEXER_H_
#define LEXER_H_

//Libraries:
#include "enumerations.hpp" //TokenType, Case
#include "functions.hpp" //functions
#include "Token.hpp" //Token

#include <string> //string
#include <sstream> //stringstream
#include <vector> //vector

#include <iostream> //cout

class Lexer
{
    public:

        //Constructor:
        Lexer(const std::string& inputText = "");

        //Destructor:
        ~Lexer();

        //Setters:
        /*
         * Function: 	readTokens
         * Summary: 	Converts the text into a vector of tokens.
         * Arguments: 	None
         * Return: 		The vector of tokens
         */
        std::vector<Token> readTokens();

    private:
        //Declare private variables.
        std::string text;
        std::vector<Token> tokens;

};

#endif /* LEXER_H_ */
