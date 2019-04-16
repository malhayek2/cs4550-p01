#include "node.h"
#include "debug.h"
#include <iostream>
Node::~Node(){

}
void Node::Interpret(){}
/**/
StartNode::StartNode(ProgramNode *mProgramNode){
	this->mProgramNode = mProgramNode;

}
StartNode::~StartNode(){
	delete mProgramNode;
	std::cout << "StartNode Deleting ProgramNode " << std::endl;

}
void StartNode::Interpret(){mProgramNode->Interpret();}

/**/
ProgramNode::ProgramNode(BlockNode *mBlockNode){
	this->mBlockNode = mBlockNode;
}
ProgramNode::~ProgramNode(){
	delete mBlockNode;
	std::cout << "ProgramNode Deleting BlockNode " << std::endl;
}
void ProgramNode::Interpret(){mBlockNode->Interpret();}
/**/
BlockNode::BlockNode(StatementGroupNode *mStatementGroupNode){
	this->mStatementGroupNode = mStatementGroupNode;
}
BlockNode::~BlockNode(){
	delete mStatementGroupNode;
	std::cout << "BlockNode Deleting StatementGroupNode" << std::endl;	 
}

void BlockNode::Interpret()
{
	// mSymbolTable->PushScope();
	mStatementGroupNode->Interpret();
	// mSymbolTable->PopScope();
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

void StatementGroupNode::Interpret()
{
	for(unsigned int i=0;i<mStatementNodeVector.size();i++)
	{
		mStatementNodeVector[i]->Interpret();
		//StatementNode *sm=mStatementNodeVector.at(i);
		//->Interpret();
	}
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

void DeclarationStatementNode::Interpret(){mIdentifierNode->DeclareVariable();};
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
void AssignmentStatementNode::Interpret()
{
	int id = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(id);
}
/**/
CoutStatementNode::CoutStatementNode(){}
CoutStatementNode::CoutStatementNode(ExpressionNode *mExpressionNode){
	this->mExpressionNode = mExpressionNode;
}
CoutStatementNode::~CoutStatementNode(){
	std::cout << "Deleting  ExpressionNode " << std::endl; 
	delete mExpressionNode;
}
void CoutStatementNode::Interpret()
{
	for(unsigned int i=0;i<mExpressionNodeVec.size();i++)
	{
		if(!(mExpressionNodeVec.at(i)==NULL)) {
			std::cout<<mExpressionNodeVec.at(i)->Evaluate();
		}
		else {std::cout<<""<<std::endl;}
	}
	// std::cout << mExpressionNode->Evaluate() << std::endl;

}
void CoutStatementNode::addExpression(ExpressionNode *e){
	mExpressionNodeVec.push_back(e);
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

/*if & while repeat*/


IfStatementNode::IfStatementNode(ExpressionNode *enode, StatementNode *snode)
{
	this->mExpressionNode=enode;
	this->mStatementNode=snode;
	this->isElse=false;
}
IfStatementNode::~IfStatementNode()
{
	delete mExpressionNode;
	delete mStatementNode;
	MSG("IfStatementNode Deleted");
}
void IfStatementNode::Interpret() 
{ 
	if(this->mExpressionNode->Evaluate()!=0) 
	{ 
		this->mStatementNode->Interpret(); 
	}
	else if(this->mExpressionNode->Evaluate()==0) 
	{
		if(isElse)
		{
			this->mStatementNodeElse->Interpret();
		}
	}
}
// void IfStatementNode::Code(InstructionsClass &machinecode)
// {
// 	NCMSG("Coded IfStatmentNode");
// 	mExpressionNode->Code(machinecode);
// 	unsigned char *InsertAddress=machinecode.SkipIfZeroStack();
// 	unsigned char *FromAddress=machinecode.GetAddress();
	
// 	if(!this->isElse){this->mStatementNode->Code(machinecode);}
// 	else if(this->isElse)
// 	{
// 		if(this->mExpressionNode->Evaluate()!=0) 
// 		{
// 			this->mStatementNode->Code(machinecode);
// 		}
// 		else
// 		{
// 			this->mStatementNodeElse->Code(machinecode);
// 		}
// 	}

// 	unsigned char *ToAddress=machinecode.GetAddress();
// 	machinecode.SetOffset(InsertAddress,ToAddress-FromAddress);
// }
void IfStatementNode::SetElse(){this->isElse=true;}
bool IfStatementNode::GetElse(){return this->isElse;}
void IfStatementNode::SetElseNode(StatementNode *snode){this->mStatementNodeElse=snode;}

WhileStatementNode::WhileStatementNode(ExpressionNode *enode, StatementNode *snode)
{
	this->mExpressionNode=enode;
	this->mStatementNode=snode;
}
WhileStatementNode::~WhileStatementNode()
{
	delete mExpressionNode;
	delete mStatementNode;
	MSG("WhileStatementNode Deleted");
}
void WhileStatementNode::Interpret()
{
	while(this->mExpressionNode->Evaluate()!=0)
	{
		this->mStatementNode->Interpret();
	}
}





/****REPEAT STATMENT!****/

RepeatStatementNode::RepeatStatementNode(ExpressionNode *enode, StatementNode *snode)
{
	
	this->mExpressionNode=enode;
	this->mStatementNode=snode;
	MSG("initialized RepeatStatementNode");
}
RepeatStatementNode::~RepeatStatementNode()
{
	delete mExpressionNode;
	delete mStatementNode;
	MSG("RepeatStatementNode Deleted");
}
void RepeatStatementNode::Interpret()
{
	/*expression evaluted return an integer should be stored*/
	int expression = this->mExpressionNode->Evaluate();
	MSG("expression is" << expression);
	for (int i = 0; i < expression; i++) {
		MSG("Doing forloop : " << i);
		this->mStatementNode->Interpret();

	}
	MSG("Finihsed forloop");
}


