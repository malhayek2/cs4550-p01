#ifndef SYMBOL 
#define SYMBOL

#include "debug.h"
#include <string>
#include <vector>
#include <iostream>



class SymbolTableClass{
public:
	SymbolTableClass();
	bool Exists(const std::string &s);
	void AddEntry (const std::string &s);
	int GetValue (const std::string &s);
	void SetValue(const std::string &s, int v);
	int GetIndex (const std::string &s);
	int GetCount();
	/*Inter*/
	void PushScope();
	void PopScope();


	/*a struct... */
	struct Variable{
	/*Data Type.*/
	std::string mLabel;
	int mValue;
	};

private:
	/*Vector of our data type*/
	std::vector<Variable> myVector;

};






#endif //SYMBOL