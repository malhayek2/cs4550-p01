#include "token.h"
#include "scanner.h"
#include "statemachine.h"
#include "debug.h"
#include "Symbol.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "node.h"
/*Testing*/

std::string printTrueORFalse(bool given){
	if(given){
		return "True";
	}
	return "False";
}


int main()
{
	/*Testing Nodes */
	StatementGroupNode *statementgroupnode=new StatementGroupNode(); //no paramaters-added later
	SymbolTableClass *mySTC = new SymbolTableClass() ;
	mySTC->AddEntry("Hello World");
	IdentifierNode *identifiernode=new IdentifierNode("sum", mySTC );//symboltable address
	IntegerNode *integernode=new IntegerNode(5);
	
	AssignmentStatementNode *assignmentstatementnode=new AssignmentStatementNode(identifiernode,integernode);
	DeclarationStatementNode *declarationstatementnode=new DeclarationStatementNode(identifiernode);
	CoutStatementNode *coutstatementnode=new CoutStatementNode(identifiernode);
	/*testing add Statement pushs back nodes into the gourp */
	/*since they are inherited from Node, they should be okay as a parameter*/
	statementgroupnode->AddStatement(declarationstatementnode);
	statementgroupnode->AddStatement(assignmentstatementnode);
	statementgroupnode->AddStatement(coutstatementnode);
	/*PlusNode is inherited from BinaryOperatorNode, Testing its contructor = tesing BinaryOperatorNode */
	PlusNode *plusnode=new PlusNode(integernode,integernode);
	std::cout<<"plusnode: "<<plusnode->Evaluate()<<std::endl;

	BlockNode *blocknode=new BlockNode(statementgroupnode);
	ProgramNode *programnode=new ProgramNode(blocknode);
	StartNode *startnode=new StartNode(programnode);

	delete startnode;
	return 0;
}


void testScanner(){
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
		cout << "Current Line Number " << scanner.GetLineNumber() << endl;
		/*prints TokenTypeName & Lexeme */
		cout << "TokenType Enum: " << tc.GetTokenString() << endl;
		cout << tc << endl;
	}	
}

void testSymbolTable(){
	/*Constructor */
	SymbolTableClass mySTC;
	/*Test AddEntry*/
	mySTC.AddEntry("Hello World");
	/*an error should be thrown*/
	mySTC.AddEntry("Hello World");
	/*Test Exists*/
	std::cout << "Does Hello World Exists " << printTrueORFalse(mySTC.Exists("Hello World")) << std::endl;
	/*add SetValue Label, Value*/
	mySTC.SetValue("Hello World" , 123);
	/*Get Value*/
	std::cout << "Getting the NEW value of Hello World : "  << mySTC.GetValue("Hello World") << std::endl;
	/*Get Index*/
	std::cout << "Getting the Index " << mySTC.GetIndex("Hello World") << std::endl;
	/*Get Count*/
	std::cout << "Current Count in the SymbolTableClass "  << mySTC.GetCount() << std::endl;

}