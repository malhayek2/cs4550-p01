#include <cstdio>
#include <cstdlib>
using namespace std;
#include "statemachine.h"
#include "debug.h"

bool commentline=false;
bool commentblock=false;
StateMachineClass::StateMachineClass()
{
	// First, initialize all the mLegalMoves to CANTMOVE_STATE
	// Then, reset the mLegalMoves that are legitimate 

	MSG("Initializing StateMachine");
	mCurrentState=START_STATE;
	mLegalMoves[LAST_STATE][LAST_CHAR];
	mCorrespondingTokenTypes[LAST_STATE];
	
	for(int i=0; i<LAST_STATE; i++){for(int j=0; j<LAST_CHAR; j++){mLegalMoves[i][j] = CANTMOVE_STATE;}}
	mLegalMoves[START_STATE][LETTER_CHAR]=IDENTIFIER_STATE;
	mLegalMoves[START_STATE][DIGIT_CHAR]=INTEGER_STATE;
	mLegalMoves[START_STATE][WHITESPACE_CHAR]=START_STATE;
	mLegalMoves[START_STATE][SPACE_CHAR]=START_STATE;
	mLegalMoves[START_STATE][TAB_CHAR]=START_STATE;
	mLegalMoves[START_STATE][RETURN_CHAR]=START_STATE;
	mLegalMoves[START_STATE][LCURLY_CHAR]=LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR]=RCURLY_STATE;
	mLegalMoves[START_STATE][LPAREN_CHAR]=LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN_CHAR]=RPAREN_STATE;
	mLegalMoves[START_STATE][PLUS_CHAR]=PLUS_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR]=MINUS_STATE;
	mLegalMoves[START_STATE][TIMES_CHAR]=TIMES_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR]=DIVIDE_STATE;
	mLegalMoves[START_STATE][LESS_CHAR]=LESS_STATE;
	mLegalMoves[START_STATE][GREATER_CHAR]=GREATER_STATE;
	mLegalMoves[START_STATE][EQUAL_CHAR]=ASSIGNMENT_STATE;
	mLegalMoves[START_STATE][NOT_CHAR]=NOT_STATE;
	mLegalMoves[START_STATE][NOTEQUAL_CHAR]=NOTEQUAL_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR]=SEMICOLON_STATE;
	mLegalMoves[START_STATE][ENDFILE_CHAR]=ENDFILE_STATE;
	mLegalMoves[START_STATE][BEGIN_CHAR]=BEGIN_STATE;
	mLegalMoves[START_STATE][END_CHAR]=END_STATE;
	mLegalMoves[START_STATE][AND_CHAR]=AND_STATE;
	mLegalMoves[START_STATE][OR_CHAR]=OR_STATE;

	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]=IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]=IDENTIFIER_STATE;

	mLegalMoves[INTEGER_STATE][LETTER_CHAR]=IDENTIFIER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR]=INTEGER_STATE;

	mLegalMoves[LESS_STATE][LESS_CHAR]=INSERTION_STATE;
	mLegalMoves[LESS_STATE][EQUAL_CHAR]=LESSEQUAL_STATE;
	mLegalMoves[GREATER_STATE][EQUAL_CHAR]=GREATEREQUAL_STATE;
	mLegalMoves[ASSIGNMENT_STATE][EQUAL_CHAR]=EQUAL_STATE;

	mLegalMoves[ASSIGNMENT_STATE][NOT_CHAR]=NEGATE_STATE;

	mLegalMoves[NOT_STATE][NOTEQUAL_CHAR]=NOTEQUAL_STATE;
	//mLegalMoves[NOT_STATE][EQUAL_CHAR]=NOTEQUAL_STATE;
	//mLegalMoves[NOT_STATE][DIGIT_CHAR]=NOTVALUE_STATE;


	mLegalMoves[AND_STATE][AND_CHAR]=AND_STATE;
	mLegalMoves[OR_STATE][OR_CHAR]=OR_STATE;

	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR]=COMMENT_LINE_STATE;
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR]=COMMENT_START_STATE;
	mLegalMoves[TIMES_STATE][DIVIDE_CHAR]=COMMENT_END_STATE;

	mLegalMoves[PLUS_STATE][EQUAL_CHAR]=PLUSEQUAL_STATE;
	mLegalMoves[MINUS_STATE][EQUAL_CHAR]=MINUSEQUAL_STATE;
	mLegalMoves[TIMES_STATE][EQUAL_CHAR]=TIMESEQUAL_STATE;
	//tokens
	// First, initialize all states to correspond to the BAD token type.
	// Then, reset the end states to correspond to the correct token types.

	for(int i=0; i<LAST_STATE; i++){mCorrespondingTokenTypes[i]=BAD_TOKEN;}
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	/*Reserved Words:*/
	mCorrespondingTokenTypes[VOID_STATE] = VOID_TOKEN;
	mCorrespondingTokenTypes[MAIN_STATE] = MAIN_TOKEN;
	mCorrespondingTokenTypes[INT_STATE] = INT_TOKEN;
	mCorrespondingTokenTypes[COUT_STATE] = COUT_TOKEN;
	mCorrespondingTokenTypes[BOOL_STATE] = BOOL_TOKEN;
	mCorrespondingTokenTypes[TRUE_STATE] = TRUE_TOKEN;
	mCorrespondingTokenTypes[FALSE_STATE] = FALSE_TOKEN;
	/*added repeat token!*/
	mCorrespondingTokenTypes[REPEAT_STATE] = REPEAT_TOKEN;
	/*Relational Operators:*/
	mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[NOT_STATE] = NOT_TOKEN;
	mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;


	mCorrespondingTokenTypes[NEGATE_STATE] = NEGATE_TOKEN;

	/*Other Operators:*/
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[PLUSEQUAL_STATE] = PLUSEQUAL_TOKEN;
	mCorrespondingTokenTypes[MINUSEQUAL_STATE] = MINUSEQUAL_TOKEN;
	mCorrespondingTokenTypes[TIMESEQUAL_STATE] = TIMESEQUAL_TOKEN;
	/*Other Characters:*/
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[BEGIN_STATE] = BEGIN_TOKEN;
	mCorrespondingTokenTypes[END_STATE] = END_TOKEN;
	mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
	/*Other Token Types:*/
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[BAD_STATE] = BAD_TOKEN;
}
char lastchar;
MachineState StateMachineClass::UpdateState(char currentCharacter,TokenType & correspondingTokenType)
{
	// MSG("Updating State w currnetChar: " << currentCharacter);
	
	// MSG("corresponding TokenType: " << correspondingTokenType);
	// convert the input character into an input character type
	CharacterType charType = BAD_CHAR;
	

	//get out of comment mode
	if(currentCharacter=='\n'){commentline=false;}
	if(lastchar=='*' && currentCharacter=='/'){commentblock=false;}

	//get into comment mode
	if(currentCharacter=='/' && !commentline && !commentblock){commentline=true;}
	else if(currentCharacter=='*' && lastchar=='/'){commentblock=true;}

	if(commentline){charType = WHITESPACE_CHAR;}
	else if(commentblock){charType = WHITESPACE_CHAR;}

	else if(currentCharacter=='=' && lastchar=='!'){charType=NOTEQUAL_CHAR;}

	else if(isdigit(currentCharacter)){charType = DIGIT_CHAR;}
	else if(isalpha(currentCharacter)){charType = LETTER_CHAR;}
	else if(currentCharacter==' '){charType = WHITESPACE_CHAR;}
	else if(currentCharacter=='\t'){charType = WHITESPACE_CHAR;}
	else if(currentCharacter=='\n'){charType = WHITESPACE_CHAR;}
	else if(currentCharacter=='\r'){charType = WHITESPACE_CHAR;}
	else if(isspace(currentCharacter)){charType = WHITESPACE_CHAR;}
	else if(currentCharacter=='_'){charType = LETTER_CHAR;}
	else if(currentCharacter=='{'){charType = LCURLY_CHAR;}
	else if(currentCharacter=='}'){charType = RCURLY_CHAR;}
	else if(currentCharacter=='('){charType = LPAREN_CHAR;}
	else if(currentCharacter==')'){charType = RPAREN_CHAR;}
	else if(currentCharacter=='+'){charType = PLUS_CHAR;}
	else if(currentCharacter=='-'){charType = MINUS_CHAR;}
	else if(currentCharacter=='*'){charType = TIMES_CHAR;}
	else if(currentCharacter=='/'){charType = DIVIDE_CHAR;}
	else if(currentCharacter=='<'){charType = LESS_CHAR;}
	else if(currentCharacter=='>'){charType = GREATER_CHAR;}
	else if(currentCharacter=='='){charType = EQUAL_CHAR;}
	else if(currentCharacter=='!'){charType = NOT_CHAR;}
	else if(currentCharacter==';'){charType = SEMICOLON_CHAR;}
	else if(currentCharacter=='&'){charType = AND_CHAR;}
	else if(currentCharacter=='|'){charType = OR_CHAR;}
	else if(currentCharacter==EOF){charType = ENDFILE_CHAR;}

	lastchar=currentCharacter;

	if(charType==BAD_CHAR)
	{
		MSG("Char Type is bad " + charType);
		cerr<<"Bad char: " << currentCharacter;
		exit(1);
	}
	/*correspondingTokenType reference parameter as follows*/
	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}