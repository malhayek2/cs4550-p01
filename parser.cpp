#include "parser.h"
#include "debug.h"

/*debugging*/
const string ggTokenTypeNames[] = 
{
	"VOID", "MAIN", "INT", "COUT", "IF", "ELSE", "WHILE", "BOOL", "TRUE", "FALSE", "REPEAT",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOT","NOTEQUAL","NEGATE",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE","PLUSEQUAL","MINUSEQUAL","TIMESEQUAL", "DIVIDEEQUAL", "MOD"
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY","OR","AND",
	"BEGIN","END","IDENTIFIER", "INTEGER", "BAD", "ENDFILE","ENDL", "DO"
};




ParserClass::ParserClass(ScannerClass * scanner, SymbolTableClass * symbol) {
	this->mScanner = scanner;
	this->mSymbol = symbol;
}

TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mScanner->GetNextToken();
	std::cout << "ExpectedType Name " << ggTokenTypeNames[expectedType] << std::endl;
	std::cout << "Read Token" <<  currentToken.GetTokenTypeName() << std::endl;
	if(currentToken.GetTokenType() != expectedType)

	{
		cerr << "Error in ParserClass::Match. " << endl;
		cerr << "Expected token type " << 
			expectedType << 
			", but got type " << currentToken.GetTokenTypeName() << endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " << 
		currentToken.GetTokenTypeName() << ". Lexeme: \"" << 
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}

StartNode * ParserClass::Start() {
	MSG("StartNode Start()");
	ProgramNode *p = Program();
	Match(ENDFILE_TOKEN);
	StartNode *s = new StartNode(p);
	return s;
}

ProgramNode * ParserClass::Program() {
	MSG("ProgramNode Program()");
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode *b = Block();
	ProgramNode *p = new ProgramNode(b);
	return p;
}

BlockNode * ParserClass::Block() {
	MSG("BlockNode Block()");
	Match(LCURLY_TOKEN);
	/*then recursively calls the
	 	ParserClass::StatementGroup() method, then insists on matching an
	RCURLY_TOKEN, then returns.*/
	StatementGroupNode * sg = StatementGroup();



	Match(RCURLY_TOKEN);
	BlockNode *b = new BlockNode(sg);
	return b;
}



StatementGroupNode * ParserClass::StatementGroup() { 
	MSG("StatementGroupNode StatementGroup()");
/*ParserClass::StatementGroup(), call the Statement() method over and over in a
while loop until it returns NULL.*/
	auto statementGroupNode = new StatementGroupNode();

    while (true) {
        auto statement = Statement();
        if (!statement) { break; }
        statementGroupNode->AddStatement(statement);
    }
return statementGroupNode;
}


StatementNode *ParserClass::Statement() {
	/*ParserClass::Statement() method needs to “peek” at the next token that will
be coming from the scanner to decide what to do next. We are currently
supporting only three kinds of statements – DeclarationStatements,
AssignmentStatements, and CoutStatements. They begin with INT_TOKEN,
IDENTIFIER_TOKEN, and COUT_TOKEN tokens respectively. If the next token
is one of those three, the corresponding method is recursively called, and the
return value should be “true” (eventually a node pointer). If*/
	MSG("StatementNode Statement()");
    auto token = mScanner->PeekNextToken().GetTokenType();
    
    switch (token) {

        case INT_TOKEN:
            return DeclarationStatement();
        case IDENTIFIER_TOKEN:
            return AssignmentStatement();
        case COUT_TOKEN:
        	//cout << "read COUT"
            return CoutStatement();
        case WHILE_TOKEN:
        	return While();
    	case IF_TOKEN:
    		return If();
		case LCURLY_TOKEN:
			return Block();
		/*in case of a Repeat token*/
		case REPEAT_TOKEN:
			return Repeat();
		/*Added Do While*/
		case DO_TOKEN:
			return DoWHILE();
        default:
        	cout << "went default";
            return NULL;
    }
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
	MSG("DeclarationStatementNode DeclarationStatement()");
	Match(INT_TOKEN);
	IdentifierNode *id = Identifier();
	//IdentifierNode *id = new IdentifierNode("test",mSymbol);		//change from 'test' and delete gettokens later
	//mScanner->GetNextToken();
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode *ds = new DeclarationStatementNode(id);
	return ds;
}

