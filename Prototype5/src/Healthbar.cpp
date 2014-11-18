//==========================//
// Healthbar.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "Healthbar.h"
#include "EventManager.h"

//=================================================================================
// HBPlayerHitHandler::handleEvent(Event::Data)
// Handles Event::PLAYER_HIT by calling Healthbar::adjustBy() through its internal
// Healthbar pointer, passing the amount of damage done.
//=================================================================================
void HBPlayerHitHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::PLAYER_HIT)
		pHB->adjustBy(-1 * e.damage);
}

//=================================================================================
// HBPlayerHealHandler::handleEvent(Event::Data)
// Handles Event::PLAYER_HEAL by calling Healthbar::adjustBy() through its internal
// Healthbar pointer, passing the amount of health gained.
//=================================================================================
void HBPlayerHealHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::PLAYER_HEAL)
		pHB->adjustBy(e.health);
}


//==========================================================================
// Healthbar Constructor(int, int)
// Sets the starting amount and maximum amount of health for the Healthbar.
//==========================================================================
Healthbar::Healthbar(int start, int max):
	MAX_HEALTH(max),
	health(start)
{
	// Do nothing
}

//=============================================
// Healthbar::setTexture(sf::Texture*)
// Sets the texture pointer for the Healthbar.
//=============================================
void Healthbar::setTexture(sf::Texture *t)
{
	texture = t;
}

//====================================================================================
// Healthbar::init()
// Sets the texture and texture rects for the bar and seg sprites.  Positions the bar
// on the screen.
//====================================================================================
void Healthbar::init()
{
	// Set the texture for the bar and seg sprites
	bar.setTexture(*texture);
	//seg.setTexture(*texture);

	// Set the texture rects for the sprites
	bar.setTextureRect(Health::BAR_RECT);
	//seg.setTextureRect(Health::SEG_RECT);
	
	seg.setFillColor(sf::Color::Red);

	// Position the Healthbar
	bar.setPosition(Health::POS);

	// Register EventHandlers
	hitHandler = new HBPlayerHitHandler(this);
	healHandler = new HBPlayerHealHandler(this);
	EventManager::addHandler(Event::PLAYER_HIT, hitHandler);
	EventManager::addHandler(Event::PLAYER_HEAL, healHandler);
}

//===================================================================================
// Healthbar::adjustBy(int)
// Adjusts the health by the given amount.  Ensures the value of health remains non-
// negative and does not exceed the maximum amount of health.
//===================================================================================
void Healthbar::adjustBy(int amount)
{
	health += amount;

	if (health < 0)
		health = 0;
	else if (health > MAX_HEALTH)
		health = MAX_HEALTH;
}

//====================================================================================
// Healthbar::draw(sf::RenderWindow&)
// Draws the Healthbar to the screen. First draws the background of the bar, and then
// positions and draws a health segment for each point of health remaining.
//====================================================================================
void Healthbar::draw(sf::RenderWindow& window)
{

	
	float scale = bar.getLocalBounds().width / bar.getGlobalBounds().width;
	float offset = Health::OFFSET * scale;

	sf::Vector2f segSize;
	segSize.x = bar.getGlobalBounds().width - 2.0f * offset;
	segSize.y = 0.5f * bar.getGlobalBounds().height;
	float ratio = (float)health / (float)MAX_HEALTH;

	segSize.x *= ratio;

	sf::Vector2f pos = bar.getPosition();
	seg.setPosition(pos.x + offset, pos.y + offset);

	seg.setSize(segSize);
	window.draw(bar);
	window.draw(seg);
	

	//sf::Vector2f segSize;
	//segSize.y = 0.5f * bar.getGlobalBounds().height;



	//segSize.x = (bar.getGlobalBounds().width - 2.0f * offset) / (1.5f * (float)MAX_HEALTH);
	//space = 0.5f * segSize.x;

	//seg.setSize(segSize);
	//seg.setFillColor(sf::Color::Red);
	
	/*

	sf::Vector2f segPos;
	sf::Vector2f pos = bar.getPosition();
	float ratio = bar.getLocalBounds().width / bar.getGlobalBounds().width;
	float offset = Health::OFFSET * ratio;
	float space = Health::SPACE * ratio;
	segPos.y = pos.y + offset;

	float segWidth = seg.getGlobalBounds().width;

	window.draw(bar);

	for (int i = 0; i < health; i++)
	{

		// Position and draw the health segment
		segPos.x = pos.x + offset + i * (segWidth + space);
		seg.setPosition(segPos);
		window.draw(seg);
	}
	*/
}
