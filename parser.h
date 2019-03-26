#pragma once

#include "token.h"
#include "scanner.h"
#include "symbol.h"
#include "node.h"

class ParserClass
{
public:
	ParserClass(ScannerClass *sc, SymbolTableClass *stc);
	~ParserClass();
	StartNode* Start();
	SymbolTableClass *getSymbolTable();

private:
	TokenClass Match(TokenType expectedType);

	StatementGroupNode *StatementGroup();

	ExpressionNode *Term();
	ExpressionNode *Expression();
	ExpressionNode *Side();
	ExpressionNode *Factor();
	ExpressionNode *Relational();
	ExpressionNode *And();
	ExpressionNode *Or();

	BooleanNode *Boolean();
	IdentifierNode *Identifier();
	IntegerNode *Integer();

	ProgramNode *Program();

	BlockNode *Block();
	BlockNode *Blockwords();

	StatementNode *Statement();
	IfStatementNode *IfStatement();
	WhileStatementNode *WhileStatement();

	DeclarationStatementNode *DeclarationStatement();
	AssignmentStatementNode *AssignmentStatement();
	CoutStatementNode *CoutStatement();

	ScannerClass *mScanner;
	SymbolTableClass *mSymbolTable;
};