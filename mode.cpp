#include "mode.h"

//basic rgb data constructor
RGB::RGB(uint8_t r, uint8_t g, uint8_t b) :
		r(r),
		g(g),
		b(b)
{}
 
//Mode constructors
Mode::Mode() :
		//setup defaults and inits
		isHSY(true),
		useDim(true),
		colorList(nullptr),
		callback(nullptr)
{}
Mode::Mode(Callback<Mode> cb) : 
		Mode()
{
	callback = cb;
}
Mode::Mode(RGB *list) :
		Mode()
{
	colorList = list;
}
