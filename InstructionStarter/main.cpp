#include <iostream>

int main()
{
unsigned char mCode[] = {0x55, 0x8B, 0xEC, 0X5d, 0XC3};
std::cout << "About to Execute the machine code.." << std::endl;
void * ptr = mCode;
void (*f)(void);
f = (void (*)(void)) ptr ;
f(); // call the array as if it were a function
std::cout << "There and back again" << std::endl;
return 0;
}