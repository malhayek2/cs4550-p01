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
	
	TokenType tt = scanner.GetNextToken(); 
	TokenType nt;
	while(tt!=ENDFILE_TOKEN){
		nt = scanner.GetNextToken();
		cout << tt << endl;
	}
}