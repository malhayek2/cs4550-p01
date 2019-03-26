#include <cstdlib>
using namespace std;
#include "parser.h"

ParserClass::ParserClass(ScannerClass *sc, SymbolTableClass *stc)
{
	this->mScanner=sc;
	this->mSymbolTable=stc;
}
ParserClass::~ParserClass(){}
SymbolTableClass *ParserClass::getSymbolTable(){return mSymbolTable;}
StartNode *ParserClass::Start()
{
	// PCMSG("ParserClass::Start()");
	ProgramNode *p = Program();
	Match(ENDFILE_TOKEN);
	StartNode *n = new StartNode(p);
	return n;
}

// Verify that the next token in the input file is of the same type
// that the parser expects.
TokenClass ParserClass::Match(TokenType expectedType)
{
	// PCMSG("ParserClass::Match()");
	TokenClass currentToken = mScanner->GetNextToken();
	//if((currentToken.GetTokenType() == LCURLY_TOKEN) && (expectedType == BEGIN_TOKEN)){return currentToken;}
	//if((currentToken.GetTokenType() == BEGIN_TOKEN) && (expectedType == LCURLY_TOKEN)){return currentToken;}
	//if((currentToken.GetTokenType() == RCURLY_TOKEN) && (expectedType == END_TOKEN)){return currentToken;}
	//if((currentToken.GetTokenType() == END_TOKEN) && (expectedType == RCURLY_TOKEN)){return currentToken;}
	if(currentToken.GetTokenType() != expectedType)
	{
		cerr<<"Error: Expected token type "<<gTokenTypeNames[expectedType]<<", but got type "<<currentToken<<" in ParserClass::Match."<<endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: "<<currentToken.GetTokenTypeName()<< ". Lexeme: \""<<currentToken.GetLexeme()<< "\"");
	return currentToken;
}
DeclarationStatementNode *ParserClass::DeclarationStatement()
{
	// PCMSG("ParserClass::DeclarationStatement()");
	TokenType tt=mScanner->PeekNextToken().GetTokenType();
	if(tt==BOOL_TOKEN)
	{
		Match(BOOL_TOKEN);
		IdentifierNode *i=Identifier();
		Match(SEMICOLON_TOKEN);
		DeclarationStatementNode *d=new DeclarationStatementNode(i);
		return d;
	}
	else if(tt==INTEGER_TOKEN)
	{
		Match(INTEGER_TOKEN);
		IdentifierNode *i=Identifier();
		Match(SEMICOLON_TOKEN);
		DeclarationStatementNode *d=new DeclarationStatementNode(i);
		return d;
	}
	else
	{
		cerr<<"Error: Incorrect token type "<<gTokenTypeNames[tt]<<" in ParserClass::DeclarationStatement()"<<endl;
		exit(1);
	}
}
AssignmentStatementNode *ParserClass::AssignmentStatement()
{
	// PCMSG("ParserClass::AssignmentStatement()");
	IdentifierNode *i=Identifier();
	if(mScanner->PeekNextToken().GetTokenType()==PLUSEQUAL_TOKEN)
	{
		Match(PLUSEQUAL_TOKEN);
		ExpressionNode *e=Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode *a=new PlusEqualNode(i, e);
		return a;
	}
	else if(mScanner->PeekNextToken().GetTokenType()==MINUSEQUAL_TOKEN)
	{
		Match(MINUSEQUAL_TOKEN);
		ExpressionNode *e=Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode *a=new MinusEqualNode(i, e);
		return a;
	}
	else if(mScanner->PeekNextToken().GetTokenType()==TIMESEQUAL_TOKEN)
	{
		Match(TIMESEQUAL_TOKEN);
		ExpressionNode *e=Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode *a=new TimesEqualNode(i, e);
		return a;
	}
	
	else if(mScanner->PeekNextToken().GetTokenType()==NEGATE_TOKEN)
	{
		Match(NEGATE_TOKEN);

		cout<<mScanner->PeekNextToken().GetTokenType()<<endl;

		ExpressionNode *e=Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode *a=new NegateNode(i, e);
		return a;
	}
	else
	{
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode *e=Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode *a=new AssignmentStatementNode(i, e);
		return a;
	}
}
CoutStatementNode * ParserClass::CoutStatement()
{
	// PCMSG("ParserClass::CoutStatement()");
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
			ExpressionNode *e=Expression();
			c->addExpression(e);
		}
	}
	Match(SEMICOLON_TOKEN);
	return c;
}
StatementGroupNode *ParserClass::StatementGroup()
{
	// PCMSG("ParserClass::StatementGroup()");
	StatementGroupNode *s=new StatementGroupNode();
	while(true)
	{
		StatementNode * sn = Statement();
		if(sn==NULL){break;}
		s->AddStatement(sn);	
	}
	return s;
}
StatementNode *ParserClass::Statement()
{
	TokenClass T=mScanner->PeekNextToken();
	StatementNode *curr=NULL;
	if(T.GetTokenType()==INTEGER_TOKEN) {curr=DeclarationStatement();}
	else if(T.GetTokenType()==BOOL_TOKEN) {curr=DeclarationStatement();}//bool
	else if(T.GetTokenType()==IDENTIFIER_TOKEN) {curr=AssignmentStatement();}
	else if(T.GetTokenType()==COUT_TOKEN) {curr=CoutStatement();}
	else if(T.GetTokenType()==LCURLY_TOKEN) {curr=Block();}
	else if(T.GetTokenType()==IF_TOKEN) {curr=IfStatement();}
	else if(T.GetTokenType()==WHILE_TOKEN) {curr=WhileStatement();}
	else if(T.GetTokenType()==BEGIN_TOKEN) {curr=Blockwords();}
	return curr;
}
IfStatementNode *ParserClass::IfStatement()
{
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	TokenClass T=mScanner->PeekNextToken();
	ExpressionNode *e=Expression();
	Match(RPAREN_TOKEN);
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
WhileStatementNode *ParserClass::WhileStatement()
{
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	TokenClass T=mScanner->PeekNextToken();
	ExpressionNode *e=Expression();
	Match(RPAREN_TOKEN);
	StatementNode *s=Statement();
	WhileStatementNode *isn=new WhileStatementNode(e,s);
	return isn;
}
BlockNode *ParserClass::Block()
{
	// PCMSG("ParserClass::Block()");
	TokenType tt=mScanner->PeekNextToken().GetTokenType();
	if(tt==LCURLY_TOKEN)
	{
		Match(LCURLY_TOKEN);
		StatementGroupNode * sgn = StatementGroup();
		Match(RCURLY_TOKEN);
		BlockNode * bn = new BlockNode(sgn, getSymbolTable());
		return bn;
	}
	else if(tt==BEGIN_TOKEN)
	{
		Match(BEGIN_TOKEN);
		StatementGroupNode * sgn = StatementGroup();
		Match(END_TOKEN);
		BlockNode * bn = new BlockNode(sgn, getSymbolTable());
		return bn;
	}
	else
	{
		cerr<<"Error: in ParserClass::Block()"<<endl;
		exit(1);
	}
}
BlockNode *ParserClass::Blockwords()
{
	// PCMSG("ParserClass::Blockwords()");
	Match(BEGIN_TOKEN);
	StatementGroupNode * sgn = StatementGroup();
	Match(END_TOKEN);
	BlockNode * bn = new BlockNode(sgn, getSymbolTable());
	return bn;
}
ProgramNode *ParserClass::Program()
{
	// PCMSG("ParserClass::Program()");
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode *b = Block();
	Match(ENDFILE_TOKEN);
	ProgramNode *n = new ProgramNode(b);
	return n;
}
ExpressionNode *ParserClass::Expression()
{
	// PCMSG("ParserClass::Expression()");
	ExpressionNode * current = Or();
	return current;
}
ExpressionNode *ParserClass::Side()
{
	// PCMSG("ParserClass::Side()");
	ExpressionNode *current = Term();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, Term());
		}
		else if(tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, Term());
		}
		else { break; }
	}
	return current;
}
ExpressionNode *ParserClass::Term()
{
	// PCMSG("ParserClass::Term()");
	ExpressionNode *current = Factor();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == TIMES_TOKEN)
		{
			Match(tt);
			current = new TimesNode(current, Factor());
		}
		else if(tt == DIVIDE_TOKEN)
		{
			Match(tt);
			current = new DivideNode(current, Factor());
		}
		else { break; }
	}
	return current;
}
ExpressionNode *ParserClass::Factor()
{
	// PCMSG("ParserClass::Factor()");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt==IDENTIFIER_TOKEN)
	{
		return Identifier();
	}
	else if(tt==INTEGER_TOKEN)
	{
		return Integer();
	}
	else if(tt==LPAREN_TOKEN)
	{
		Match(LPAREN_TOKEN);
		ExpressionNode * current = Expression();
		Match(RPAREN_TOKEN);
		return current;
	}
	else if(tt==TRUE_TOKEN || tt==FALSE_TOKEN){return Boolean();}
	else
	{
		cerr<<"Error: Incorrect token type "<<gTokenTypeNames[tt]<<" in ParserClass::Factor()"<<endl;
		exit(1);
	}
}

