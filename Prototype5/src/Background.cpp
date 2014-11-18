//==========================//
// Background.cpp           //
// Author: Matthew Stephens //
//==========================//

#include "Background.h"
#include "Constants.h"

// Mutators
void Background::setTexture(sf::Texture *t)
{
	texture = t;
}

void Background::setScrollRatio(float r)
{
	scrollRatio = r;
}

void Background::setScroll(sf::Vector2f s)
{
	s.x *= scrollRatio;
	scrollX = s.x;
	scrollY = s.y;
}

void Background::init()
{
	sprite.setTexture(*texture);

	float scale = SCREEN_HEIGHT / sprite.getLocalBounds().height;
	sprite.setScale(scale, scale);

	scrollX = scrollY = 0.0f;
}

void Background::scroll(sf::Vector2f ds)
{
	ds *= scrollRatio;
	scrollX += ds.x;
	scrollY += ds.y;
}
	
// Methods
void Background::draw(sf::RenderWindow& window)
{
	float width = sprite.getGlobalBounds().width;
	float offsetX = scrollX - (int)(scrollX / width) * width;

	for (float x = -1.0f * offsetX; x < SCREEN_WIDTH; x+= width)
	{
		sprite.setPosition(x, 0.0f);
		window.draw(sprite);
	}
}