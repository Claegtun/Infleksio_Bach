/*
 * Token.h
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#ifndef TOKEN_H_
#define TOKEN_H_

//Libraries:
#include "enumerations.hpp" //TokenType, Case
#include "functions.hpp" //toString()

#include <string> //string, to_string()

class Token
{
    public:
        //Constructor:
        Token(const std::string& inputWord = "", const TokenType& inputType = nullType);
        Token(const std::string&, const TokenType&, const int&);
        //Destructor:
        ~Token();

        //Setters:
        void setWord(const std::string&);
        void setType(const TokenType&);
        void setIndex(const int&);

        //Getters:
        const std::string getWord();
        const TokenType getType();
        const int getIndex();
        const std::string toString();

    private:
        //Declare private variables.
        std::string word;
        TokenType type;
        int index;
};

#endif /* TOKEN_H_ */
