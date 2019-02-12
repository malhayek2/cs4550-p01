#pragma once
// #ifndef DEBUG
// #define DEBUG
/*Prop can be set tp 0 or turn on or off debugging*/
#define ShowMessages 0


#if ShowMessages
#define MSG(X) cout << X << endl;
#else 
#define MSG(X);
#endif
















// #endif // DEBUG