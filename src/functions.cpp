/*
 * functions.c
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

//Libraries:
#include "functions.hpp"

using namespace std;

/*
Parameters: the string to be checked
Return: whether it is an adverb or conjunction
*/
const bool isAdvConj(const string& s) {
    bool whether;
    string advConj[] = {"if", "then", "else", "elseif", "while", "first", "as", "then", "also", "sothat", "given", "when",
                        "unless", "until", "lest",
                        "hence", "hither",
                        "and", "or", "not", "eitheror", "neithernor"};
    for (int i = 0; i < (sizeof(advConj)/sizeof(*advConj)); i++) {
        whether = whether || (s == advConj[i]);
    }
    return whether;
}

/*
Parameters: a string to see whether it is an integer
Return: whether the string is an integer
*/
bool isInt(const string& s) {
    int l = s.length();
    bool whether = true;

    for (int i = 0; i < l; i++) {
        if ((i == 0) && (s.substr(0,1) == "-")) continue;
        whether = (whether && isdigit(s[i]));
    }

    return whether;
}

/*
*/
const string caseToString(const Case& inputCase) {
    switch (inputCase) {
        case acc: return "accusative";
        case dat: return "dative";
        case gen: return "genitive";
        default:
        case nullCase: return "null";
    }
}

/*
*/
const string typeToString(const TokenType& inputType) {
    switch (inputType) {
        case noun: return "noun";
        case plural: return "plural noun";
        //case card: return "cardinal";
        case litc: return "literal character";
        case litcard: return "literal cardinal";
        case litord: return "literal ordinal";
        case lits: return "literal string";
        case adj: return "adjective";
        case adv: return "adverb";
        case imperative: return "imperative";
        case subjunctive: return "subjunctive";
        case participle: return "participle";
        case comma: return "comma";
        case stop: return "stop";
        case IF: return "IF";
        case THEN: return "THEN";
        case ELSE: return "ELSE";
        case ELSEIF: return "ELSEIF";
        case ASLONGAS: return "ASLONGAS";
        case WHILE: return "WHILE";
        case FIRST: return "FIRST";
        case SOTHAT: return "SOTHAT";
        case GIVEN: return "GIVEN";
        case AS: return "AS";
        case UNLESS: return "UNLESS";
        case UNTIL: return "UNTIL";
        case LEST: return "LEST";
        case HENCE: return "HENCE";
        case HITHER: return "HITHER";
        case NOT: return "NOT";
        case BOTH: return "BOTH";
        case AND: return "AND";
        case MAYBE: return "MAYBE";
        case EITHER: return "EITHER";
        case OR: return "OR";
        case NEITHER: return "NEITHER";
        case NOR: return "NOR";
        case WHETHER: return "WHETHER";
        case STEAD: return "STEAD";
        case STAFF: return "STAFF";
        case SHORT: return "SHORT";
        case WHOLE: return "WHOLE";
        case LONG: return "LONG";
        case REAL: return "REAL";
        case PRECISE: return "PRECISE";
        case BOOLEAN: return "BOOLEAN";
        case NOTHING: return "NOTHING";
        case FULL: return "FULL";
        case STONE: return "STONE";
        case MAKE: return "MAKE";
        case PASS: return "PASS";
        case END: return "END";
        case GIVE: return "GIVE";
        case USE: return "USE";
        case DO: return "DO";
        case ADDED: return "ADDED";
        case TAKEN: return "TAKEN";
        case DIFFERED: return "DIFFERED";
        case MULTIPLIED: return "MULTIPLIED";
        case DIVIDED: return "DIVIDED";
        case MATCHED: return "MATCHED";
        case PUSHED: return "PUSHED";
        case INVERTED: return "INVERTED";
        case FILLED: return "FILLED";
        case NEGATIVE: return "NEGATIVE";
        case ALIKE: return "ALIKE";
        case UNALIKE: return "UNALIKE";
        case SMALLER: return "SMALLER";
        case BIGGER: return "BIGGER";
        case ATMOST: return "ATMOST";
        case ATLEAST: return "ATLEAST";
        case GROW: return "GROW";
        case GROWING: return "GROWING";
        case GROWN: return "GROWN";
        case SHRINK: return "SHRINK";
        case SHRINKING: return "SHRINKING";
        case SHRUNKEN: return "SHRUNKEN";
        case lBracket: return "left bracket";
        case rBracket: return "right bracket";
        case ende: return "end";
        default:
        case nullType: return "null";
    }
}

/*

*/
/*const string translateClause(stringstream& ss) {

}*/
