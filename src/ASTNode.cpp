/*
 * ASTNode.cpp
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#include "ASTNode.hpp"

using namespace std;

/*
 * ASTNode:
 */

//Constructor:
ASTNode::ASTNode(ASTNode* inputParent) {
	parent = inputParent;
}

//Destructor:
ASTNode::~ASTNode() {}

//Setters:
void ASTNode::setParent(ASTNode* inputParent) {
	parent = inputParent;
}

//Getters:
ASTNode* ASTNode::getParent() {
	return parent;
}

const string ASTNode::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	return s;
}

/*
 * Block:
 */

//Constructor:
Block::Block(ASTNode* inputParent)
: ASTNode(inputParent) {}

//Destructor:
Block::~Block() {
	int l = statements.size();
	for (int i = 0; i < l; i++) {
		if (statements[i] != NULL) {
			delete statements[i];
			statements[i] = NULL;
		}
	}
}

//Setters:
void Block::setStatement(const int& index, ASTNode* inputStatement) {
	statements[index] = inputStatement;
}
void Block::addStatement(ASTNode* inputStatement) {
	statements.push_back(inputStatement);
}

//Getters:
ASTNode* Block::getStatement(const int& index) {
	return statements[index];
}
const int Block::getNumber() {
	return statements.size();
}
const string Block::writeTree() {
	return writeTree(0);
}
const string Block::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "Block:";

	for (int i = 0; i < statements.size(); i++) {
		if (statements[i] != NULL)
			s += "\n" + statements[i]->writeTree(indent+1);
	}

	return s;
}

/*
 * Routine:
 */

//Constructor:
Routine::Routine(ASTNode* inputParent, Block* inputBlock)
: ASTNode(inputParent) {
	block = inputBlock;
}

//Destructor:
Routine::~Routine() {
	if (block != NULL) {
		delete block;
		block = NULL;
	}
}

//Setters:
void Routine::setBlock(Block* inputBlock) {
	block = inputBlock;
}

//Getters:
Block* Routine::getBlock() {
	return block;
}
const string Routine::writeTree() {
	return block->writeTree();
}

/*
 * Argument:
 */

//Constructor:
Argument::Argument(ASTNode* inputParent, const Token& inputWord)
: ASTNode(inputParent) {
	word = inputWord;
}

//Destructor:
Argument::~Argument() {
}

//Setters:
void Argument::setWord(const Token& inputWord) {
	word = inputWord;
}

//Getters:
Token Argument::getWord() {
	return word;
}

const string Argument::writeTree() {
	return writeTree(0);
}
const string Argument::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "Argument:" + word.toString();

	return s;
}

/*
 * Partitive:
 */

//Constructor:
Partitive::Partitive(ASTNode* inputParent, const Token& inputWord)
: Argument(inputParent, inputWord) {
	part = NULL;
	genitive = NULL;
}

//Destructor:
Partitive::~Partitive() {
}

//Setters:
void Partitive::setPart(Argument* inputPart) {
	part = inputPart;
}
void Partitive::setGenitive(Argument* inputGenitive) {
	genitive = inputGenitive;
}

//Getters:
Argument* Partitive::getPart() {
	return part;
}
Argument* Partitive::getGenitive() {
	return genitive;
}
const string Partitive::writeTree() {
	return writeTree(0);
}
const string Partitive::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "Partitive:" + word.toString();

	s += "\n" + part->writeTree(indent+1);

	s += "\n" + genitive->writeTree(indent+1);

	return s;
}

/*
 * Operation:
 */

//Constructor:
Operation::Operation(ASTNode* inputParent, const Token& inputWord)
: Argument(inputParent, inputWord) {
	MAX = 100;
	numArg = 0;
	for (int i = 0; i < MAX; i++) {
		arguments[i] = NULL;
	}
}

//Destructor:
Operation::~Operation() {
	int l = MAX;

	for (int i = 0; i < l; i++) {
		if (arguments[i] != NULL) {
			delete arguments[i];
			arguments[i] = NULL;
		}
	}
}

//Setters:
void Operation::setArgument(Argument* inputArgument, const int& index) {
	if (index >= numArg) numArg = index + 1;
	//if (index >= dative.size())
		//dative.push_back(inputDative);

	/*if (arguments[index] != NULL) {
		delete arguments[index];
		arguments[index] = NULL;
	}*/

	arguments[index] = inputArgument;
}