CoutStatementNode * ParserClass::CoutStatement() {
	MSG("CoutStatementNode  CoutStatement()");
	// Match(COUT_TOKEN);
	// Match(INSERTION_TOKEN);
	// ExpressionNode *exp = Expression();
	// Match(SEMICOLON_TOKEN);

	// CoutStatementNode *cs = new CoutStatementNode(exp);
	// return cs;

	CoutStatementNode *c=new CoutStatementNode();
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	if(mScanner->PeekNextToken().GetTokenType()==ENDL_TOKEN)
	{
		Match(ENDL_TOKEN);
		c->addExpression(NULL);
	}
	else
	{
		ExpressionNode *e=Expression();
		c->addExpression(e);
	}
	/*While reading more << */
	while(mScanner->PeekNextToken().GetTokenType()!=SEMICOLON_TOKEN)
	{	
		Match(INSERTION_TOKEN);

		if(mScanner->PeekNextToken().GetTokenType()==ENDL_TOKEN)
		{
			Match(ENDL_TOKEN);
			c->addExpression(NULL);
		}
		else
		{
			
			//std::cout << "ParserClass cout " << std::endl;
			ExpressionNode *e2=Expression();
			//e->incExpression(e2);
			// ExpressionNode *newEN = &combined;
			c->addExpression(e2);
		}
	}
	Match(SEMICOLON_TOKEN);
	//c->Interpret();
	// std::cout << "parser cout done " << std::endl;
	return c;
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {
	/**/
	MSG("AssignmentStatementNode AssignmentStatement()");
	IdentifierNode *id = Identifier();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	MSG("AssignmentStatement " << ggTokenTypeNames[tt] );
	if (tt == MINUSEQUAL_TOKEN) { //machine code, push val on stack, push val code_->eval on right on stack poppopaddpush then pop and store
		Match(tt);
			ExpressionNode * e = Expression();
			Match(SEMICOLON_TOKEN);
			AssignmentStatementNode* a = new MinusEqualNode(id, e);
			return a;
	}
	if (tt == PLUSEQUAL_TOKEN) {
		Match(tt);
		ExpressionNode * e = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode* a = new PlusEqualNode(id, e);
		return a;
	}
	if (tt == TIMESEQUAL_TOKEN) {
		Match(tt);
		ExpressionNode * e = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode* a = new TimesEqualNode(id, e);
		return a;
	}
	if (tt == DIVIDEEQUAL_TOKEN) {
		Match(tt);
		ExpressionNode * e = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode* a = new DivideEqualNode(id, e);
		return a;
	}
	if (tt == PLUSEQUAL_TOKEN) {
		Match(tt);
		ExpressionNode * e = new IntegerNode(1);
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode* a = new PlusEqualNode(id, e);
		return a;
	}

	Match(ASSIGNMENT_TOKEN);
	ExpressionNode *exp = Expression();
	Match(SEMICOLON_TOKEN);

	AssignmentStatementNode *asgn = new AssignmentStatementNode(id, exp);
	return asgn;
}

ExpressionNode * ParserClass::Expression()

{
	MSG("ExpressionNode Expression()");
	ExpressionNode * current = And();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(	tt == OR_TOKEN)
	{
		Match(tt);
		current = new OrNode(current, And());
	}
	return current;
}

ExpressionNode * ParserClass::And() {
	MSG("ExpressionNode AND()");
	ExpressionNode * current = Relational();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == AND_TOKEN)
		{
			Match(tt);
			current = new AndNode(current, Relational());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode * ParserClass::Relational() {
	ExpressionNode * current = PlusMinus();
	while(true)
	{
		MSG("ExpressionNode Relational()");
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == LESS_TOKEN) {
			Match(tt);
			current = new LessNode(current, PlusMinus());
		}
		else if(tt == LESSEQUAL_TOKEN) {
			Match(tt);
			current = new LessEqualNode(current, PlusMinus());
		}
		else if(tt == GREATER_TOKEN) {
			Match(tt);
			current = new GreaterNode(current, PlusMinus()); 
		}
		else if(tt == GREATEREQUAL_TOKEN) {
			Match(tt);
			current = new GreaterEqualNode(current, PlusMinus());
		}
		else if(tt == EQUAL_TOKEN) {
			Match(tt);
			current = new EqualNode(current, PlusMinus());
		}
		else if(tt == NOTEQUAL_TOKEN) {
			Match(tt);
			current = new NotEqualNode(current, PlusMinus());
		}
		else {
			return current;
		}

	}
}

ExpressionNode * ParserClass::PlusMinus() {
	ExpressionNode * current = TimesDivide();
	while(true)
	{
		MSG("ExpressionNode PlusMinus()");
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == PLUS_TOKEN) {
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		}
		else if(tt == MINUS_TOKEN) {
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		}
		else {
			return current;
		}

	}
}

