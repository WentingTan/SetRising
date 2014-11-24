//==========================//
// AlphaOscillator.h        //
// Author: Matthew Stephens //
//==========================//
#ifndef _ALPHA_OSCILLATOR_H
#define _ALPHA_OSCILLATOR_H

#include <SFML/Graphics.hpp>

class AlphaOscillator
{
public:
	// Constructor
	AlphaOscillator(float high, float low, float cycleTime);
	// Destructor
	//~AlphaOscillator() {}

	// Methods
	void update(float dt);
	sf::Uint8 getAlpha() const;
	void reset();

private:
	float alpha;
	float alphaHi;
	float alphaLo;
	float cycle;
	float time;
};

#endif