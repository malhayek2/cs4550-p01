#pragma once
// #ifndef DEBUG
// #define DEBUG
/*Prop can be set tp 0 or turn on or off debugging*/
#define ShowMessages 1


#if ShowMessages
#define MSG(X) std::cout << X << std::endl;
#else 
#define MSG(X);
#endif
















// #endif // DEBUG