ExpressionNode * ParserClass::TimesDivide() {
	ExpressionNode * current = Not();
	while(true)
	{
		MSG("ExpressionNode TimesDivide() ")
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == TIMES_TOKEN) {
			Match(tt);
			current = new TimesNode(current, Not());
		}
		else if(tt == DIVIDE_TOKEN) {
			Match(tt);
			current = new DivideNode(current, Not());
		}
		else if (tt == MOD_TOKEN)
		{
			Match(tt);
			current = new ModulusNode(current, Not());
		}
		else {
			return current;
		}

	}
}

ExpressionNode * ParserClass::Not() {
	MSG("ExpressionNode NOT()");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == NOT_TOKEN) {
		Match(tt);
		NotNode * current = new NotNode(Not());
		return current;
	}
	else {return Factor();}
}

ExpressionNode * ParserClass::Factor() {
	MSG("ExpressionNode Factor()");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == IDENTIFIER_TOKEN) {
		ExpressionNode * current = Identifier();
		return current;
	}
	else if(tt == INTEGER_TOKEN) {
		ExpressionNode * current = Integer();
		return current;
	}
	else if(tt == LPAREN_TOKEN) {
		Match(tt);
		ExpressionNode * current = Expression();
		Match(RPAREN_TOKEN);
		return current;
	}
	else {
		cerr << "Factor error on line " << mScanner->mLineNumber;
		cerr << "Expected 'identifier', 'integer', or '(' token";
		exit(1);
	}
}


IdentifierNode * ParserClass::Identifier() {
	MSG("IdentifierNode identifier()");
	TokenClass t = Match(IDENTIFIER_TOKEN);
	string name = t.GetLexeme();
	IdentifierNode *id = new IdentifierNode(name, mSymbol);
	return id;
}

IntegerNode * ParserClass::Integer() {
	MSG("IntegerNode Integer() ");
	TokenClass t = Match(INTEGER_TOKEN);
	string value = t.GetLexeme();
	IntegerNode *en = new IntegerNode(stoi(value));
	return en;
}









/***INTERPRETER **** */

// void IfNode:Interpret() {
// 	if(mExpressionTest.Evaluate()) {
// 		mStatementNode->Interpret()
// 	}
// }

// Priorities:
// * /
// + - 
// <= < > >= != ==
// &&
// ||

// Or -> And -> PlusMinus -> TimesDivide -> Factor (Ident, Int, Expr)





IfStatementNode * ParserClass::If() {
	MSG("IfStatementNode if()");
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	TokenClass T=mScanner->PeekNextToken();
	ExpressionNode *e=Expression();
	Match(RPAREN_TOKEN);
	// BlockNode *bn = Block();
	StatementNode *s=Statement();
	
	IfStatementNode *isn=new IfStatementNode(e,s);

	T=mScanner->PeekNextToken();
	if(T.GetTokenType()==ELSE_TOKEN)
	{
		isn->SetElse();
		Match(ELSE_TOKEN);
		StatementNode *n=Statement();
		
		isn->SetElseNode(n);
	}
	return isn;
}

WhileStatementNode * ParserClass::While() {
	MSG("WhileStatementNode While()");
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode *exp = Expression();
	Match(RPAREN_TOKEN);
	BlockNode *bn = Block();
	WhileStatementNode *wh = new WhileStatementNode(exp, bn);
	return wh;
}
/*Repeat Node*/
RepeatStatementNode * ParserClass::Repeat(){
	MSG("RepeatStatementNode repeat()");
	Match(REPEAT_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode *exp = Expression();
	Match(RPAREN_TOKEN);
	StatementNode *sn = Statement();
	RepeatStatementNode *repeat = new RepeatStatementNode(exp, sn);
	return repeat;

}

/*Do While*/

DoWhileNode * ParserClass::DoWHILE() {
	MSG("DO WHILE Node");
	Match(DO_TOKEN);
	
	BlockNode *bn = Block();
	//StatementNode * s = Statement();
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* e = Expression();
	Match(RPAREN_TOKEN);
	Match(SEMICOLON_TOKEN);
	DoWhileNode* a = new DoWhileNode(e, bn);
	return a;
}
/*	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode *exp = Expression();
	Match(RPAREN_TOKEN);
	BlockNode *bn = Block();
	WhileStatementNode *wh = new WhileStatementNode(exp, bn);*/