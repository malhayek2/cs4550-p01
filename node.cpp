#include "node.h"



Node::Node(){

}

/**/
ProgramNode::ProgramNode(BlockNode *mBlockNode){
	this->mBlockNode = mBlockNode;
}
ProgramNode::~ProgramNode(){
	delete mBlockNode;
}
/**/
BlockNode::BlockNode(StatementGroupNode *mStatementGroupNode){
	this->mStatementGroupNode = mStatementGroupNode;
}
BlockNode::~BlockNode(){
	delete mStatementGroupNode;
}
/**/
StatementGroupNode::StatementGroupNode(){}
StatementGroupNode::~StatementGroupNode(){
	for (unsigned int i = 0; i > mStatementNodeVector.size(); i++){
		delete mStatementNodeVector[i];
		// mStatementNodeVector.erase(mStatementNodeVector.begin()+i);
	}
}
StatementGroupNode::AddStatment(StatementNode *node){
	mStatementNodeVector.push_back(node);
}
/**/
StatementNod::StatementNod(){

}
StatementNod::~StatementNod(){

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
IntegerNode::~IntegerNode(){

}
int IntegerNode::Evaluate(){
	return this->mInt;
}
/**/
IdentifierNode::IdentifierNode(string mLabel, SymbolTableClass *mSymbolTableClass){
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

PlusNode::Evaluate(){
	return left->Evaluate() + right->Evaluate();
}
