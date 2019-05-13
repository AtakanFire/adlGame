#ifndef EasingFunctions_h__
#define EasingFunctions_h__

#include "game/GameGeneric/GameGenericTypedef.h"

class EasingFunctions { 

public:


	// Basic

	static float linear(float t) { return t; };

	static float easeInQuad(float t) { return t * t; };
	static float easeOutQuad(float t) { return t * (2 - t); };
	static float easeInOutQuad(float t) { return t < .5 ? 2 * t*t : -1 + (4 - 2 * t)*t; };

	static float easeInCubic(float t) { return t * t*t; };
	static float easeOutCubic(float t) { return (--t)*t*t + 1; };
	static float easeInOutCubic(float t) { return t < .5 ? 4 * t*t*t : (t - 1)*(2 * t - 2)*(2 * t - 2) + 1; };

	static float easeInQuart(float t) { return t * t*t*t; };
	static float easeOutQuart(float t) { return 1 - (--t)*t*t*t; };
	static float easeInOutQuart(float t) { return t < .5 ? 8 * t*t*t*t : 1 - 8 * (--t)*t*t*t; };
	
	static float easeInQuint(float t) { return t * t*t*t*t; };
	static float easeOutQuint(float t) { return 1 + (--t)*t*t*t*t; };
	static float easeInOutQuint(float t) { return t < .5 ? 16 * t*t*t*t*t : 1 + 16 * (--t)*t*t*t*t; };
	

	static float easeInElastic(float t) { return (.04 - .04 / t) * std::sin(25 * t) + 1; };
	static float easeOutElastic(float t) { return .04 * t / (--t) * std::sin(25 * t); };
	static float easeInOutElastic(float t) { return (t -= .5) < 0 ? (.02 + .01 / t) * std::sin(50 * t) : (.02 - .01 / t) * std::sin(50 * t) + 1; };

	// Advenced 
	// Time, Start, Change, Duration
	// No need for now

private:

};

#endif //EasingFunctions_h__
