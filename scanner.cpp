#include <string>
#include <cstdlib>
using namespace std;
#include "scanner.h"

ScannerClass::ScannerClass(const char *file)
{
	
	this->mLineNumber=1;
	this->mFin.open(file,ios::binary);
	if(!mFin)
	{
		cout<<"Bad ifstream start" << endl; 
		
	}
	this->mLocation=0;
}
ScannerClass::~ScannerClass(){this->mFin.close();}
TokenClass ScannerClass::GetNextToken()
{
	StateMachineClass StateMachine;
	TokenType tt;
	string lexeme;
	while(true)
	{
		char c=mFin.get();
		lexeme += c;
		MachineState ms = StateMachine.UpdateState(c,tt);
		if(lexeme=="\n") {mLineNumber++; }
		if(ms==CANTMOVE_STATE) { break; }
		if(ms==START_STATE) { lexeme = ""; }
	}
	if(tt==BAD_TOKEN)
	{
		cout<<"Bad State " << endl;
		exit(1);
	}

	mFin.unget();
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