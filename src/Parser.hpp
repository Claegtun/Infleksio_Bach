/*
 * Parser.h
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#ifndef PARSER_H_
#define PARSER_H_

//Libraries:
#include "ASTNode.hpp" //ASTNode
#include "Token.hpp" //Token
#include <string> //string
#include <vector> //vector
#include <iostream> //cout (debugging £)

class Parser
{
    public:
        //Constructor:
        Parser(const std::vector<Token>& inputTokens = std::vector<Token>());

        //Destructor:
        ~Parser();

        //Setters:
        /*
         * Function: 	parseRoutine
         * Summary: 	Parses the main block and sets it.
         * Arguments: 	None
         * Return: 		The root, i.e. the routine
         */
        Routine* parseRoutine();
        /*
         * Function: 	parseBlock
         * Summary: 	Creates a new block. If the next token is hither, then
         * 				the block is done and is returned. Else, parses the
         * 				statement and sets it.
         * Arguments: 	The parent
         * Return: 		The newly made block
         */
        Block* parseBlock(ASTNode* inputParent = NULL);
        /*
         * Function: 	parseStatement
         * Summary: 	Sees whether the next statement is an if-condition, a
         * 				while-condition, or an operation, parses it, and then
         * 				returns it.
         * Arguments: 	The parent
         * Return: 		The statement
         */
        ASTNode* parseStatement(ASTNode* inputParent = NULL);
        /*
         * Function: 	parseOperation
         * Summary: 	Makes a new operation and then parses each token in the
         * 				sentence until either the end of file or the full-stop,
         * 				i.e. the end of the operation.
         * Arguments: 	The parent
         * Return: 		The newly made operation
         */
        Operation* parseOperation(ASTNode* inputParent = NULL);
        /*
         * Function: 	parseIfCondition
         * Summary: 	Makes a new if-condition and parses the operation, the
         * 				if-block, and any else-block.
         * Arguments: 	The parent
         * Return: 		The newly made if-condition
         */
        IfCondition* parseIfCondition(ASTNode*);
        /*
         * Function: 	parseWhileCondition
         * Summary: 	Makes a new while-condition and parses the operation
         * 				and the block.
         * Arguments: 	The parent
         * Return: 		The newly made while-condition
         */
        WhileCondition* parseWhileCondition(ASTNode*);

    private:
        std::vector<Token> tokens;
        Routine* root;
        int finger;
};

#endif /* PARSER_H_ */
