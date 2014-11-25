//==========================//
// EnergyBar.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENERGY_BAR_H_
#define _ENERGY_BAR_H_

#include <SFML/Graphics.hpp>

class EnergyBar
{
public:
	// Constructor
	EnergyBar(float max);

	// Methods
	void setTexture(sf::Texture *t);
	void setTextureRect(sf::IntRect rect);
	void setColor(sf::Color color);
	void setPosition(float x, float y);
	void setEnergy(float amount);
	void draw(sf::RenderWindow& window);

protected:
	sf::Texture *texture;
	sf::Sprite outline;
	sf::RectangleShape bar;
	const float MAX_ENERGY;
	float energy;
};

#endif