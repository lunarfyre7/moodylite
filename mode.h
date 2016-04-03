#pragma once
#include <arduino.h>
#include "rgb.h"
//MoodyLite
//file: mode.h
//**
//Licensed: CC0 2016, author: lunarfyre (Jake Vandereay)
//License details: https://creativecommons.org/publicdomain/zero/1.0/

//Defines mode object for creating modes


typedef void (*Callback)(); //define a pointer type for passing callbacks
 

//Mode class, instances of these define the properties of each mode added to the program
class Mode {
public:
	//           		  VV the 2nd arg is for the pattern, and is optional 
	//                    VV                                   VV you must also pass the length of the list
	Mode(Callback, const RGB patternlist[] = nullptr, uint8_t =0); //if the mode is based on a function, i/e/, for more complecated effects
	Mode(const RGB colorlist[], uint8_t clistLen, const RGB patternlist[] = nullptr, uint8_t plistLen=0); //if the mode is based on a list of colors
	Mode(); //Init with no params
	
	//public vars meant to be messed with in the config
	const RGB *pattern; // the pattern shown when the mode is first selected
	bool isHSV; // Use HSL color transitioning, true by default
	bool useDim; // Apply dimming level, true by default
	bool random; //cycle randomly, default false;
	
	//less useful for the config area
	const RGB *colorList;
	uint8_t cLen;//length of color array
	uint8_t pLen;//length of pattern array
	//helpers
	bool call(); //call the callback if there is one, returns true if there is a callback.
private:
	Callback callback;//the callback
};