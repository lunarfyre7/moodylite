#include <Arduino.h>

//MoodyLite
//file: rgb.h
//**
//Licensed: CC0 2016, author: lunarfyre (Jake Vandereay)
//License details: https://creativecommons.org/publicdomain/zero/1.0/

//Defines RGB and HSV classes with member function to convern between the two.
//Serves as a wrapper for hsv.h and as a data type.

class HSV;//forward declaration
class RGB {
public:
	RGB (uint8_t=0,uint8_t=0,uint8_t=0); //populate with rgb
	uint8_t r;
	uint8_t g;
	uint8_t b;
	
	HSV getHSV(); //return the HSV equivilant 
};

class HSV {
public:
	HSV (uint8_t=0,uint8_t=0,uint8_t=0);
	uint8_t h;
	uint8_t s;
	uint8_t v;
	
	RGB getRGB(); //return the RGB equiv
};