BooleanNode *ParserClass::Boolean()
{
	// PCMSG("ParserClass::Boolean()");
	TokenType tt = mScanner->PeekNextToken().GetTokenType();

	if(tt==TRUE_TOKEN)
	{
		TokenClass tc=Match(TRUE_TOKEN);
		BooleanNode *b=new BooleanNode(true);
		return b;
	}
	else if(tt==FALSE_TOKEN)
	{
		TokenClass tc=Match(FALSE_TOKEN);
		BooleanNode *b=new BooleanNode(false);
		return b;
	}
	else
	{
		cerr<<"Error: Incorrect token type "<<gTokenTypeNames[tt]<<" in ParserClass::Boolean()"<<endl;
		exit(1);
	}
}

IdentifierNode *ParserClass::Identifier()
{
	// PCMSG("ParserClass::Identifier()");
	TokenClass tc=Match(IDENTIFIER_TOKEN);
	IdentifierNode *i=new IdentifierNode(tc.GetLexeme(), getSymbolTable());
	return i;
}

IntegerNode *ParserClass::Integer()
{
	// PCMSG("ParserClass::Integer()");

	TokenClass tc=Match(INTEGER_TOKEN);
	int tci = atoi(tc.GetLexeme().c_str());
	IntegerNode *i=new IntegerNode(tci);
	return i;
}
/*parser #1*/
ExpressionNode *ParserClass::Relational()
{
	MSG("ParserClass::Relational()");

	ExpressionNode *current=Side();

	TokenType tt = mScanner->PeekNextToken().GetTokenType();


	if(tt==LESS_TOKEN)
	{
		Match(tt);
		current=new LessNode(current,Side());
	}
	else if(tt==LESSEQUAL_TOKEN)
	{
		Match(tt);
		current=new LessEqualNode(current,Side());
	}
	else if(tt==GREATER_TOKEN)
	{
		Match(tt);
		current=new GreaterNode(current,Side());
	}
	else if(tt==GREATEREQUAL_TOKEN)
	{
		Match(tt);
		current=new GreaterEqualNode(current,Side());
	}
	else if(tt==EQUAL_TOKEN)
	{
		Match(tt);
		current=new EqualNode(current,Side());
	}
	else if(tt==NOTEQUAL_TOKEN)
	{
		Match(tt);
		current=new NotEqualNode(current,Side());
	}
	return current;
}
ExpressionNode *ParserClass::And()
{
	// PCMSG("ParserClass::And()");
	ExpressionNode *c = Relational();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt==AND_TOKEN)
		{
			Match(tt);
			c=new AndNode(c,Relational());
		}
		else {break;}
	}
	return c;
}
ExpressionNode *ParserClass::Or()
{
	// PCMSG("ParserClass::Or()");
	ExpressionNode *c = And();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt==OR_TOKEN)
		{
			Match(tt);
			ExpressionNode *c2 = And();
			c=new OrNode(c,c2);
		}
		else {break;}
	}
	return c;
}