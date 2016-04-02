#pragma once
#include <arduino.h>
//MoodyLite
//file: mode.h
//**
//Licenced: CC0 2016, author: lunarfyre (Jake Vandereay)
//Licence details: https://creativecommons.org/publicdomain/zero/1.0/

//color datatype
struct RGB {
	RGB (uint8_t=0,uint8_t=0,uint8_t=0); //populate with rgb
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

typedef void (*Callback)(); //define a pointer type for passing callbacks
 

//Mode class, instances of these define the properties of each mode added to the program
class Mode {
public:
	//           		  VV the 2nd arg is for the pattern, and is optional 
	Mode(Callback, RGB * = nullptr); //if the mode is based on a function, i/e/, for more complecated effects
	Mode(RGB *, RGB * = nullptr); //if the mode is based on a list of colors
	Mode(); //Init with no params
	
	//public vars meant to be messed with in the config
	RGB *pattern; // the pattern shown when the mode is first selected
	bool isHSV; // Use HSL color transitioning, true by default
	bool useDim; // Apply dimming level, true by default
	bool random; //cycle randomly, default false;
	
	//less useful for the config area
	RGB *colorList;
	//helpers
	bool call(); //call the callback if there is one, returns true if there is a callback.
private:
	Callback callback;//the callback
};