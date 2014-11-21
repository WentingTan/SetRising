//==========================//
// HScrollBar.h             //
// Author: Matthew Stephens //
//==========================//
#ifndef _H_SCROLL_BAR_H_
#define _H_SCROLL_BAR_H_

#include "Scroll.h"

class HScrollBar
{
public:
	// Constructor
	HScrollBar(float size, float viewLength, float viewLimit, sf::Vector2f pos);

	float getScroll();
	bool handleInput(Input *input);
	void update(float dt);

	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape bar;
	sf::RectangleShape indicator;
	sf::RectangleShape leftBox;
	sf::RectangleShape rightBox;
	sf::CircleShape leftArrow;
	sf::CircleShape rightArrow;

	sf::FloatRect leftHit;
	sf::FloatRect rightHit;

	bool usable;
	bool scrollLeft;
	bool scrollRight;


	sf::Vector2f pos;
	float scrollLim;
	float viewLength;
	float scroll;
	float delta;
	float size;
};

#endif