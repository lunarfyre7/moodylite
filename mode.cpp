#include "mode.h"
//MoodyLite
//file: mode.cpp
//**
//Licenced: CC0 2016, author: lunarfyre (Jake Vandereay)
//Licence details: https://creativecommons.org/publicdomain/zero/1.0/

 
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
Mode::Mode(Callback cb, const RGB *pat) : 
		Mode()
{
	callback = cb;
	pattern = pat;
}
Mode::Mode(const RGB *list, const RGB *pat) :
		Mode()
{
	colorList = list;
	pattern = pat;
}
bool Mode::call() {
	if (callback)//is the callback pointer null?
		(*callback)();//call the callback
	else
		return false;//
	return true;//this only get run if the above else statement is not
}
