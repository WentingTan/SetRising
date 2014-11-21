//==========================//
// VScrollBar.cpp           //
// Author: Matthew Stephens //
//==========================//

#include "VScrollBar.h"
#include <SFML/Window/Mouse.hpp>

VScrollBar::VScrollBar(float barSize, float paneSize, float maxScroll, sf::Vector2f pos):
	size(barSize),
	viewable(paneSize),
	scrollLim(maxScroll - paneSize),
	pos(pos),
	ds(0.0f),
	scroll(0.0f)
{
	// Determine if the scroll bar is usable, i.e. the area to be scrolled
	// is larger than the viewing area
	if (scrollLim <= 0.0f)
		usable = false;
	else
		usable = true;

	// Set the size, position, and color of the bar
	bar.setSize(sf::Vector2f(WIDTH, size));
	bar.setPosition(pos);
	bar.setOutlineThickness(1);
	bar.setOutlineColor(sf::Color(50, 50, 50));
	bar.setFillColor(LIGHT_GRAY);

	// Set the size, position, and color of the up box
	upBox.setSize(sf::Vector2f(WIDTH, WIDTH));
	upBox.setPosition(pos);
	upBox.setFillColor(LIGHT_GRAY);
	// Set the hitbox of the up button
	upHit.left = upBox.getPosition().x;
	upHit.top = upBox.getPosition().y;
	upHit.width = WIDTH;
	upHit.height = WIDTH;

	// Make a triangle for the upArrow
	upArrow = sf::CircleShape(0.3f * WIDTH, 3);
	// Set its position and color
	upArrow.setOrigin(upArrow.getLocalBounds().width / 2.0f, upArrow.getLocalBounds().height / 2.0f);
	upArrow.setPosition(pos.x + (WIDTH / 2.0f) - 1.0f, WIDTH / 2.0f);
	if (usable)
		upArrow.setFillColor(sf::Color(75, 75, 75));
	else
		upArrow.setFillColor(sf::Color(125, 125, 125));

	// Set the size, position, and color of the down box
	downBox.setSize(sf::Vector2f(WIDTH, WIDTH));
	downBox.setPosition(pos.x, pos.y + size - WIDTH);
	downBox.setFillColor(LIGHT_GRAY);
	// Set the hitbox of the down button
	downHit.left = downBox.getPosition().x;
	downHit.top = downBox.getPosition().y;
	downHit.width = WIDTH;
	downHit.height = WIDTH;

	// Make a triangle for the down arrow
	downArrow = sf::CircleShape(0.3f * WIDTH, 3);
	// Rotate it so it's pointing down
	downArrow.setOrigin(downArrow.getLocalBounds().width / 2.0f, downArrow.getLocalBounds().height / 2.0f);
	downArrow.rotate(180.0f);
	// Set its position and color
	downArrow.setPosition(pos.x + WIDTH / 2.0f, pos.y + size - WIDTH / 2.0f);
	if (usable)
		downArrow.setFillColor(sf::Color(75, 75, 75));
	else
		downArrow.setFillColor(sf::Color(125, 125, 125));

	// Don't bother with the position indicator if the scroll bar isn't usable
	if (usable)
	{
		// Calculate the size of the indicator bar
		float indHeight = (viewable / maxScroll) * (size - 2.0f * WIDTH);
		// Set the size, position, and color of the indicator bar
		indicator.setSize(sf::Vector2f(0.9f * WIDTH, indHeight));
		indicator.setOrigin(indicator.getLocalBounds().width / 2.0f, 0.0f);
		indicator.setPosition(pos.x + (WIDTH / 2.0f), pos.y + WIDTH);
		indicator.setFillColor(sf::Color(125, 125, 125));
	}
}




float VScrollBar::getScroll() 
{
	float t = ds;
	ds = 0.0f;
	return t;
}

bool VScrollBar::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();
	if (!bar.getGlobalBounds().contains(mousePos))
		return false;

	if (!usable)
		return true;

	scrollUp = scrollDown = false;

	if (upHit.contains(mousePos))
	{
		upBox.setFillColor(sf::Color(150, 150, 150));
		if (input->isPressed(InputNS::LEFT))
		{
			upArrow.setFillColor(sf::Color::White);
			scrollUp = true;
		}
		else
			upArrow.setFillColor(sf::Color(75,75,75));
	}
	else
		upBox.setFillColor(LIGHT_GRAY);

	if (downHit.contains(mousePos))
	{
		downBox.setFillColor(sf::Color(150, 150, 150));
		if (input->isPressed(InputNS::LEFT))
		{
			downArrow.setFillColor(sf::Color::White);
			scrollDown = true;
		}
		else
			downArrow.setFillColor(sf::Color(75,75,75));
	}
	else
		downBox.setFillColor(LIGHT_GRAY);

	return true;
}


void VScrollBar::update(float dt)
{
	if (!usable)
		return;

	ds = 0.0f;
	if (scrollUp)
		ds = -SCROLL_RATE * dt;
	else if (scrollDown)
		ds = SCROLL_RATE * dt;

	if (scroll + ds < 0.0f)
	{
		ds = -scroll;
		scroll = 0.0f;
	}
	else if (scroll + ds > scrollLim)
	{
		ds = scrollLim - scroll;
		scroll = scrollLim;
	}
	else
		scroll += ds;

	float indMove = (ds / scrollLim) * (size - 2.0f * WIDTH - indicator.getLocalBounds().height);
	indicator.move(0.0f, indMove);
}


void VScrollBar::draw(sf::RenderWindow& window)
{
	window.draw(bar);
	window.draw(upBox);
	window.draw(downBox);
	window.draw(upArrow);
	window.draw(downArrow);
	window.draw(indicator);
}