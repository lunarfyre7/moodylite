//crude print macro thing

#ifdef DEBUGGING
#define PRINT(thing) Serial.print(thing)
#define PRINTLN(thing) Serial.println(thing)
#define PRINT2(thing1, thing2) Serial.print(thing1); Serial.println(thing2)
#endif
#ifndef DEBUGGING 
#define PRINT(thing)
#define PRINTLN(thing)
#define PRINT2(thing1, thing2)
#endif