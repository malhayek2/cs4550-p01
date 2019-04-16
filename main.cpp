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
#include "parser.h"
/*Testing*/

std::string printTrueORFalse(bool given){
	if(given){
		return "True";
	}
	return "False";
}

int parserclass(ScannerClass *scanner,SymbolTableClass *symtable)
{
	ParserClass pc(scanner,symtable);
	//cout<< pc->Start() <<endl;
	pc.Start();
	return 0;
}
void nodesTestSymbolTable(){
	/*Testing Nodes */
	StatementGroupNode *statementgroupnode=new StatementGroupNode(); 
	SymbolTableClass *mySTC = new SymbolTableClass() ;
	mySTC->AddEntry("Hello World");
	IdentifierNode *identifiernode=new IdentifierNode("sum", mySTC );//symboltable address
	IntegerNode *integernode= new IntegerNode(5);
	IntegerNode *integernode2 = new IntegerNode(10);
	AssignmentStatementNode *assignmentstatementnode=new AssignmentStatementNode(identifiernode,integernode);
	DeclarationStatementNode *declarationstatementnode=new DeclarationStatementNode(identifiernode);
	CoutStatementNode *coutstatementnode=new CoutStatementNode(identifiernode);
	/*testing add Statement pushs back nodes into the gourp */
	/*since they are inherited from Node, they should be okay as a parameter*/
	statementgroupnode->AddStatement(declarationstatementnode);
	statementgroupnode->AddStatement(assignmentstatementnode);
	statementgroupnode->AddStatement(coutstatementnode);
	/*PlusNode is inherited from BinaryOperatorNode, Testing its contructor = tesing BinaryOperatorNode */
	PlusNode *plusnode=new PlusNode(integernode,integernode2);
	std::cout << "plusnode evaluate : " << plusnode->Evaluate() <<std::endl;
	/*Testing Other BinaryOperatorNodes and their evaluate should be 1 or 0?*/
	MinusNode *minusnode = new MinusNode(integernode,integernode2);
	std::cout << "minusnode evaluate: " << minusnode->Evaluate() <<std::endl;

	TimesNode *timesNode = new TimesNode(integernode,integernode2);
	std::cout << "timesNode evaluate: " << timesNode->Evaluate() <<std::endl;

	DivideNode *divideNode = new DivideNode(integernode,integernode2);
	std::cout << "divideNode evaluate: " << divideNode->Evaluate() <<std::endl;
	/*Those node's evaluate are blooeans therefore it has to be 0 or 1 */
	LessNode *lessnode = new LessNode(integernode,integernode2);
	std::cout << "lessnode evaluate: " << lessnode->Evaluate() <<std::endl;

	LessEqualNode *lessequalnode = new LessEqualNode(integernode,integernode2);
	std::cout << "lessequalnode evaluate: " << lessequalnode->Evaluate() <<std::endl;

	GreaterNode *greaternode = new GreaterNode(integernode,integernode2);
	std::cout << "greaternode evaluate: " << greaternode->Evaluate() <<std::endl;

	GreaterEqualNode *greaterequalnode = new GreaterEqualNode(integernode,integernode);
	std::cout << "greaterequalnode evaluate 5 & 5: " << greaterequalnode->Evaluate() <<std::endl;

	EqualNode *equalNode = new EqualNode(integernode,integernode);
	std::cout << "equalNode evaluate 5 & 5: " << equalNode->Evaluate() <<std::endl;

	NotEqualNode *notequalNode = new NotEqualNode(integernode,integernode2);
	std::cout << "notequalNode evaluate 5 & 10: " << notequalNode->Evaluate() <<std::endl;


	BlockNode *blocknode=new BlockNode(statementgroupnode);
	ProgramNode *programnode=new ProgramNode(blocknode);
	StartNode *startnode=new StartNode(programnode);

	delete startnode;
	// return 0;
}


void interpetTest(){
	const char *file="midterm.txt";
	
	ScannerClass scanner(file);
	//std::cout << scanner.PeekNextToken() << std::endl;
	SymbolTableClass mySTC; 

	ParserClass pc(&scanner,&mySTC);
	//cout<< pc->Start() <<endl;
	StartNode *sn = pc.Start();
	sn->Interpret();
	delete sn;

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


int main()

{
	unsigned char mCode[] = {0x55, 0x8B, 0xEC, 0X5d, 0XC3};
	cout  << "About to Execute the machine code...\n";
	void * ptr = mCode;
	void (*f)(void);
	f = (void (*)(void)) ptr ;
	f(); // call the array as if it were a function
	cout << "There and back again!\n" <<;;
	return 0;

}

