#ifndef GUARD_timer
#define GUARD_timer
//MoodyLite
//file: timer.h
//**
//Licenced: CC0 2016, author: lunarfyre (Jake Vandereay)
//Licence details: https://creativecommons.org/publicdomain/zero/1.0/

//timer class, taken from another project of mine, this would be better as a tiny library
class Timer {
public:
	Timer();
	Timer SetInterval(unsigned long);//set the interval for the timer length
	Timer Reset();//resets the timer
	bool CheckInterval();//checks the interval set by SetInterval
	bool Check(unsigned long);
	bool Every(unsigned long);//true every x amount of time
	bool StaticCheck(unsigned long time);//checks if time has elapsed since last reset
	bool First(); //is this the first check? It returns true only once.
	//added for moodlight
	float Progress();//returns the ratio of time elapsed until the next reset in the range of 0-1
	unsigned long Time();//returns time since last reset
private:
	//FunctionPointer function;
	unsigned long lastTime;
	unsigned long interval;
	bool first;
};

#endif
