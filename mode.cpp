#include "mode.h"
//MoodyLite
//file: mode.cpp
//**
//Licensed: CC0 2016, author: lunarfyre (Jake Vandereay)
//License details: https://creativecommons.org/publicdomain/zero/1.0/

 
//Mode constructors
Mode::Mode() :
		//setup defaults and inits
		isHSV(true),
		useDim(true),
		random(false),
		colorList(nullptr),
		callback(nullptr),
		pattern(nullptr)
{}
Mode::Mode(Callback cb, const RGB pat[], uint8_t plistLen) : 
		Mode()
{
	callback = cb;
	pattern = pat;
	pLen = plistLen;
}
Mode::Mode(const RGB list[], uint8_t clistLen, const RGB pat[], uint8_t plistLen) :
		Mode()
{
	colorList = list;
	pattern = pat;
	pLen = plistLen;
	cLen = clistLen;
}
bool Mode::call() {
	if (callback)//is the callback pointer null?
		(*callback)();//call the callback
	else
		return false;//
	return true;//this only get run if the above else statement is not
}
