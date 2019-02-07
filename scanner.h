#pragma once

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
	int GetLineNumber(){return mLineNumber;};
	TokenClass GetNextToken();
	TokenClass PeekNextToken();

private:
	ifstream  mFin;
	int mLineNumber;
	int mLocation;
};