class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};


class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};


class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};

class ModulusNode : public BinaryOperatorNode {
public:
	ModulusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};


class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};


class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};


class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};


class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};

class AndNode : public BinaryOperatorNode {
public:
	AndNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};
class OrNode : public BinaryOperatorNode {
public:
	OrNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
};
class NotNode : public ExpressionNode {
public:
	NotNode(ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &instr);
private:
	ExpressionNode * mExpressionNode;
};


/****/


void PlusNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing MinusNode");
}


int MinusNode::Evaluate() {
	int sum = 0;
	sum = mLeft->Evaluate() - mRight->Evaluate();

	return sum;
}
void MinusNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopSubPush();
}
MinusEqualNode::MinusEqualNode(IdentifierNode* left, ExpressionNode * right)
	: AssignmentStatementNode(left, right), mExpressionNode(right), mIdentifierNode(left)
{
	MSG("Initializing MinusEqualNode");
}

void MinusEqualNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(mIdentifierNode->Evaluate() - val);
}
void MinusEqualNode::Code(InstructionsClass &instr) {
	mIdentifierNode->CodeEvaluate(instr);
	mExpressionNode->CodeEvaluate(instr);
	instr.PopPopSubPush();
	std::string exists = mIdentifierNode->GetLabel();
	instr.PopAndStore(mIdentifierNode->GetIndex(exists));
}
PlusEqualNode::PlusEqualNode(IdentifierNode* left, ExpressionNode * right)
	: AssignmentStatementNode(left, right), mExpressionNode(right), mIdentifierNode(left)
{
	MSG("Initializing PlusEqualNode");
}

void PlusEqualNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(mIdentifierNode->Evaluate() + val);
}
void PlusEqualNode::Code(InstructionsClass &instr) {
	mIdentifierNode->CodeEvaluate(instr);
	mExpressionNode->CodeEvaluate(instr);
	instr.PopPopAddPush();
	std::string exists = mIdentifierNode->GetLabel();
	instr.PopAndStore(mIdentifierNode->GetIndex(exists));
}

TimesEqualNode::TimesEqualNode(IdentifierNode* left, ExpressionNode * right)
	: AssignmentStatementNode(left, right), mExpressionNode(right), mIdentifierNode(left)
{
	MSG("Initializing TimesEqualNode");
}

void TimesEqualNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(mIdentifierNode->Evaluate() * val);
}
void TimesEqualNode::Code(InstructionsClass &instr) {
	mIdentifierNode->CodeEvaluate(instr);
	mExpressionNode->CodeEvaluate(instr);
	instr.PopPopMulPush();
	std::string exists = mIdentifierNode->GetLabel();
	instr.PopAndStore(mIdentifierNode->GetIndex(exists));
}
DivideEqualNode::DivideEqualNode(IdentifierNode* left, ExpressionNode * right)
	: AssignmentStatementNode(left, right), mExpressionNode(right), mIdentifierNode(left)
{
	MSG("Initializing DivideEqualNode");
}
void DivideEqualNode::Interpret() {
	int val = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(mIdentifierNode->Evaluate() / val);
}
void DivideEqualNode::Code(InstructionsClass &instr) {
	mIdentifierNode->CodeEvaluate(instr);
	mExpressionNode->CodeEvaluate(instr);
	instr.PopPopDivPush();
	std::string exists = mIdentifierNode->GetLabel();
	instr.PopAndStore(mIdentifierNode->GetIndex(exists));
}
TimesNode::TimesNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing TimesNode");
}
int TimesNode::Evaluate() {
	int sum = 0;
	sum = mLeft->Evaluate() * mRight->Evaluate();
	return sum;
}
void TimesNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopMulPush();
}
DivideNode::DivideNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing DivideNode");
}
int DivideNode::Evaluate() {
	int sum = 0;
	sum = mLeft->Evaluate() / mRight->Evaluate();
	return sum;
}
void DivideNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopDivPush();
}
ModulusNode::ModulusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing ModulusNode");
}

int ModulusNode::Evaluate() {
	int sum = 0;
	sum = mLeft->Evaluate() % mRight->Evaluate();
	return sum;
}

void ModulusNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopModPush();
}

LessNode::LessNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing LessNode");
}


int LessNode::Evaluate() {
	if (mLeft->Evaluate() < mRight->Evaluate()) { return 1; }
	return 0;
}
void LessNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopLessPush();
}
LessEqualNode::LessEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing LessEqualNode");
}


int LessEqualNode::Evaluate() {
	if (mLeft->Evaluate() <= mRight->Evaluate()) { return 1; }

	return 0;
}
void LessEqualNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopLessEqualPush();
}
GreaterNode::GreaterNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing GreaterNode");
}


int GreaterNode::Evaluate() {
	if (mLeft->Evaluate() > mRight->Evaluate()) { return 1; }
	return 0;
}
void GreaterNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopGreaterPush();
}
GreaterEqualNode::GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing GreaterEqualNode");
}


int GreaterEqualNode::Evaluate() {
	if (mLeft->Evaluate() <= mRight->Evaluate()) { return 1; }
	return 0;
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopGreaterEqualPush();
}
EqualNode::EqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing EqualNode");
}


int EqualNode::Evaluate() {
	if (mLeft->Evaluate() == mRight->Evaluate()) { return 1; }
	return 0;
}
void EqualNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopEqualPush();
}
NotEqualNode::NotEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing NotEqualNode");
}


int NotEqualNode::Evaluate() {
	if (mLeft->Evaluate() != mRight->Evaluate()) { return 1; }
	return 0;
}
void NotEqualNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopNotEqualPush();
}
AndNode::AndNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing ANDNode");
}


int AndNode::Evaluate() {
	if (mLeft->Evaluate() && mRight->Evaluate()) { return 1; }
	return 0;
}
void AndNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopAndPush();
}
OrNode::OrNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right)
{
	MSG("Initializing ORNode");
}


int OrNode::Evaluate() {
	if (mLeft->Evaluate() || mRight->Evaluate()) { return 1; }
	return 0;
}
void OrNode::CodeEvaluate(InstructionsClass &instr) {
	mLeft->CodeEvaluate(instr);
	mRight->CodeEvaluate(instr);
	instr.PopPopOrPush();
}