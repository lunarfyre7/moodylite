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
//I have also tried to heavily comment this code so that hopefully it is more useful to those reading it.
//
//[write more stuff here later]

//MoodyLite config
//
//This is where you can change which board you build for,
//and where you can tweak and add color modes.
//
namespace CFG {
//**BOARD CONFIG**//
	// #define TYPE_ATTINY //uncomment for attiny build target
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
	//mode 1 (just something to fill space atm)
	RGB colors1[] = {red,green,blue,white, RGB(0,150,100)};//the colors to be cycled through go here
	RGB pattern1[] = {blue, blue, green};//the pattern played when this mode is selected is set here
	Mode mode1(colors1, pattern1);//create an instance of Mode for this mode
	
	//mode2 example using a callback
	
	void callback1() {
		//a callback to directly manupulate the colors
		
	}


	//add modes to the mode list
	Mode &modelist[] = {mode1};
	
//**OTHER SETTINGS**//
	void modeSetup() {
		//include setup code here that cannot be done outside of a function
		//this is only here to avoid having super long constructor argument lists
		
		
	}
	const unsigned long interval = 5000; //the interval of color change, the time it takes to fade from one color to the next
	
//**END CONFIG**//
};
namespace Moody {
	RGB oldColor();//if fading from A to B this would be A
	RGB nextColor();//and this B
	RGB activeColor();//this would be the current state that is shown and is the point that moves from A to B
	Mode *activeMode = nullptr;
	Timer animT();//the timer for the main animation function
	RGB *currentColorList; //the active color list from the active mode
	uint8_t currentMode; //the current mode index
	
	//forward declarations
	void getNextColor();//get next color forom color list
	void setOutputColor(RGB);//set the argument color as the pwn output to the actual lights
	void linearFade();
	void hsvFade();
	int getRand();//return a random number

	
	void anim_init() {
		//setup code for anim here
		animT.SetInterval(interval);//tell the timer what interval we are using
		currentMode = 0;//start at 0
		activeMode = &CFG::modelist[currentMode];//get a pointer to the first mode and make it the active mode
		CFG::modeSetup();//run the init function for the modes
	}
	void anim_tick() {
		//color differences
		int diff_r;
		int diff_g;
		int diff_b;
		//check if there is a callback defined and run it if it is
		if(activeMode->callback != nullptr) {
			activeMode->call();//ask the Mode to call its callback
			return; //skip the rest
		}
		//this handles the default animation
		if (animT.StaticCheck() < interval) {//animate from color a to b
			if (activeMode->useHSV) {//do we want to use HSV rotation or linear fading?
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
		diff_r = newColor.r - oldColor.r;
		diff_g = newColor.g - oldColor.g;
		diff_b = newColor.b - oldColor.b;
		//Mix the colors according to the current progression of the transition
		currentColor.r = oldColor.r + diff_r * animT.progress();
		currentColor.g = oldColor.g + diff_g * animT.progress();
		currentColor.b = oldColor.b + diff_b * animT.progress();

	}
	void hsvFade() {
		//fades by rotating the hue and adjusting saturation and lightness to transition
	}
	
	//mode list functions
	void getNextColor() {//get next color forom color list
		RGB *clist = activeMode->colorlist;//get pointer to the colot list (for cleaner syntax)
		uint8_t len = sizeof(clist)/sizeof(clist[0]);//length of the color array in C style
		
		if (len == 1) //if there is only one color abort
			return;
		if (activeMode->random) {//check if the next color should be random or not
			currentColor = getRand() % (len-1);//get random number, and limit it with modulo length - 1 to keep it in bounds
		} 
		else //simply go to the next color if random is turned off
			if (++currentColor <= len) //increment currentColor and check if it is out of bounds
				currentColor = 0;//reset if it is
			
	}
	int getRand () {
		//return a random number
		return analogRead(RANDPIN);//analog pin 'static' method of getting a random number
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
