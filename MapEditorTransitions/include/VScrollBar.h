//==========================//
// VScrollBar.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _V_SCROLL_BAR_H_
#define _V_SCROLL_BAR_H_

#include <SFML/Graphics.hpp>
#include "Input.h"

const float WIDTH = 15.0f;
const sf::Color LIGHT_GRAY(sf::Color(190,190,190));
const float SCROLL_RATE = 150.0f;

class VScrollBar
{
public:
	// Constructor
	VScrollBar(float size, float viewable, float scollLim, sf::Vector2f pos);

	float getScroll();
	bool handleInput(Input *input);
	void update(float dt);

	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape bar;
	sf::RectangleShape indicator;
	sf::RectangleShape upBox;
	sf::RectangleShape downBox;
	sf::CircleShape upArrow;
	sf::CircleShape downArrow;


	sf::FloatRect upHit;
	sf::FloatRect downHit;

	bool usable;
	bool scrollUp;
	bool scrollDown;


	sf::Vector2f pos;
	float scrollLim;
	float viewable;
	float scroll;
	float ds;
	float size;
};

#endif