//==========================//
// Healthbar.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _HEALTH_BAR_H
#define _HEALTH_BAR_H

#include <SFML/Graphics.hpp>
#include "EventHandler.h"

// Forward declaration
class Healthbar;

//==============================================
// Healthbar EventHandler for Event::PLAYER_HIT
//==============================================
class HBPlayerHitHandler : public EventHandler
{
public:
	// Constructor
	explicit HBPlayerHitHandler(Healthbar *hb): pHB(hb) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Healthbar *pHB;
};

//===============================================
// Healthbar EventHandler for Event::PLAYER_HEAL
//===============================================
class HBPlayerHealHandler : public EventHandler
{
public:
	// Constructor
	explicit HBPlayerHealHandler(Healthbar *hb): pHB(hb) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Healthbar *pHB;
};

namespace Health
{
	const sf::IntRect BAR_RECT = sf::IntRect(0, 0, 128, 16);
	const sf::IntRect SEG_RECT = sf::IntRect(0, 16, 2, 8);
	const int MAX_HEALTH = 40;
	const sf::Vector2f POS = sf::Vector2f(30.0f, 30.0f);
	const float OFFSET = 4.0f;
	const float SPACE = 1.0f;
};

class Healthbar
{
public:
	// Constructor
	Healthbar(int start, int max);

	// Methods
	void setTexture(sf::Texture *t);
	void init();
	void adjustBy(int amount);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture *texture;
	sf::Sprite bar;
	//sf::Sprite seg;
	sf::RectangleShape seg;
	const int MAX_HEALTH;
	int health;

	EventHandler *hitHandler;
	EventHandler *healHandler;
};

#endif