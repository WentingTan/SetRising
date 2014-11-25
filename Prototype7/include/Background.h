//==========================//
// Background.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background
{
public:
	// Constructor
	Background() {}
	// Destructor
	~Background() {}
	
	// Mutators
	void setTexture(sf::Texture *t);
	void setScrollRatio(float r);
	void setScroll(sf::Vector2f s);
	
	// Methods
	void init();
	void setScale(int type);
	void scroll(sf::Vector2f ds);
	void draw(sf::RenderWindow& window);

protected:
	sf::Texture *texture;
	sf::Sprite sprite;
	float scrollX;
	float scrollY;
	float scrollRatio;
};

#endif