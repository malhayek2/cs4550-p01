#include "token.h"
#include "scanner.h"
#include "statemachine.h"

#include <iostream>
#include <vector>
#include <utility>
#include <string>
/*Testing*/

int main()
{
	ScannerClass scanner("problem01.txt");
	// TokenType tt = VOID_TOKEN;
	// string lexeme = "void";
	// TokenClass tok1(tt, lexeme);
	// cout << tok1 << endl;
	/*in the getNextToken*/
	
	TokenClass tc = scanner.GetNextToken();
	//TokenClass nc;
	//cout << "Type Name : " << tc.GetTokenTypeName() << endl;
	//cout << "Type : " << tc.GetTokenType() << endl;
	while(tc.GetTokenType()!=ENDFILE_TOKEN){
		tc = scanner.GetNextToken();
		cout << "Token Type: "  << tc.GetTokenType() << "Name:" << tc.GetTokenTypeName() << endl;
	}
}