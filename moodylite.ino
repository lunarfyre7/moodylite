#include "timer.h"
#include "mode.h"
#include "hsv.h"
#include "wheel.h"

//MoodyLite
//file: moodylite.ino
//**
//Licenced: CC0 2016, author: lunarfyre (Jake Vandereay)
//Licence details: https://creativecommons.org/publicdomain/zero/1.0/
//Functions and algorithms sourced from elsewhere are implied to be public domain, however credit is still
//given in the relivent files, the CC0 licenced is not meant to be applied to those.
//**
//MoodyLite is a moodlight program for Arduino that is somewhat modular in it's configuration
//and should be easily extensible. It comes with several modes pre coded.
//Main color effects: HSV fading, color wheel rotations, linear fading, arbitrary functions.
//
//I have also tried to heavily comment this code so that hopefully it is more useful to those 
//reading it (also for people new to C++ hopefully). Most of the things that are relivant to 
//tweaking should be in this file, but you may want to look at the others for comments on what does what.
//
//[write more stuff here later]

///***IMPORTANT***///
//To make this code compile for attiny85 you need the attiny85 core here https://code.google.com/p/arduino-tiny/
//Also you need to use ide version 1.6.5 at the latest, newer versions are not compatible with the tiny core
//One more gotcha, if you use 1.6.5 or older you need to add " -std=gnu++11" (without quotes ofc) to the 
//"compiler.cpp.flags" line in platforms.txt found BOTH the normal Arduino core /and/ the tiny core you added.

//MoodyLite config
//
//This is where you can change which board you build for,
//and where you can tweak and add color modes.
//
namespace CFG {
//**BOARD CONFIG**//
	// #define TYPE_ATTINY85 //uncomment for attiny85 build target
	#define TYPE_UNO //uncomment for uno build target
	const bool IS_SOURCE = false; //false: current sink, true: current source


	#ifdef TYPE_UNO
		//uno pin config
		const byte RPIN = 3;
		const byte GPIN = 5;
		const byte BPIN = 6;
		const byte BTN1 = 8;
		const byte BTN2 = 9;
		const byte RANDPIN = A0;//analog pin for randomness
	#endif

	#ifdef TYPE_ATTINY85 //for attiny85
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
	//mode 1 (just something to fill space atm)
	RGB colors1[] = {red,green,blue,white, RGB(0,150,100)};//the colors to be cycled through go here
	RGB pattern1[] = {blue, blue, green};//the pattern played when this mode is selected is set here
	Mode mode1(colors1, pattern1);//create an instance of Mode for this mode
	
	//mode2 example using a callback
	
	void callback2() {
		//a callback to directly manupulate the colors
	}
	RGB pattern2[] = {blue, blue, red};
	Mode mode2(callback2, pattern2);//passing the function instead of a color list as the 1st arg


	//add modes to the mode list
	Mode *modelist[] = {&mode1};
	
//**OTHER SETTINGS**//
	void modeSetup() {
		//include setup code here that cannot be done outside of a function
		//this is only here to avoid having super long constructor argument lists
		
		//let's set mode one as HSV fading and random
		mode1.isHSV = true;
		mode1.random = true;
	}
	const unsigned long interval = 5000; //the interval of color change, the time it takes to fade from one color to the next
	
//**END CONFIG**//
};
namespace Moody {
	RGB oldColor;//if fading from A to B this would be A
	RGB nextColor;//and this B
	RGB activeColor;//this would be the current state that is shown and is the point that moves from A to B
	Mode *activeMode = nullptr;
	Timer animT;//the timer for the main animation function
	RGB *activeColorList; //the active color list from the active mode
	uint8_t currentMode = 0; //the current mode index
	uint8_t currentColor = 0; //the current colot index (note current here is used for indexes and active is used for pointers)
	
	//forward declarations
	void getNextColor();//get next color forom color list
	void setOutputColor(RGB);//set the argument color as the pwn output to the actual lights
	void linearFade();
	void hsvFade();
	int getRand();//return a random number

	
	void anim_init() {
		//setup code for anim here
		animT.SetInterval(CFG::interval);//tell the timer what interval we are using
		activeMode = CFG::modelist[currentMode];//get a pointer to the first mode and make it the active mode
		CFG::modeSetup();//run the init function for the modes
	}
	void anim_tick() {
		//color differences
		int diff_r;
		int diff_g;
		int diff_b;
		//check if there is a callback defined and run it if it is
		if(activeMode->call()) //ask the Mode to call its callback
			return; //skip the rest if the mode returns true indicating that it did indeed call the callback
		//this handles the default animation
		if (animT.Time() < CFG::interval) {//animate from color a to b
			if (activeMode->isHSV) {//do we want to use HSV rotation or linear fading?
				hsvFade();
			} else {
				linearFade();
			}
		}
		else {
			oldColor = nextColor; //save the old color
			//nextColor = //USE A THING TO GET nextColor HERE
			animT.Reset();//reset the timer
		}
	}
	
	void linearFade() {
		//linear fading mode
		//get the color differences
		int diff_r = nextColor.r - oldColor.r;
		int diff_g = nextColor.g - oldColor.g;
		int diff_b = nextColor.b - oldColor.b;
		//Mix the colors according to the current progression of the transition
		activeColor.r = oldColor.r + diff_r * animT.Progress();
		activeColor.g = oldColor.g + diff_g * animT.Progress();
		activeColor.b = oldColor.b + diff_b * animT.Progress();
	}
	void hsvFade() {
		//fades by rotating the hue and adjusting saturation and lightness to transition
	}
	
	//mode list functions
	void getNextColor() {//get next color forom color list
		RGB *clist = activeMode->colorList;//get pointer to the colot list (for cleaner syntax)
		uint8_t len = sizeof(clist)/sizeof(clist[0]);//length of the color array in C style
		
		if (len == 1) //if there is only one color abort
			return;
		if (activeMode->random) {//check if the next color should be random or not
			activeColor = getRand() % (len-1);//get random number, and limit it with modulo length - 1 to keep it in bounds
		} 
		else //simply go to the next color if random is turned off
			if (++currentColor <= len) //increment activeColor and check if it is out of bounds
				activeColor = 0;//reset if it is
	}
	int getRand () {
		//return a random number
		return analogRead(CFG::RANDPIN);//analog pin 'static' method of getting a random number
		//an alternative is creating a random number based on running time [millis()]
		//maybe add a LFSR random gen
	}

}

void setup() {
	Moody::anim_init();
}

void loop() {
	Moody::anim_tick();
}