#ifndef NODE 
#define NODE
#include <vector>
#include "Symbol.h"
#include <string>
class Node;
class StartNode;
class BlockNode;
class ProgramNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;


class Node{
public:
	virtual ~Node();

private:
};
/**/
class StatementNode : public Node{
public:
	virtual ~StatementNode();
	StatementNode();
};
/*add statments push_back to the vector */
/*destuctor should loop and delete every node*/
class StatementGroupNode : public Node{
public:
	virtual ~StatementGroupNode();
	StatementGroupNode();
	void AddStatement(StatementNode *node);
private:
std::vector <StatementNode *> mStatementNodeVector;
};
/**/
class BlockNode: public Node{
public:
	virtual ~BlockNode();
	BlockNode(StatementGroupNode *mStatementGroupNode);
private:
	StatementGroupNode *mStatementGroupNode;
};
/**/
class ProgramNode : public Node{
public:
	virtual ~ProgramNode();
	ProgramNode(BlockNode *mBlockNode);
private:
	BlockNode  *mBlockNode;
};
/*Store the mProgramNode into the private variable.*/
/*destrcutor must call delete on that pointer*/
class StartNode : public Node{
public:
	StartNode(ProgramNode *mProgramNode);
	virtual ~StartNode();
	
private:
	ProgramNode *mProgramNode; 
};
/**/
class ExpressionNode{
public:
	ExpressionNode();
	virtual ~ExpressionNode();
	virtual int Evaluate();
private:
	int mInt;
};
/**/
class IdentifierNode: public ExpressionNode{
public:
	virtual ~IdentifierNode();
	IdentifierNode(std::string mLabel, SymbolTableClass *mSymbolTableClass);
	/*which adds the IdentifierNode’s label to the symbol table.*/
	void DeclareVariable();
	/*which sets the value into the symbol table by calling something like mSymbolTable→SetValue(mLabel, v).*/
	void SetValue(int v);
	/*which returns the integer position of where this variable is being stored in the symbol table.*/
	int GetIndex();

	virtual int Evaluate();
private:
	std::string mLabel;
	SymbolTableClass *mSymbolTableClass;

};
/*Store the value.*/
class DeclarationStatementNode: public StatementNode{
public:
	virtual ~DeclarationStatementNode();
	DeclarationStatementNode(IdentifierNode *mIdentifierNode);

private:
	IdentifierNode *mIdentifierNode;
};


class AssignmentStatementNode : public StatementNode{
public:
	virtual ~AssignmentStatementNode();
	AssignmentStatementNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
private:
	ExpressionNode *mExpressionNode;
	IdentifierNode *mIdentifierNode;

};

class CoutStatementNode : public StatementNode{
public: 
	virtual ~CoutStatementNode();
	CoutStatementNode(ExpressionNode *mExpressionNode);
private:
	ExpressionNode *mExpressionNode;
};
/*NOT DIREVED from Node*/

/*Evaluate Method Should return the stored integer */
class IntegerNode : public ExpressionNode{
public:
	//virtual ~IntegerNode();
	IntegerNode(int mInt);
	virtual int Evaluate();
private:
	int mInt;
};



class BinaryOperatorNode : public ExpressionNode{
public:
	virtual ~BinaryOperatorNode();
	BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
	// virtual int Evaluate();
protected:
	ExpressionNode *left;
	ExpressionNode *right;
};

/* the cpnstuctor
PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right)
{
}
*/
class PlusNode : public BinaryOperatorNode{
public:
	virtual ~PlusNode();
	PlusNode(ExpressionNode *left, ExpressionNode *right);
	virtual int Evaluate();
private:
	/// NOTHING!!!
};



class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	
private:
};


class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};


class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};


class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};


class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	
private:
};


class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};


class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};
/**/

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();

private:
};

// class AndNode : public BinaryOperatorNode {
// public:
// 	AndNode(ExpressionNode * left, ExpressionNode * right);
// 	int Evaluate();
// 	void CodeEvaluate(InstructionsClass &instr);
// private:
// };
// class OrNode : public BinaryOperatorNode {
// public:
// 	OrNode(ExpressionNode * left, ExpressionNode * right);
// 	int Evaluate();
// 	void CodeEvaluate(InstructionsClass &instr);
// private:
// };
// class NotNode : public ExpressionNode {
// public:
// 	NotNode(ExpressionNode * right);
// 	int Evaluate();
// 	void CodeEvaluate(InstructionsClass &instr);
// private:
// 	ExpressionNode * mExpressionNode;
// };


#endif // NODE