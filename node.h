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
class OrNode;
class AndNode;
class NotNode;

class IfStatementNode;
class WhileStatementNode;
class RepeatStatementNode;





class Node{
public:
	virtual ~Node();
	virtual void Interpret();
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
	virtual void Interpret();
	void AddStatement(StatementNode *node);
private:
std::vector <StatementNode *> mStatementNodeVector;
};
/**/
class BlockNode: public StatementNode{
public:
	virtual ~BlockNode();
	virtual void Interpret();
	BlockNode(StatementGroupNode *mStatementGroupNode);
private:
	StatementGroupNode *mStatementGroupNode;
	SymbolTableClass *mSymbolTable;
};
/**/
class ProgramNode : public Node{
public:
	virtual ~ProgramNode();
	virtual void Interpret();
	ProgramNode(BlockNode *mBlockNode);
private:
	BlockNode  *mBlockNode;
};
/*Store the mProgramNode into the private variable.*/
/*destrcutor must call delete on that pointer*/
class StartNode : public Node{
public:
	StartNode(ProgramNode *mProgramNode);
	virtual void Interpret();
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
	// virtual int Evaluate();
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
	virtual void Interpret();

private:
	IdentifierNode *mIdentifierNode;
};


class AssignmentStatementNode : public StatementNode{
public:
	virtual ~AssignmentStatementNode();
	AssignmentStatementNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode);
	virtual void Interpret();
private:
	ExpressionNode *mExpressionNode;
	IdentifierNode *mIdentifierNode;

};

class CoutStatementNode : public StatementNode{
public: 
	virtual ~CoutStatementNode();
	CoutStatementNode();
	CoutStatementNode(ExpressionNode *mExpressionNode);
	virtual void Interpret();
	void addExpression(ExpressionNode *);
private:
	ExpressionNode *mExpressionNode;
	std::vector<ExpressionNode *> mExpressionNodeVec;
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

class AndNode : public BinaryOperatorNode {
public:
	AndNode(ExpressionNode * left, ExpressionNode * right);
	virtual ~AndNode();
	int Evaluate();
	// void CodeEvaluate(InstructionsClass &instr);
private:
};
class OrNode : public BinaryOperatorNode {
public:
	OrNode(ExpressionNode * left, ExpressionNode * right);
	virtual ~OrNode();
	int Evaluate();
	// void CodeEvaluate(InstructionsClass &instr);
private:
};
class NotNode : public ExpressionNode {
public:
	NotNode(ExpressionNode * right);
	virtual ~NotNode();
	int Evaluate();
	// void CodeEvaluate(InstructionsClass &instr);
private:
	ExpressionNode * mExpressionNode;
};

/*added if and while Statements */

class IfStatementNode: public StatementNode{
public:
	IfStatementNode(ExpressionNode *enode, StatementNode *snode);
	virtual ~IfStatementNode();
	virtual void Interpret();
	// virtual void Code(InstructionsClass &machinecode);
	void SetElse();
	bool GetElse();
	void SetElseNode(StatementNode *snode);

private:
	ExpressionNode *mExpressionNode;
	StatementNode *mStatementNode;
	StatementNode *mStatementNodeElse;
	bool isElse;
};
class WhileStatementNode: public StatementNode{
public:
	WhileStatementNode(ExpressionNode *enode, StatementNode *snode);
	virtual ~WhileStatementNode();
	virtual void Interpret();
	// virtual void Code(InstructionsClass &machinecode);
private:
	ExpressionNode *mExpressionNode;
	StatementNode *mStatementNode;
};

class RepeatStatementNode: public StatementNode{
public:
	RepeatStatementNode(ExpressionNode *enode, StatementNode *snode);
	virtual ~RepeatStatementNode();
	virtual void Interpret();
private:
	
	ExpressionNode *mExpressionNode;
	StatementNode *mStatementNode;
};
#endif // NODE