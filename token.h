#ifndef TOKEN
#define TOKEN


#include <string>
#include <iostream>
using namespace std;


enum TokenType 
{
	/*Reserved Words:*/
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN, BOOL_TOKEN, TRUE_TOKEN, FALSE_TOKEN, REPEAT_TOKEN,
	/*Relational Operators:*/
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOT_TOKEN, NOTEQUAL_TOKEN,NEGATE_TOKEN,
	/*Other Operators:*/
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN, TIMESEQUAL_TOKEN,
	/*Other Characters:*/
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN, OR_TOKEN, AND_TOKEN,
	/*Other Token Types:*/
	BEGIN_TOKEN,END_TOKEN,IDENTIFIER_TOKEN, INTEGER_TOKEN, BAD_TOKEN, ENDFILE_TOKEN, ENDL_TOKEN
};
const string gTokenTypeNames[] = 
{
	"VOID", "MAIN", "INT", "COUT", "IF", "ELSE", "WHILE", "BOOL", "TRUE", "FALSE", "REPEAT",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOT","NOTEQUAL","NEGATE",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE","PLUSEQUAL","MINUSEQUAL","TIMESEQUAL",
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY","OR","AND",
	"BEGIN","END","IDENTIFIER", "INTEGER", "BAD", "ENDFILE","ENDL"
};
class TokenClass
{
public:
	TokenClass();
	TokenClass(TokenType type, const string & lexeme);
	TokenType GetTokenType() const { return mType; }
	const string & GetTokenTypeName() const { return gTokenTypeNames[mType]; }
	string GetLexeme() const { return mLexeme; }
	void CheckReserved();
private:
	TokenType mType;
	string mLexeme;
};
ostream & operator<<(ostream & out, const TokenClass & tc);




#endif // TOKEN
