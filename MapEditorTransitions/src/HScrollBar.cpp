//==========================//
// HScrollBar.cpp           //
// Author: Matthew Stephens //
//==========================//

#include "HScrollBar.h"
#include <SFML/Window/Mouse.hpp>

HScrollBar::HScrollBar(float size, float viewLength, float viewLimit, sf::Vector2f pos):
	size(size),
	viewLength(viewLength),
	scrollLim(viewLimit - viewLength),
	pos(pos),
	delta(0.0f),
	scroll(0.0f)
{
	// Determine if the scroll bar is usable, i.e. the area to be scrolled
	// is larger than the viewing area
	if (scrollLim <= 0.0f)
		usable = false;
	else
		usable = true;

	// Set the size, position, and color of the bar
	bar.setSize(sf::Vector2f(size, Scroll::WIDTH));
	bar.setPosition(pos);
	bar.setOutlineThickness(1);
	bar.setOutlineColor(Scroll::OUTLINE);
	bar.setFillColor(Scroll::BAR);

	// Set the size, position, and color of the left box
	leftBox.setSize(sf::Vector2f(Scroll::WIDTH, Scroll::WIDTH));
	leftBox.setPosition(pos);
	leftBox.setFillColor(Scroll::BAR);
	// Set the hitbox of the left button
	leftHit.left = leftBox.getPosition().x;
	leftHit.top = leftBox.getPosition().y;
	leftHit.width = Scroll::WIDTH;
	leftHit.height = Scroll::WIDTH;

	// Make a triangle for the leftArrow
	leftArrow = sf::CircleShape(0.3f * Scroll::WIDTH, 3);
	// Rotate it so it's pointing left
	leftArrow.setOrigin(leftArrow.getLocalBounds().width / 2.0f, leftArrow.getLocalBounds().height / 2.0f);
	leftArrow.rotate(-90.0f);
	// Set its position and color
	leftArrow.setPosition(pos.x + (Scroll::WIDTH / 2.0f) - 1.0f, pos.y + Scroll::WIDTH / 2.0f);
	if (usable)
		leftArrow.setFillColor(Scroll::ARROW);
	else
		leftArrow.setFillColor(Scroll::ARROW_DISABLED);

	// Set the size, position, and color of the right box
	rightBox.setSize(sf::Vector2f(Scroll::WIDTH, Scroll::WIDTH));
	rightBox.setPosition(pos.x + size - Scroll::WIDTH, pos.y);
	rightBox.setFillColor(Scroll::BAR);
	// Set the hitbox of the down button
	rightHit.left = rightBox.getPosition().x;
	rightHit.top = rightBox.getPosition().y;
	rightHit.width = Scroll::WIDTH;
	rightHit.height = Scroll::WIDTH;

	// Make a triangle for the right arrow
	rightArrow = sf::CircleShape(0.3f * Scroll::WIDTH, 3);
	// Rotate it so it's pointing right
	rightArrow.setOrigin(rightArrow.getLocalBounds().width / 2.0f, rightArrow.getLocalBounds().height / 2.0f);
	rightArrow.rotate(90.0f);
	// Set its position and color
	rightArrow.setPosition(pos.x + Scroll::WIDTH / 2.0f, pos.y + size - Scroll::WIDTH / 2.0f);
	rightArrow.setPosition(pos.x + size - Scroll::WIDTH / 2.0f, pos.y + Scroll::WIDTH / 2.0f);
	if (usable)
		rightArrow.setFillColor(Scroll::ARROW);
	else
		rightArrow.setFillColor(Scroll::ARROW_DISABLED);

	// Don't bother with the position indicator if the scroll bar isn't usable
	if (usable)
	{
		// Calculate the size of the indicator bar
		float indSize = (viewLength / viewLimit) * (size - 2.0f * Scroll::WIDTH);
		// Set the size, position, and color of the indicator bar
		indicator.setSize(sf::Vector2f(indSize, 0.9f * Scroll::WIDTH));
		indicator.setOrigin(0.0f, indicator.getLocalBounds().height / 2.0f);
		indicator.setPosition(pos.x + Scroll::WIDTH, pos.y + (Scroll::WIDTH / 2.0f));
		indicator.setFillColor(Scroll::INDICATOR);
	}
}


float HScrollBar::getScroll() 
{
	return delta;
}

bool HScrollBar::handleInput(Input *input)
{
	sf::Vector2f mousePos = input->getMousePos();
	if (!bar.getGlobalBounds().contains(mousePos))
		return false;

	if (!usable)
		return true;

	scrollLeft = scrollRight = false;

	if (leftHit.contains(mousePos))
	{
		leftBox.setFillColor(Scroll::BOX_MOUSE);
		if (input->isPressed(InputNS::LEFT))
		{
			leftArrow.setFillColor(Scroll::ARROW_CLICK);
			scrollLeft = true;
		}
		else
			leftArrow.setFillColor(Scroll::ARROW);
	}
	else
	{
		leftBox.setFillColor(Scroll::BAR);
		leftArrow.setFillColor(Scroll::ARROW);
	}

	if (rightHit.contains(mousePos))
	{
		rightBox.setFillColor(Scroll::BOX_MOUSE);
		if (input->isPressed(InputNS::LEFT))
		{
			rightArrow.setFillColor(Scroll::ARROW_CLICK);
			scrollRight = true;
		}
		else
			rightArrow.setFillColor(Scroll::ARROW);

	}
	else
	{
		rightBox.setFillColor(Scroll::BAR);
		rightArrow.setFillColor(Scroll::ARROW);
	}

	return true;
}


void HScrollBar::update(float dt)
{
	if (!usable)
		return;

	delta = 0.0f;
	if (scrollLeft)
		delta = -Scroll::SPEED * dt;
	else if (scrollRight)
		delta = Scroll::SPEED * dt;

	if (scroll + delta < 0.0f)
	{
		delta = -scroll;
		scroll = 0.0f;
	}
	else if (scroll + delta > scrollLim)
	{
		delta = scrollLim - scroll;
		scroll = scrollLim;
	}
	else
		scroll += delta;

	float indMove = (delta / scrollLim) * (size - 2.0f * Scroll::WIDTH - indicator.getLocalBounds().width);
	indicator.move(indMove, 0.0f);
}


void HScrollBar::draw(sf::RenderWindow& window)
{
	window.draw(bar);
	window.draw(leftBox);
	window.draw(rightBox);
	window.draw(leftArrow);
	window.draw(rightArrow);
	window.draw(indicator);
}