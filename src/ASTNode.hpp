/*
 * ASTNode.h
 *
 *  Created on: 29 June 2022
 *      Author: Clayton
 */

#ifndef ASTNODE_H_
#define ASTNODE_H_

//Libraries:
#include "enumerations.hpp" //TokenType, Case
#include "Token.hpp" //Token

#include <string> //string
#include <iostream> //cout
#include <vector> //vector

#include <iostream> //cout (debugging £)

class ASTNode
{
    public:
        //Constructor:
        ASTNode(ASTNode* inputParent = NULL);

        //Destructor:
        virtual ~ASTNode();

        //Setters:
        void setParent(ASTNode*);

        //Getters:
        ASTNode* getParent();

        virtual const std::string writeTree(const int&);

    protected:
        ASTNode* parent;

    private:
};

class Block: public ASTNode
{
    public:
        //Constructor:
        Block(ASTNode* inputParent = NULL);

        //Destructor:
        ~Block();

        //Setters:
        void setStatement(const int&, ASTNode*);
        void addStatement(ASTNode*);

        //Getters:
        ASTNode* getStatement(const int& ) ;
        const int getNumber();
        const std::string writeTree();
        const std::string writeTree(const int&);

    private:
        std::vector<ASTNode*> statements;
};

class Routine: public ASTNode
{
    public:
        //Constructor:
        Routine(ASTNode* inputParent = NULL, Block* inputBlock = NULL);

        //Destructor:
        ~Routine();

        //Setters:
        void setBlock(Block*);

        //Getters:
        Block* getBlock();
        const std::string writeTree();

    private:
        Block* block;
};

class Argument: public ASTNode
{
    public:
        //Constructor:
        Argument(ASTNode* inputParent = NULL, const Token& inputWord = Token());

        //Destructor:
        ~Argument();

        //Setters:
        void setWord(const Token&);

        //Getters:
        Token getWord();

        const std::string writeTree();
        const std::string writeTree(const int&);

    protected:
        Token word;

    private:
};

class Operation: public Argument
{
    public:
        //Constructor:
        Operation(ASTNode* inputParent = NULL, const Token& inputWord = Token());

        //Destructor:
        ~Operation();

        //Setters:
        void setArgument(Argument*, const int&);

        //Getters:
        Argument* getArgument(const int&);
        const int getNumArg();

        const std::string writeTree();
        const std::string writeTree(const int&);

    protected:
        Argument* arguments[100];
        int MAX;
        int numArg;

    private:
};

class Casting: public Argument
{
    public:
        //Constructor:
        Casting(ASTNode* inputParent = NULL, const Token& inputToken = Token());

        //Destructor:
        ~Casting();

        //Setters:
        void setArgument(Argument*);

        //Getters:
        Argument* getArgument();

        const std::string writeTree();
        const std::string writeTree(const int&);

    protected:
        Argument* argument;

    private:
};

class IfCondition: public ASTNode {
    public:
        //Constructor:
        IfCondition(ASTNode* inputParent = NULL, const Token& inputWord = Token());

        //Destructor:
        ~IfCondition();
        //Setters:
        void setOperation(Operation*);
        void setIfBlock(Block*);
        void setElseBlock(Block*);

        //Getters:
        Operation* getOperation();
        Block* getIfBlock();
        Block* getElseBlock();
        const std::string writeTree();
        const std::string writeTree(const int&);

    private:
        Token word;
        Operation* ifOperation;
        Block* ifBlock;
        Block* elseBlock;
        int MAX;
        int numElse;

};

class WhileCondition: public ASTNode {
    public:
        //Constructor:
        WhileCondition(ASTNode* inputParent = NULL, const Token& inputWord = Token());

        //Destructor:
        ~WhileCondition();

        //Setters:
        void setOperation(Operation*);
        void setBlock(Block*);

        //Getters:
        Operation* getOperation();
        Block* getBlock();
        const std::string writeTree();
        const std::string writeTree(const int&);

    private:
        Token word;
        Operation* asOperation;
        Block* thenBlock;

};

#endif /* ASTNODE_H_ */
