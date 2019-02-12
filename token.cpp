#include "token.h"
#include "debug.h"

TokenClass::TokenClass(){}

TokenClass::TokenClass(TokenType type, const string & lexeme)
{
	MSG("Initializing Token");
	this->mType=type;
	this->mLexeme=lexeme;
}
void TokenClass::CheckReserved()
{

	if(mLexeme=="main"){mType=MAIN_TOKEN;}
	else if(mLexeme=="repeat"){mType=REPEAT_TOKEN;}
	else if(mLexeme=="void"){mType=VOID_TOKEN;}
	else if(mLexeme=="cout"){mType=COUT_TOKEN;}
	else if(mLexeme=="int"){mType=INTEGER_TOKEN;}
	else if(mLexeme=="if"){mType=IF_TOKEN;}
	else if(mLexeme=="else"){mType=ELSE_TOKEN;}
	else if(mLexeme=="while"){mType=WHILE_TOKEN;}
	else if(mLexeme=="begin"){mType=BEGIN_TOKEN;}
	else if(mLexeme=="end"){mType=END_TOKEN;}
	else if(mLexeme=="endl"){mType=ENDL_TOKEN;}

	else if(mLexeme=="bool"){mType=BOOL_TOKEN;}
	else if(mLexeme=="true"){mType=TRUE_TOKEN;}
	else if(mLexeme=="false"){mType=FALSE_TOKEN;}
}
ostream &operator<<(ostream &out, const TokenClass &tc)
{
	out<<tc.TokenClass::GetTokenTypeName()<<": '"<<tc.TokenClass::GetLexeme()<<"'";
	return out;
}