#include "token.h"
#include "node.h"
#include "scanner.h"
#include "Symbol.h"

class ParserClass {
public:
	ParserClass(ScannerClass * scanner, SymbolTableClass * symbol);
	StartNode * Start();

private:
	TokenClass Match(TokenType expected);
	ProgramNode * Program();
	BlockNode * Block();
	StatementGroupNode * StatementGroup();
	// IfNode * If();
	// WhileNode * While();
	DeclarationStatementNode * DeclarationStatement();
	AssignmentStatementNode * AssignmentStatement();
	CoutStatementNode * CoutStatement();
	/*Added Nodes !! */
	ExpressionNode * Expression();
	ExpressionNode * And();

	ExpressionNode * Relational();
	ExpressionNode * PlusMinus();
	ExpressionNode * TimesDivide();
	ExpressionNode * Not();
	ExpressionNode * Factor();
	IdentifierNode * Identifier();
	IntegerNode * Integer();

	
	ScannerClass * mScanner;
	SymbolTableClass * mSymbol;
};

