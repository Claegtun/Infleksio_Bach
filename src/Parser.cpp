/*
 * Parser.cpp
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

//Libraries:
#include "Parser.hpp"

using namespace std;

//Constructor:
Parser::Parser(const vector<Token>& inputTokens) {
	tokens = inputTokens;
	root = new Routine();
	finger = 0;
}

//Destructor:
Parser::~Parser() {
	if (root != NULL) {
		//delete root;
	}
}

//Setters:
/*
 * Function: 	parseRoutine
 * Summary: 	Parses the main block and sets it.
 * Arguments: 	None
 * Return: 		The root, i.e. the routine
 */
Routine* Parser::parseRoutine() {
	root->setBlock(parseBlock(root));
	return root;
}
/*
 * Function: 	parseBlock
 * Summary: 	Creates a new block. If the next token is hither, then
 * 				the block is done and is returned. Else, parses the
 * 				statement and sets it.
 * Arguments: 	The parent
 * Return: 		The newly made block
 */
Block* Parser::parseBlock(ASTNode* inputParent) {
	Block* block = new Block(inputParent);

	while (finger < tokens.size()) {
		switch (tokens[finger].getType()) {
			case HITHER:
				finger++;
				return block;
			default:
				block->addStatement(parseStatement(inputParent));
		}
	}

	return block;
}
/*
 * Function: 	parseStatement
 * Summary: 	Sees whether the next statement is an if-condition, a
 * 				while-condition, or an operation, parses it, and then
 * 				returns it.
 * Arguments: 	The parent
 * Return: 		The statement
 */
ASTNode* Parser::parseStatement(ASTNode* inputParent) {
	switch (tokens[finger].getType()) {
		case IF:
			finger++;
			return parseIfCondition(inputParent);
		case ASLONGAS:
			finger++;
			return parseWhileCondition(inputParent);
		default:
			return parseOperation(inputParent);
	}
	return new ASTNode();
}
/*
 * Function: 	parseOperation
 * Summary: 	Makes a new operation and then parses each token in the sentence until either the end of file
 * 				or the full-stop, i.e. the end of the operation.
 * Arguments: 	The parent
 * Return: 		The newly made operation
 */
