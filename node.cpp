#include "node.h"
#include "debug.h"
#include <iostream>
Node::~Node(){

}
/*those methods are overriden by child nodes*/
void Node::Interpret(){}
void Node::Code(InstructionsClass &instr){}

/**/
StartNode::StartNode(ProgramNode *mProgramNode){
	this->mProgramNode = mProgramNode;

}
StartNode::~StartNode(){
	delete mProgramNode;
	std::cout << "StartNode Deleting ProgramNode " << std::endl;

}
void StartNode::Interpret(){mProgramNode->Interpret();}
void StartNode::Code(InstructionsClass &instr)
{ 
	mProgramNode->Code(instr);
}
/**/
ProgramNode::ProgramNode(BlockNode *mBlockNode){
	this->mBlockNode = mBlockNode;
}
ProgramNode::~ProgramNode(){
	delete mBlockNode;
	std::cout << "ProgramNode Deleting BlockNode " << std::endl;
}
void ProgramNode::Interpret(){mBlockNode->Interpret();}
void ProgramNode::Code(InstructionsClass &instr) { mBlockNode->Code(instr); }
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

void BlockNode::Code(InstructionsClass &instr) { 
	// mSymbolTable->PushScope();
	mStatementGroupNode->Code(instr); 
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
void StatementGroupNode::Code(InstructionsClass &instr) {
	for (unsigned int i = 0; i < mStatementNodeVector.size(); i++) {
		mStatementNodeVector[i]->Code(instr);
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
void StatementNode::Code(InstructionsClass &instr){

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
void  DeclarationStatementNode::Code(InstructionsClass& instr) {
	mIdentifierNode->DeclareVariable();
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
void AssignmentStatementNode::Interpret()
{
	int id = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(id);
}
void AssignmentStatementNode::Code(InstructionsClass &instr){
	mExpressionNode->CodeEvaluate(instr);
	int index=mIdentifierNode->GetIndex();
	/*replicate the position in the sybmoltable into our mCode Array*/
	instr.PopAndStore(index);
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

		if(!(mExpressionNodeVec[i]==NULL)) {
			
			std::cout<<mExpressionNodeVec[i]->Evaluate() <<  std::endl;
			// continue;
		}
		else {std::cout<<"";}
	}
	
	// std::cout << mExpressionNode->Evaluate() << std::endl;

}
void CoutStatementNode::addExpression(ExpressionNode *e){
	mExpressionNodeVec.push_back(e);
}

/*You might want to add a helper funtion to add Expression into one for cout << 1 << 1 */
/*debug this */
void CoutStatementNode::Code(InstructionsClass &instr) {
	for (unsigned int i = 0; i < mExpressionNodeVec.size(); i++) {
		if (mExpressionNodeVec[i] == NULL) {
			instr.WriteEndl();
			continue;
		}else{
			mExpressionNodeVec[i]->CodeEvaluate(instr);
			instr.PopAndWrite();
		}
		/*TESTING*/
		//std::cout <<  "mExpressionNodeVec" << i << "Value " << mExpressionNodeVec[i]->mInt << std::endl;
		//std::cout << val;
	}
}
/*ExpressionNode !! */
ExpressionNode::ExpressionNode(){

}
ExpressionNode::~ExpressionNode(){

}
int ExpressionNode::Evaluate(){
	return this->mInt;
}
int const combine(int a, int b) {
   int times = 1;
   while (times <= b)
      times *= 10;
   	
   std::cout << "done combine" << std::endl;

   return a*times + b;

}
// void ExpressionNode::setmInt(int x) const {
// 	std::cout << "setting" <<std::endl;
// 	if(x !=NULL){
// 		this->mInt=x;	
// 	}
	
// 	std::cout << "done setting " << std::endl;
// }
void ExpressionNode::incExpression(ExpressionNode *en2){
	//std::cout << "incExpression" << std::endl;
	int first = this->Evaluate();
	int second = en2->Evaluate();
	// std::cout << "Got evaluete value  " << first << second << std::endl;
	ExpressionNode newEN0 = ExpressionNode();
	// ExpressionNode *newEN = &newEN0;
	//newEN0.mInt = combine(first,second);
	en2->mInt = combine(first,second);
	std::cout << "HEEEERRRREEEEEEEEEEEEEEEEEEEEEEEE  done incExpression :" << en2->Evaluate() << "Combine result :" << combine(first,second) << std::endl;
	//return newEN0;
}
void ExpressionNode::CodeEvaluate(InstructionsClass &instr){
	/*nothing*/
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

void IntegerNode::CodeEvaluate(InstructionsClass &instr) { 
	instr.PushValue(this->mInt);
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

void IdentifierNode::CodeEvaluate(InstructionsClass &instr) { 
	int index=mSymbolTableClass->GetIndex(this->mLabel);
	instr.PushVariable(index);
}
/**/
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right){
	this->left = left;
	this->right = right;	
}

BinaryOperatorNode::~BinaryOperatorNode(){

}
void BinaryOperatorNode::CodeEvaluate(InstructionsClass &instr){

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
void PlusNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopAddPush();
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
void MinusNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopSubPush();
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

void TimesNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopMulPush();
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
void DivideNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopDivPush();
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
void LessNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopLessPush();
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
void LessEqualNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopLessEqualPush();
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
void GreaterNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopGreaterPush();
}
/**/
GreaterEqualNode::GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	// MSG("Initializing GreaterEqualNode");
}


int GreaterEqualNode::Evaluate() {
	if (left->Evaluate() <= right->Evaluate()) { return 1; }
	return 0;
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopGreaterEqualPush();
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
void EqualNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopEqualPush();
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

void NotEqualNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopNotEqualPush();
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
void OrNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopOrPush();
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
void AndNode::CodeEvaluate(InstructionsClass &instr) {
	left->CodeEvaluate(instr);
	right->CodeEvaluate(instr);
	instr.PopPopAndPush();
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
void NotNode::CodeEvaluate(InstructionsClass &instr) {
	mExpressionNode->CodeEvaluate(instr);
	mExpressionNode->CodeEvaluate(instr);
	//somehow find out whats on stack and switch the boolean
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
void IfStatementNode::Code(InstructionsClass &instr)
{
	MSG("Coded IfStatmentNode");
	mExpressionNode->CodeEvaluate(instr);
	unsigned char *InsertAddress=instr.SkipIfZeroStack();
	unsigned char *FromAddress=instr.GetAddress();
	
	if(!this->isElse){this->mStatementNode->Code(instr);}
	else if(this->isElse)
	{
		if(this->mExpressionNode->Evaluate()!=0) 
		{
			this->mStatementNode->Code(instr);
		}
		else
		{
			this->mStatementNodeElse->Code(instr);
		}
	}

	unsigned char *ToAddress=instr.GetAddress();
	instr.SetOffset(InsertAddress,ToAddress-FromAddress);
}
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
void WhileStatementNode::Code(InstructionsClass &instr)
{
	MSG("Coded WhileStatmentNode");
	unsigned char *Address0=instr.GetAddress();
	mExpressionNode->CodeEvaluate(instr);
	unsigned char *Offset1=instr.SkipIfZeroStack();
	unsigned char *Address1=instr.GetAddress();
	mStatementNode->Code(instr);
	unsigned char *Offset2=instr.Jump();
	unsigned char *Address2=instr.GetAddress();
	
	instr.SetOffset(Offset2,(Address0-Address2));//return to begining
	instr.SetOffset(Offset1,(Address2-Address1));//while loop has ended
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


void RepeatStatementNode::Code(InstructionsClass &instr)
{
	MSG("Coded RepeatStatementNode");
	unsigned char *Address0=instr.GetAddress();
	mExpressionNode->CodeEvaluate(instr);
	unsigned char *Offset1=instr.SkipIfZeroStack();
	unsigned char *Address1=instr.GetAddress();
	mStatementNode->Code(instr);
	unsigned char *Offset2=instr.Jump();
	unsigned char *Address2=instr.GetAddress();
	
	instr.SetOffset(Offset2,(Address0-Address2));//return to begining
	instr.SetOffset(Offset1,(Address2-Address1));//while loop has ended
}

