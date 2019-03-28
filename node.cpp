#include "node.h"
#include "debug.h"
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
	std::cout << "deleting IdentifierNode" << std::endl; 
	delete mIdentifierNode;
}
/**/
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *mIdentifierNode, ExpressionNode *mExpressionNode){
	this->mIdentifierNode = mIdentifierNode;
	this->mExpressionNode = mExpressionNode;
}
AssignmentStatementNode::~AssignmentStatementNode(){
	std::cout << "deleting ExpressionNode && IdentifierNode" << std::endl; 
	delete mExpressionNode;
	delete mIdentifierNode;
}

CoutStatementNode::CoutStatementNode(ExpressionNode *mExpressionNode){
	this->mExpressionNode = mExpressionNode;
}
CoutStatementNode::~CoutStatementNode(){
	std::cout << "Deleting  ExpressionNode " << std::endl; 
	delete mExpressionNode;
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
/*The remaning Binary Operators*/

MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing MinusNode");
}

int MinusNode::Evaluate() {

	return( left->Evaluate() - right->Evaluate());


}
/**/
TimesNode::TimesNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing TimesNode");
}
int TimesNode::Evaluate() {
	
	return (left->Evaluate() * right->Evaluate());
	
}
/**/
DivideNode::DivideNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing DivideNode");
}
int DivideNode::Evaluate() {

	 return (left->Evaluate() / right->Evaluate());

}
/**/
LessNode::LessNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing LessNode");
}


int LessNode::Evaluate() {
	if (left->Evaluate() < right->Evaluate()) { return 1; }
	return 0;
}
/**/
LessEqualNode::LessEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing LessEqualNode");
}


int LessEqualNode::Evaluate() {
	if (left->Evaluate() <= right->Evaluate()) { return 1; }

	return 0;
}
/**/
GreaterNode::GreaterNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing GreaterNode");
}

/**/
int GreaterNode::Evaluate() {
	if (left->Evaluate() > right->Evaluate()) { return 1; }
	return 0;
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing GreaterEqualNode");
}


int GreaterEqualNode::Evaluate() {
	if (left->Evaluate() <= right->Evaluate()) { return 1; }
	return 0;
}
/**/
EqualNode::EqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing EqualNode");
}


int EqualNode::Evaluate() {
	if (left->Evaluate() == right->Evaluate()) { return 1; }
	return 0;
}
/**/
NotEqualNode::NotEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing NotEqualNode");
}


int NotEqualNode::Evaluate() {
	if (left->Evaluate() != right->Evaluate()) { return 1; }
	return 0;
}



/**added Nodes for  parser**/



//OR NODE
OrNode::OrNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left, right)
{
	MSG("Or node initialized.");
}

OrNode::~OrNode() { 
	MSG("Or node destroyed.");
}

int OrNode::Evaluate() {
	int res = left->Evaluate() || right->Evaluate();
	MSG("NotEqual node evaluated to " << res);
	return res;
}


//AND NODE
AndNode::AndNode(ExpressionNode *left, ExpressionNode *right)
	: BinaryOperatorNode(left, right)
{
	MSG("NotEqual node initialized.");
}

AndNode::~AndNode() {
	MSG("NotEqual node destroyed.");
}

int AndNode::Evaluate() {
	int res = left->Evaluate() && right->Evaluate();
	MSG("NotEqual node evaluated to " << res);
	return res;
}








NotNode::NotNode(ExpressionNode *exp)
{
	this->mExpressionNode = exp;
	MSG("Not node initialized.");
}
	
NotNode::~NotNode() {
	delete this->mExpressionNode;
	MSG("Plus node destroyed.");
}

int NotNode::Evaluate() {
	int res = mExpressionNode->Evaluate();
	if(res) {
		return 0;
	}
	else {
		return 1;
	}
	MSG("Not node evaluated as " << res);
}

// 

