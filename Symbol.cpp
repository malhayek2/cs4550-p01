#include <Symbol.h>


SymbolTableClass::SymbolTableClass(){
	/*Nothing really */
}

bool SymbolTableClass::Exists(const std::string &s){
	// returns true if &lt;s&gt; is already in the symbol table.
	for (unsigned int i =0; i < this->myVector.size() ; i++){
		/*if the value matchs given string then return*/
		if(this->myVector[i].mLabel == s ){
			return true;
		}
	}
	return false;
}

void SymbolTableClass::AddEntry (const std::string &s){
	// adds &lt;s&gt; to the symbol table,
	// or quits if it was already there
	if(Exists(s)){
		MSG("The given entry already exists in the SymbolTable.");
		return;
	}

	Variable newEntry;
	/*what is our value key?*/
	newEntry.mLabel = s;
	newEntry.mValue = 0;
	this->myVector.push_back(newEntry); 


}
/*So i think this takes an mLabel*/
int SymbolTableClass::GetValue (const std::string &s){
	// returns the current value of variable &lt;s&gt;, when
	// interpreting. Meaningless for Coding and Executing.
	// Prints a message and quits if variable s does not exist.
	for (unsigned int i = 0; i < this->myVector.size(); i++){
		if(this->myVector[i].mLabel == s){
			return this->myVector.mValue; 
		}
	}
	MSG("Could not find Value of mlabel" + s);


}

void SymbolTableClass::SetValue(const std::string &amp; s, int v){
// sets variable &lt;s&gt; to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
	for(unsigned int i = 0; i < this->myVector.size(); i ++){
		if(this->myVector[i].mLabel == s ){
			this->myVector[i].mValue = v;
			return;			
		}
	}
	MSG("Could not assign " + s + "with value " + v);


}
	// returns the index of where variable &lt;s&gt; is.
	// returns -1 if variable &lt;s&gt; is not there.
int SymbolTableClass::GetIndex(const std::string &s){

	for (unsigned iint i = 0 ; i < this->myVector.size(); i++){
		if(this->myVector[i].mLabel == s){
			return i;
		}
	}
	MSG("Could not find index of " + s );

}
int SymbolTableClass::GetCount(){
	// returns the current number of variables in the symbol
	// table.
	return this->myVector.size();

}