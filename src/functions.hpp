/*
 * functions.h
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

//Libraries:
#include <string> //string
#include <sstream> //stringstream
#include <fstream> //files
#include "enumerations.hpp" //TokenType, Case

/*
Parameters: the string to be checked
Return: whether it is an adverb or conjunction
*/
const bool isAdvConj(const std::string&);

/*
Parameters: a string to see whether it is an integer
Return: whether the string is an integer
*/
bool isInt(const std::string&);

/*
*/
const std::string caseToString(const Case&);

/*
*/
const std::string typeToString(const TokenType&);

/*

*/
//const std::string translateClause(std::stringstream&);

#endif /* FUNCTIONS_HPP_ */
