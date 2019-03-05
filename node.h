#ifndef NODE 
#define NODE
#import <vector>
#import "Symbol.h"

class Node{
public:
	virtual ~Node();
	Node();

private:
};
/*Store the mProgramNode into the private variable.*/
/*destrcutor must call delete on that pointer*/
class StartNode : public Node{
public:
	virtual ~StartNode();
	StartNode(ProgramNode *mProgramNode);
private:
	ProgramNode mProgramNode; 
};
/*Store the value.*/
class ProgramNode : public Node{
public:
	virtual ~ProgramNode();
	ProgramNode(BlockNode *mBlockNode);
private:
	BlockNode  mBlockNode;
}

class BlockNode: public Node{
public:
	virtual ~BlockNode();
	BlockNode(StatementGroupNode *mStatementGroupNode);
private:
	StatementGroupNode mStatementGroupNode;
};
/*add statments push_back to the vector */
/*destuctor should loop and delete every node*/
class StatementGroupNode : public Node{
public:
	virtual ~StatementGroupNode();
	StatementGroupNode();
	void AddStatement(StatementNode *node);
private:
vector <StatementNode *> mStatementNodeVector;
};

class StatementNode : public Node{
public:
	virtual ~StatementNode();
	StatementNode();
};

class DeclarationStatementNode: StatementNode{
public:
	virtual ~DeclarationStatementNode();
	DeclarationStatementNode(IdentifierNode *mIdentifierNode);

private:
	IdentifierNode mIdentifierNode;
};


class AssignmentStatementNode : StatementNode{
public:
	virtual ~AssignmentStatementNode();
	AssignmentStatementNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
private:
	ExpressionNode mExpressionNode;
	IdentifierNode mIdentifierNode;

};

class CoutStatementNode : StatementNode{
public: 
	virtual ~CoutStatementNode();
	CoutStatementNode(ExpressionNode *mExpressionNode);
private:
	ExpressionNode mExpressionNode;
};
/*NOT DIREVED from Node*/
class ExpressionNode{
public:
	ExpressionNode();
	virtual ~ExpressionNode();
	virtual int Evaluate();
private:
	int mInt;
};
/*Evaluate Method Should return the stored integer */
class IntegerNode : ExpressionNode{
public:
	//virtual ~IntegerNode();
	IntegerNode(int mInt);
	virtual int Evaluate();
private:
	int mInt;
};

class IdentifierNode : ExpressionNode{
public:
	virtual ~IdentifierNode();
	IdentifierNode(string mLabel, SymbolTableClass *mSymbolTableClass);
	/*which adds the IdentifierNode’s label to the symbol table.*/
	void DeclareVariable();
	/*which sets the value into the symbol table by calling something like mSymbolTable→SetValue(mLabel, v).*/
	void SetValue(int v);
	/*which returns the integer position of where this variable is being stored in the symbol table.*/
	int GetIndex();
	virtual int Evaluate();
private:
	string mLabel;
	SymbolTableClass *mSymbolTableClass

};

class BinaryOperatorNode : ExpressionNode{
public:
	virtual ~BinaryOperatorNode();
	BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
	// virtual int Evaluate();
protected:
	ExpressionNode left;
	ExpressionNode right;
};

/* the cpnstuctor
PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right)
{
}
*/
class PlusNode : BinaryOperatorNode{
public:
	virtual ~PlusNode();
	PlusNode(ExpressionNode *left, ExpressionNode *right);
	virtual int Evaluate();
private:
	/// NOTHING!!!
};



#endif // NODE