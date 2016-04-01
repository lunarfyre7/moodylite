#pragma once
#include <arduino.h>

//color datatype
struct RGB {
	RGB (uint8_t,uint8_t,uint8_t); //populate with rgb
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

template<typename T>
using Callback = void (*)(T&);//callback template
 

//Mode class, instances of these define the properties of each mode added to the program
class Mode {
public:
	Mode(Callback<Mode>); //if the mode is based on a function, i/e/, for more complecated effects
	Mode(RGB *); //if the mode is based on a list of colors
	Mode(); //Init with no params
	
	//public vars meant to be messed with
	bool isHSY; // Use HSL color transitioning, true by default
	bool useDim; // Apply dimming level, true by default
	
	//less public variables that are still public but are less useful for config
	RGB *colorList;
	//helpers
	void Call(); //call the callback if there is one
private:
	Callback<Mode> callback;//the callback
};