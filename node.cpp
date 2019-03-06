#include "node.h"
#include <iostream>
Node::~Node(){

}

/**/
StartNode::StartNode(ProgramNode *mProgramNode){
	this->mProgramNode = mProgramNode;

}
StartNode::~StartNode(){
	delete mProgramNode;
	std::cout << "StartNode Deleting ProgramNode " << std::endl;

}


/**/
ProgramNode::ProgramNode(BlockNode *mBlockNode){
	this->mBlockNode = mBlockNode;
}
ProgramNode::~ProgramNode(){
	delete mBlockNode;
	std::cout << "ProgramNode Deleting BlockNode " << std::endl;
}
/**/
BlockNode::BlockNode(StatementGroupNode *mStatementGroupNode){
	this->mStatementGroupNode = mStatementGroupNode;
}
BlockNode::~BlockNode(){
	delete mStatementGroupNode;
	std::cout << "BlockNode Deleting StatementGroupNode" << std::endl;	
}
/**/
StatementGroupNode::StatementGroupNode(){}
StatementGroupNode::~StatementGroupNode(){
	for (unsigned int i = 0; i > mStatementNodeVector.size(); i++){
		delete mStatementNodeVector[i];
		std::cout << "StatementGroupNode Deleting StatementNode Index  " << i << std::endl;
		// mStatementNodeVector.erase(mStatementNodeVector.begin()+i);
	}
}
void StatementGroupNode::AddStatement(StatementNode *node){
	mStatementNodeVector.push_back(node);
}
/**/
StatementNode::StatementNode(){

}
StatementNode::~StatementNode(){

}
/**/
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *mIdentifierNode){
	this->mIdentifierNode = mIdentifierNode;
}
DeclarationStatementNode::~DeclarationStatementNode(){
	// delete mIdentifierNode;
}
/**/
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode){
	this->mIdentifierNode = mIdentifierNode;
	this->mExpressionNode = mExpressionNode;
}
AssignmentStatementNode::~AssignmentStatementNode(){
	// delete mExpressionNode;
	// delete mIdentifierNode;
}

CoutStatementNode::CoutStatementNode(ExpressionNode *mExpressionNode){
	this->mExpressionNode = mExpressionNode;
}
CoutStatementNode::~CoutStatementNode(){
	// delete CoutStatementNode;
}


/*ExpressionNode !! */
ExpressionNode::ExpressionNode(){

}
ExpressionNode::~ExpressionNode(){

}
int ExpressionNode::Evaluate(){
	return this->mInt;
}

/**/
IntegerNode::IntegerNode(int mInt){
	this->mInt = mInt;
}
// IntegerNode::~IntegerNode(){

// }
int IntegerNode::Evaluate(){
	return this->mInt;
}
/**/
IdentifierNode::IdentifierNode(std::string mLabel, SymbolTableClass *mSymbolTableClass){
	this->mLabel = mLabel;
	this->mSymbolTableClass = mSymbolTableClass;
}
IdentifierNode::~IdentifierNode(){


}
void IdentifierNode::SetValue(int value){
	mSymbolTableClass->SetValue(this->mLabel, value);
}
void IdentifierNode::DeclareVariable(){
	mSymbolTableClass->AddEntry(this->mLabel);
}
int IdentifierNode::Evaluate(){
	return mSymbolTableClass->GetValue(mLabel);
	// return 0;
}
int IdentifierNode::GetIndex(){
	return mSymbolTableClass->GetIndex(this->mLabel);
}
/**/
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right){
	this->left = left;
	this->right = right;	
}

BinaryOperatorNode::~BinaryOperatorNode(){

}
/**/
PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
: BinaryOperatorNode(left, right)
{
}

int PlusNode::Evaluate(){
	return (left->Evaluate() + right->Evaluate());
}
PlusNode::~PlusNode(){
	//Nothing really
}
