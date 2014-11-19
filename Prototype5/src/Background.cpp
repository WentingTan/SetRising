//==========================//
// Background.cpp           //
// Author: Matthew Stephens //
//==========================//

#include "Background.h"
#include "Constants.h"
#include <fstream>
// Mutators
void Background::setTexture(sf::Texture *t)
{
	texture = t;
}

void Background::setScrollRatio(float r)
{
	scrollRatio = r;
}

void Background::setScale(int type)
{
	float scale;
	switch (type)
	{
	case SCALE_TO_HEIGHT:
		scale = SCREEN_HEIGHT / sprite.getLocalBounds().height;
		break;
	case SCALE_TO_WIDTH:
		scale = SCREEN_WIDTH / sprite.getLocalBounds().width;
		break;
	case NO_SCALE:
		scale = 1.0f;
	default:
		break;
	}

	sprite.setScale(scale, scale);
}

void Background::setScroll(sf::Vector2f s)
{
	s.x *= scrollRatio;
	s.y *= scrollRatio;
	scrollX = s.x;
	scrollY = s.y;

	std::ofstream log("log.txt", std::ios::app);
	log << "In Background::setScroll(): scroll = " << s.x << ", " << s.y << std::endl;
	log.close();
}

void Background::init()
{
	sprite.setTexture(*texture);
	scrollX = scrollY = (float)TILE_SIZE;
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
	sf::FloatRect bounds = sprite.getGlobalBounds();
	float offsetX = scrollX - scrollRatio * (float)TILE_SIZE - (int)(scrollX / bounds.width) * bounds.width;
	float offsetY = scrollY - scrollRatio * (float)TILE_SIZE - (int)(scrollY / bounds.height) * bounds.height;

	//float offsetX = scrollX  - (int)(scrollX / bounds.width) * bounds.width;
	//float offsetY = scrollY - (int)(scrollY / bounds.height) * bounds.height;

	for (float y = -1.0f * offsetY; y < SCREEN_HEIGHT; y+= bounds.height)
	{
		for (float x = -1.0f * offsetX; x < SCREEN_WIDTH; x+= bounds.width)
		{
			sprite.setPosition(x, y);
			//sprite.setPosition(x, 0.0f);
			window.draw(sprite);
		}
	}
}