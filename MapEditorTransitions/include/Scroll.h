//==========================//
// Scroll.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _SCROLL_H_
#define _SCROLL_H_

#include <SFML/Graphics.hpp>
#include "Input.h"

namespace Scroll
{
	const float WIDTH = 15.0f;
	const float SPEED = 500.0f;

	const sf::Color BAR(sf::Color(190, 190, 190));
	const sf::Color OUTLINE(sf::Color(50, 50, 50));
	const sf::Color BOX_MOUSE(sf::Color(150, 150, 150));
	const sf::Color ARROW(sf::Color(75, 75, 75));
	const sf::Color ARROW_DISABLED(sf::Color(125, 125, 125));
	const sf::Color ARROW_CLICK(sf::Color::White);
	const sf::Color INDICATOR(sf::Color(125, 125, 125));
}

#endif