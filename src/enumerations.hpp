/*
 * enumerations.h
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#ifndef ENUMERATIONS_HPP_
#define ENUMERATIONS_HPP_

//Types of tokens:
enum TokenType {
	//Types of arguments:
    noun, plural, ord, lits, litcard, litord, litc, adj, adv,
	//Types of operations:
    imperative, subjunctive, participle,
	//Punctuation:
    comma, stop,
	//Subordinating conjunctions:
    IF, THEN, ELSE, ELSEIF, ASLONGAS, WHILE, FIRST, SOTHAT, GIVEN, AS, UNLESS, UNTIL, LEST, HENCE, HITHER,
	//Correlating conjunctions:
    BOTH, AND, MAYBE, OR, EITHER, NOT, NEITHER, NOR, WHETHER,
	//Reference of argument:
    STEAD, WORTH,
	//Common types:
    STAFF, SHORT, WHOLE, LONG, REAL, PRECISE, BOOLEAN, NOTHING,
	//
    FULL, STONE,
	//Common imperatives:
    MAKE, PASS, END, GIVE, USE, DO,
	//Common participles:
    ADDED, TAKEN, DIFFERED, MULTIPLIED, DIVIDED, MATCHED, PUSHED, INVERTED, FILLED, NEGATIVE,
    LEFTSHIFT, RIGHTSHIFT,
	//Common subjunctives:
    ALIKE, UNALIKE, SMALLER, BIGGER, ATMOST, ATLEAST,
	//Common operations:
    GROW, GROWING, GROWN, SHRINK, SHRINKING, SHRUNKEN,
	//Commenting punctuation:
    lBracket, rBracket, lParenthesis, rParenthesis,

    ende, nullType
};

//Cases for arguments:
enum Case {acc, dat, gen, nullCase};

#endif /* ENUMERATIONS_HPP_ */