//Getters:
Argument* Operation::getArgument(const int& index) {
	/*if (index < dative.size())
		return dative[index];
	else
		return nullptr;*/
	return arguments[index];
}
const int Operation::getNumArg() {
	return numArg;
	//return dative.size();
}

const string Operation::writeTree() {
	return writeTree(0);
}
const string Operation::writeTree(const int& indent) {
	string s = "";
	//int l = dative.size();
	int l = MAX;

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "Operation:" + word.toString() + " " + to_string(numArg);

	for (int i = 0; i < l; i++) {
		if (arguments[i] != NULL)
			s += "\n" + arguments[i]->writeTree(indent+1);
	}

	return s;
}

/*
 * Casting:
 */

//Constructor:
Casting::Casting(ASTNode* inputParent, const Token& inputToken)
: Argument(inputParent, inputToken) {
	argument = NULL;
}

//Destructor:
Casting::~Casting() {
	delete argument;
	argument = NULL;
}

//Setters:
void Casting::setArgument(Argument* inputArgument) {
	argument = inputArgument;
}

//Getters:
Argument* Casting::getArgument() {
	return argument;
}

const string Casting::writeTree() {
	return writeTree(0);
}
const string Casting::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "Casting:" + word.toString() + "\n" + argument->writeTree(indent+1);

	return s;
}

/*
 * IfCondition
 */

//Constructor:
IfCondition::IfCondition(ASTNode* inputParent, const Token& inputWord)
: ASTNode(inputParent) {
	word = inputWord;

	MAX = 100;
	numElse = 0;

	ifOperation = NULL;
	ifBlock = NULL;
	elseBlock = NULL;
}

//Destructor:
IfCondition::~IfCondition() {
	if (ifOperation != NULL) {
		delete ifOperation;
		ifOperation = NULL;
	}

	if (ifBlock != NULL) {
		delete ifBlock;
		ifBlock = NULL;
	}

	if (elseBlock != NULL) {
		delete elseBlock;
		elseBlock = NULL;
	}
}

//Setters:
void IfCondition::setOperation(Operation* inputClause) {
	ifOperation = inputClause;
}
void IfCondition::setIfBlock(Block* inputBlock) {
	ifBlock = inputBlock;
}
void IfCondition::setElseBlock(Block* inputBlock) {
	elseBlock = inputBlock;
}

//Getters:
Operation* IfCondition::getOperation() {
	return ifOperation;
}
Block* IfCondition::getIfBlock() {
	return ifBlock;
}
Block* IfCondition::getElseBlock() {
	return elseBlock;
}
const string IfCondition::writeTree() {
	return writeTree(0);
}
const string IfCondition::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "If:";

	if (ifOperation != NULL) s += "\n" + ifOperation->writeTree(indent+1);
	if (ifBlock != NULL) s += "\n" + ifBlock->writeTree(indent+1);
	if (elseBlock != NULL) s += "\n" + elseBlock->writeTree(indent+1);

	return s;
}

/*
 * WhileCondition
 */

//Constructor:
WhileCondition::WhileCondition(ASTNode* inputParent, const Token& inputWord)
: ASTNode(inputParent) {
	word = inputWord;

	asOperation = NULL;
	thenBlock = NULL;
}

//Destructor:
WhileCondition::~WhileCondition() {
	if (asOperation != NULL) {
		delete asOperation;
		asOperation = NULL;
	}

	if (thenBlock != NULL) {
		delete thenBlock;
		thenBlock = NULL;
	}
}

//Setters:
void WhileCondition::setOperation(Operation* inputClause) {
	asOperation = inputClause;
}
void WhileCondition::setBlock(Block* inputBlock) {
	thenBlock = inputBlock;
}

//Getters:
Operation* WhileCondition::getOperation() {
	return asOperation;
}
Block* WhileCondition::getBlock() {
	return thenBlock;
}
const string WhileCondition::writeTree() {
	return writeTree(0);
}
const string WhileCondition::writeTree(const int& indent) {
	string s = "";

	for (int i = 0; i < indent; i++)
		s += "---";

	s += "While:";

	if (asOperation != NULL) s += "\n" + asOperation->writeTree(indent+1);
	if (thenBlock != NULL) s += "\n" + thenBlock->writeTree(indent+1);

	return s;
}
