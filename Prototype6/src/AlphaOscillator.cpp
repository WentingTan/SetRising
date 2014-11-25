//==========================//
// AlphaOscillator.cpp      //
// Author: Matthew Stephens //
//==========================//
#include "AlphaOscillator.h"

//====================================================================================
// AlphaOscillator Constructor(int,int,float)
// Sets the upper and lower bounds for the alpha oscillation.  Sets the initial alpha
// value to the given upper bound. Sets the time of the cycle, and initializes the
// timer to 0.
//====================================================================================
AlphaOscillator::AlphaOscillator(float high, float low, float cycleTime):
	time(0.0f)
{
	// Ensure upper bound does not exceed 255
	if (high > 255.0f)
		alphaHi = 255.0f;
	else
		alphaHi = high;

	// Ensure the lower bound is non-negative
	if (low < 0.0f)
		alphaLo = 0.0f;
	else
		alphaLo = low;

	// Ensure the upper bound is not less than the lower bound
	if (alphaHi < alphaLo)
		alphaHi = alphaLo;

	// Set initial alpha value to the high value
	alpha = alphaHi;

	// Ensure the cycle time is non-negative and non-zero
	if (cycleTime <= 0.0f)
		cycle = 0.001f;
	else
		cycle = cycleTime;
}

//=========//
// Methods //
//=========//

//====================================================================================
// AlphaOscillator::update(float)
// During the first half of the cycle, the alpha value is linearly decreased from the
// given upper bound to the given lower bound. Then it is linearly increased from the
// lower to upper bound in the second half of the cycle.
//====================================================================================
void AlphaOscillator::update(float dt)
{
	time += dt;

	// Linearly decrease alpha from upper to lower bound
	if (time < 0.5f * cycle)
		alpha = alphaHi + (2.0f * (alphaLo - alphaHi) / cycle) * time;
	// Linearly increase alpha from lower to upper bound
	else if (time < cycle)
		alpha = alphaLo + (2.0f * (alphaHi - alphaLo) / cycle) * time;
	// Reset the timer
	else
		time = 0.0f;
}

//============================================================================
// AlphaOscillator::getAlpha()
// Returns the alpha value cast as a sf::Uint8 for use as the alpha component
// in a sf::Color object.
//============================================================================
sf::Uint8 AlphaOscillator::getAlpha() const
{
	return (sf::Uint8)alpha;
}

//=====================================================
// AlphaOscillator::reset()
// Resets the alpha value and timer to default values.
//=====================================================
void AlphaOscillator::reset()
{
	alpha = alphaHi;
	time = 0.0f;
}