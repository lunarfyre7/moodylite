#include "rgb.h"
#include "hsv.h"

//MoodyLite
//file: rgb.h
//**
//Licenced: CC0 2016, author: lunarfyre (Jake Vandereay)
//Licence details: https://creativecommons.org/publicdomain/zero/1.0/

using namespace HSVlib;

//basic rgb data constructor
RGB::RGB(uint8_t r, uint8_t g, uint8_t b) :
		r(r),//init vars in init list
		g(g),
		b(b)
{}

HSV RGB::getHSV() {
	//same concept as getRGB but with rgb2hsv
	rgb _rgb = {r,g,b};
	hsv _hsv = rgb2hsv(_rgb);
	return HSV(_hsv.h, _hsv.s, _hsv.v);
}

//hsv constructor
HSV::HSV(uint8_t h, uint8_t s, uint8_t v) :
		h(h),
		s(s),
		v(v)
{}

RGB HSV::getRGB() {
	//convert the hsv values to rgb and return an rgb object.
	//this is just a wrapper for the code in hsv.h to make thigs prettier
	//the following are actually data types from hsv.h, not to be confused with the HSV and RGB classes
	hsv _hsv = {h, s, v};//create an hsv object for the hsv code
	rgb _rgb = hsv2rgb(_hsv);
	return RGB(_rgb.r, _rgb.g, _rgb.b); //make an RGB instance out of the data and return it
}