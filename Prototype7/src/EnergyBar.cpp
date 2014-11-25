//==========================//
// EnergyBar.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "EnergyBar.h"
#include "Constants.h"

//===========================================================================
// EnergyBar Constructor(float)
// Sets the starting amount and maximum amount of energy for the energy bar.
//===========================================================================
EnergyBar::EnergyBar(float max):
	MAX_ENERGY(max),
	energy(max)
{
	// Do nothing
}

//==============================================
// EnergyBar::setTexture(sf::Texture*)
// Sets the texture for the energy bar outline.
//==============================================
void EnergyBar::setTexture(sf::Texture *t)
{
	outline.setTexture(*t);
}

//================================================================================
// EnergyBar::setTextureRect(sf::IntRect)
// Sets the texture rect for the energy bar outline sprite.  Sets the size of the
// energy bar based on the outline size.
//================================================================================
void EnergyBar::setTextureRect(sf::IntRect rect)
{
	outline.setTextureRect(rect);
	bar.setSize(sf::Vector2f((float)rect.width - 2.0f * EB_OFFSET, (float)rect.height - 2.0f * EB_OFFSET));
}

//===================================
// EnergyBar::setColor(sf::Color)
// Sets the color of the energy bar.
//===================================
void EnergyBar::setColor(sf::Color color)
{
	bar.setFillColor(color);
}

//=======================================================
// EnergyBar::setPosition(float,float)
// Sets the positions of the energy bar and its outline.
//=======================================================
void EnergyBar::setPosition(float x, float y)
{
	outline.setPosition(x, y);
	bar.setPosition(x + EB_OFFSET, y + EB_OFFSET);
}


//==================================================================
// EnergyBar::setEnergy(float)
// Sets the energy to the given amount. Clamps at 0 and MAX_ENERGY.
//==================================================================
void EnergyBar::setEnergy(float amount)
{
	if (amount < 0.0f)
		energy = 0.0f;
	else if (amount > MAX_ENERGY)
		energy = MAX_ENERGY;
	else
		energy = amount;
}

//=================================================================================
// EnergyBar::draw(sf::RenderWindow&)
// Draws the EnergyBar to the screen. First draws the outline of the bar, and then
// scales and draws the rectangle shape for the energy bar.
//=================================================================================
void EnergyBar::draw(sf::RenderWindow& window)
{
	float scale = energy / MAX_ENERGY;
	bar.setScale(scale, 1.0f);

	window.draw(outline);
	window.draw(bar);
}
