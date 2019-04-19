#include "instructions.h"
#include <iostream>

/*Testing*/
/*Test your code up to this point by declaring a variable of type InstructionsClass,
 calling the Finish method, and calling the Execute method.
  Do this in InstructionsTester.cpp. 
 When running your code,
 it should jump into your machine code array (which does nothing at this point),
 and then return back to your testing code. 
 Print something to make sure it really returned. 
 Note that if you get this wrong, or any other machine code you write, you may have to reboot your computer to recover!*/
int main(){
	InstructionsClass ic;
	ic.Finish();
	ic.Execute();
	std::cout << "Finished" << std::endl;
	return 0;
}