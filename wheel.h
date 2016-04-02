#include "mode.h"
//color utilities from the old program
RGB wheel(float base, float frequency1, float frequency2, float frequency3,
	float phase1, float phase2, float phase3,
	uint8_t center, uint8_t width) {
			//color wheel thing from http://krazydad.com/tutorials/makecolors.php
	byte R = (sin(frequency1*base + phase1) * width + center);
	byte G = (sin(frequency2*base + phase2) * width + center);
	byte B = (sin(frequency3*base + phase3) * width + center);
	return RGB(R,G,B);
}
RGB wheel(float base, float freq1, float freq2, float freq3, float phase1, float phase2, float phase3) {
	return wheel(base, freq1, freq2, freq3, phase1, phase2, phase3, 128, 127);
}
RGB wheel(float base, float freq) {
	return wheel(base, freq, freq, freq, 0, 2, 4, 128, 127);
}
RGB wheel(float base) {
	return wheel(base, 0.3, 0.3, 0.3, 0, 2, 4, 128, 127);
}
RGB fauxHSB(uint8_t h, uint8_t s, uint8_t b) {//sort of not-quite HSB made with the color wheel
	b = 255 - b;
	int width = s/2;
	int center = 128;
	float _h = 2*PI*(h/255);
	return wheel(_h, 1, 1, 1, 2, 4, 6, center, width);
}