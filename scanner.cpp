#include <string>
#include <cstdlib>
using namespace std;
#include "scanner.h"
#include "debug.h"

ScannerClass::ScannerClass(const char *file)
{
	MSG("Initializing ScannerClass object");
	/*mLineNumber set = 1 */
	this->mLineNumber=1;
	this->mFin.open(file,ios::binary);
	if(!mFin)
	{
		MSG("failed to read input file"); 
		
	}
	this->mLocation=0;
}
/*Getter mLinerNumber*/
int ScannerClass::GetLineNumber(){
	return mLineNumber;
}
ScannerClass::~ScannerClass(){this->mFin.close();}
TokenClass ScannerClass::GetNextToken()
{
	StateMachineClass StateMachine;
	TokenType tt;
	string lexeme;
	while(true)
	{
		// 
		/*read the next char*/
		char c=mFin.get();
		/*increment the lexeme char by char */
		lexeme += c;
		MachineState ms = StateMachine.UpdateState(c,tt);
		/*carriage return incrment mLineNumber*/
		if(lexeme=="\n") {mLineNumber++; }
		/*Break when reaching a cantmove state*/
		if(ms==CANTMOVE_STATE) { break; }
		/*set start_state lexeme to nothing*/
		if(ms==START_STATE) { lexeme = ""; }
	}
	if(tt==BAD_TOKEN)
	{
		cout<<"Bad State: " << tt << endl;
		MSG("Bad Token Read : "  + tt );
		exit(1);
	}
	/* unget() decrease the current location in the stream by one character*/
	mFin.unget();
	/*decrment the mLineNumber */
	//MSG("Current Line Number 	" << this->GetLineNumber());

	if(lexeme=="\n"){mLineNumber--;}
	lexeme.resize(lexeme.size()-1);
	TokenClass newToken(tt, lexeme);
	newToken.CheckReserved();
	return newToken;
}
TokenClass ScannerClass::PeekNextToken()
{
	//store current state
	int linenum = mLineNumber;
	streamoff offset = mFin.tellg();

	//get info
	TokenClass T=GetNextToken();
	if(mFin.eof()) //should be this...
	{
		cout << "Clearing..." << endl;
		mFin.clear();
	}
	mFin.clear();//...instead of this, but works for now

	//restore
	mFin.seekg(offset);
	mLineNumber=linenum;

	return T;
}