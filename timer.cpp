#include "timer.h"
#include "arduino.h" //used for millis(), should be replace with something else

using namespace cel;

Timer::Timer()
	:lastTime(millis())
	,interval(0)
	,first(true)
{
	// lastTime = millis();
	// interval = 0;
	// first = true;
}
Timer Timer::SetInterval(unsigned long interval) {
	this->interval = interval;
	return *this;
}
Timer Timer::Reset() {
	lastTime = millis();
	return *this;
}
bool Timer::CheckInterval() {
	return Check(interval);
}
bool Timer::Check(unsigned long time) {
	bool isGo = false;
	first = false;

	isGo = lastTime + time < millis();
	if (isGo) {
		lastTime = millis();
	}
	return isGo;
}
bool Timer::Every(unsigned long time) {
	return First() || Check(time);
}
bool Timer::StaticCheck(unsigned long time) {
	//first = false;//should this be here?
	return lastTime + time < millis();
}
bool Timer::First() {
	bool val = first;
	first = false;
	return val;
}