Operation* Parser::parseOperation(ASTNode* inputParent) {
	//Declare local variables.
	Token currentToken;
	Operation* firstOperation = new Operation(inputParent, Token());
	Operation* currentOperation = firstOperation;
	Argument* tempArgument, * newArgument;
	Casting* tempCasting;
	int index;

	for (unsigned int tip = finger; tip < (unsigned int)tokens.size(); tip++) {
		//Define the current token.
		currentToken = tokens[tip];

		finger = tip+1;

		//Parse the suffix.
		switch (currentToken.getType()) {
			/*
			 * If the current token is either subjunctive or imperative i.e. an operation, then set the
			 * word of the operation as it.
			 */
			//Subjunctive:
			case subjunctive:
			//Imperative:
			case imperative:
				currentOperation->setWord(currentToken);
				break;
			/*
			 * If the current token is an adverb i.e. a casting, then insert the casting between the current
			 * operation.
			 */
			//Adverb:
			case adv:
				index = currentOperation->getWord().getIndex();
				tempArgument = new Casting(currentOperation->getParent(), currentToken);
				((Casting*) tempArgument)->setArgument(currentOperation);

				//If the current operation is the argument of a casting:
				if ((((Argument*)currentOperation->getParent())->getWord().getType() == adj)
				|| (((Argument*)currentOperation->getParent())->getWord().getType() == adv))
					((Casting*) (currentOperation->getParent()))->setArgument(tempArgument);
				//Else, the current operation is the argument of an operation:
				else
					((Operation*) (currentOperation->getParent()))->setArgument(tempArgument, index);

				tempArgument->setParent(currentOperation->getParent());
				currentOperation->setParent(tempArgument);
				break;
			/*
			 * If the current token is an argument, then see if there is already a casting.
			 */
			//Noun:
			case noun:
			case plural:
			//Literal:
			case litc:
			case litcard:
			case lits:
				index = currentToken.getIndex();
				tempArgument = currentOperation->getArgument(index);

				/*
				 * If there is already an existing argument in place, and its a casting, then recursively seek
				 * the end of the casting and set that as the argument.
				 */
				if ((tempArgument != NULL)
				&& ((tempArgument->getWord().getType() == adj)
					|| (tempArgument->getWord().getType() == adv)))
				{
					do {
						tempCasting = (Casting*)tempArgument;
						tempArgument = tempCasting->getArgument();
					} while ((tempArgument->getWord().getType() == adj)
					|| (tempArgument->getWord().getType() == adv));

					tempCasting->setArgument(new Argument(tempCasting, currentToken));
				}
				//Else, set the argument.
				else {
					//If there is already an existing argument in place, then delete it.
					if (tempArgument != NULL) delete tempArgument;

					currentOperation->setArgument(new Argument(currentOperation, currentToken), index);
				}

				break;
			//Adjective:
			case adj:
				index = currentToken.getIndex();
				tempArgument = currentOperation->getArgument(index);

				/*
				 * If there is already an existing argument in place, and its a casting, then recursively seek
				 * the end of the casting and set that as this current casting.
				 */
				if ((tempArgument != NULL)
				&& ((tempArgument->getWord().getType() == adj)
					|| (tempArgument->getWord().getType() == adv)))
				{
					//Seek the end of the casting.
					do {
						tempCasting = (Casting*)tempArgument;
						tempArgument = tempCasting->getArgument();
					} while ((tempArgument->getWord().getType() == adj)
					|| (tempArgument->getWord().getType() == adv));

					//Set this current casting at the end.
					tempCasting->setArgument(new Casting(tempCasting, currentToken));
					((Casting*) (tempCasting->getArgument()))->setArgument(tempArgument);

					//If there is an argument, then set its parent to this current casting.
					if (tempArgument != NULL)
						((Casting*) (tempCasting->getArgument()))
						->getArgument()->setParent(tempCasting->getArgument());
				}
				//Else, set the argument.
				else {
					//Set this current casting as the argument.
					currentOperation->setArgument(new Casting(currentOperation, currentToken), index);
					((Casting*) (currentOperation->getArgument(index)))->setArgument(tempArgument);

					//If there is an argument, then set its parent to this current casting.
					if (tempArgument != NULL)
						((Casting*) (currentOperation->getArgument(index)))
						->getArgument()->setParent(currentOperation->getArgument(index));
				}

				break;
			//Whether-clause:
			case WHETHER:
				//Parse the argument.
				/*currentOperation->setArgument(new Operation(currentOperation, Token()), currentToken.getIndex());
				currentOperation = (Operation*)currentOperation->getArgument(currentToken.getIndex());*/
				//break;
			//Participle:
			case participle:
				index = currentToken.getIndex();
				tempArgument = currentOperation->getArgument(index);

				/*
				 * If there is already an existing argument in place, and its a casting, then recursively seek
				 * the end of the casting and set that as this current operation.
				 */
				if ((tempArgument != NULL)
				&& ((tempArgument->getWord().getType() == adj)
					|| (tempArgument->getWord().getType() == adv)))
				{
					//Seek the end of the casting.
					do {
						tempCasting = (Casting*)tempArgument;
						tempArgument = tempCasting->getArgument();
					} while ((tempArgument->getWord().getType() == adj)
					|| (tempArgument->getWord().getType() == adv));

					//Set this current operation as the argument.
					tempCasting->setArgument(new Operation(tempCasting, currentToken));
					currentOperation = (Operation*)tempCasting->getArgument();
				}
				//Else, set the argument.
				else {
					//If there is already an existing argument in place, then delete it.
					if (tempArgument != NULL) delete tempArgument;

					currentOperation->setArgument(new Operation(currentOperation, currentToken), index);
					currentOperation = (Operation*)currentOperation->getArgument(index);
				}

				break;
			//Correlative conjunctions:
			case BOTH: case MAYBE: case EITHER: case NEITHER: case NOT:
				currentOperation->setWord(currentToken);
				currentOperation->setArgument(new Operation(currentOperation, Token()), 0);
				currentOperation = (Operation*)currentOperation->getArgument(0);
				break;
			case AND: case OR: case NOR:
				do {
					currentOperation = (Operation*)currentOperation->getParent();
				} while((currentOperation->getWord().getType() != BOTH)
				&& (currentOperation->getWord().getType() != MAYBE)
				&& (currentOperation->getWord().getType() != EITHER)
				&& (currentOperation->getWord().getType() != NEITHER)
				&& (currentOperation->getWord().getType() != NOT));

				index = currentOperation->getNumArg();
				currentOperation
				->setArgument(new Operation(currentOperation, Token("", nullType, index)), index);
				currentOperation = (Operation*)currentOperation->getArgument(index);
				break;
			//Ordinal:
			case ord:
			case litord:
				break;
			//End of file:
			case ende:
				return firstOperation;
			//Stop, i.e. end of clause:
			case stop:
				return firstOperation;
			//Comma, i.e. end of subclause:
			case comma:
				if (currentOperation != firstOperation)
					do {
						currentOperation = (Operation*)currentOperation->getParent();
					} while ((currentOperation->getWord().getType() == adj)
					|| (currentOperation->getWord().getType() == adv));
				else
					return firstOperation;
				break;
			//Unknown:
			default:
				break;
		}
	}
	return firstOperation;
}
/*
 * Function: 	parseIfCondition
 * Summary: 	Makes a new if-condition and parses the operation, the if-block, and any else-block.
 * Arguments: 	The parent
 * Return: 		The newly made if-condition
 */
