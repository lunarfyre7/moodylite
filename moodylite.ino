#include "timer.h"
#include "mode.h"

//**BOARD CONFIG**//


// #define TYPE_ATTINY //uncomment for attiny build target
#define TYPE_UNO //uncomment for uno build target


#ifdef TYPE_UNO
	//uno pin config
	const byte RPIN = 2;//todo, decide on wiring (this is dummy conf atm)
	const byte GPIN = 3;
	const byte BPIN = 4;
	const byte BTN1 = 5;
	const byte BTN2 = 6;
#endif

#ifdef TYPE_ATTINY
	//attiny pin config
	const byte RPIN = 2;//todo, decide on wiring (this is dummy conf atm)
	const byte GPIN = 3;
	const byte BPIN = 4;
	const byte BTN1 = 5;
	const byte BTN2 = 6;
#endif

//**COLORS**//
const RGB white = {255,255,255};
const RGB red = {255,0,0};
const RGB green = {0,255,0};
const RGB blue = {0,0,255};
//add more here later

//**MODE CONFIG**//
//pin stuff here later
//mode 1
RGB colors1[] = {red,green,blue,white, RGB(0,150,100)};
Mode mode1(colors1);

//add modes to list here

//add modes to the mode list
Mode MODELIST[] = {mode1};
//**END CONFIG**//



void setup() {
}

void loop() {}
