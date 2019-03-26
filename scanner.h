#ifndef SCANNER 
#define SCANNER

#include <fstream>
#include <iostream>
using namespace std;
#include "token.h"
#include "statemachine.h"


class ScannerClass
{
public:
	ScannerClass(const char* file);
	~ScannerClass();
	int GetLineNumber();
	TokenClass GetNextToken();
	TokenClass PeekNextToken();
	int mLineNumber;

private:
	ifstream  mFin;

	int mLocation;
};


#endif // SCANNER