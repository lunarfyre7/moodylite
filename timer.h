#ifndef GUARD_timer
#define GUARD_timer

namespace cel {
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
private:
	//FunctionPointer function;
	unsigned long lastTime;
	unsigned long interval;
	bool first;
};
}

#endif