IfCondition* Parser::parseIfCondition(ASTNode* inputParent) {
	//Declare local variables.
	IfCondition* condition = new IfCondition(inputParent, tokens[finger].getWord());

	//If:
	//Parse the operation, i.e. the clause.
	condition->setOperation(parseOperation());

	//If there is a correlating adverb, then parse a new block as the if-block.
	if ((tokens[finger].getType() == THEN) || (tokens[finger].getType() == HENCE)) {
		finger++;
		condition->setIfBlock(parseBlock());
	}
	//Else, then only parse one statement as the if-block.
	else {
		Block* smallBlock = new Block();
		smallBlock->addStatement(parseStatement());
		condition->setIfBlock(smallBlock);
	}

	//Else:
	if (tokens[finger].getType() == ELSE) {
		finger++;
		//If there is a correlating adverb, then parse a new block as the else-block.
		if ((tokens[finger].getType() == THEN) || (tokens[finger].getType() == HENCE)) {
			finger++;
			condition->setElseBlock(parseBlock());
		}
		//Else, then only parse one statement as the else-block.
		else {
			Block* smallBlock = new Block();
			smallBlock->addStatement(parseStatement());
			condition->setElseBlock(smallBlock);
		}
	}

	return condition;
}
/*
 * Function: 	parseWhileCondition
 * Summary: 	Makes a new while-condition and parses the operation and the block.
 * Arguments: 	The parent
 * Return: 		The newly made while-condition
 */
WhileCondition* Parser::parseWhileCondition(ASTNode* inputParent) {
	//Declare local variables.
	WhileCondition* condition = new WhileCondition(inputParent, tokens[finger].getWord());

	//ASLONGAS:
	//Parse the operation, i.e. the clause.
	condition->setOperation(parseOperation());

	//If there is a correlating adverb, then parse a new block as the block.
	if ((tokens[finger].getType() == THEN) || (tokens[finger].getType() == HENCE)) {
		finger++;
		condition->setBlock(parseBlock());
	}
	//Else, then only parse one statement as the block.
	else {
		Block* smallBlock = new Block();

		smallBlock->addStatement(parseStatement());
		condition->setBlock(smallBlock);
	}

	return condition;
}


