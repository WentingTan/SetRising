//==========================//
// Pickup.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Pickup.h"
#include "Constants.h"
#include "AlphaOscillator.h"

const sf::IntRect Pickup::healthRect = sf::IntRect(0, 0, 16, 16);
const sf::IntRect Pickup::gBombRect = sf::IntRect(0, 0, 16, 16);
const sf::IntRect Pickup::freezeRect = sf::IntRect(64, 32, 16, 16);
const sf::IntRect Pickup::flameRect = sf::IntRect(64, 48, 16, 16);
const sf::IntRect Pickup::flamethrowerRect = sf::IntRect(32, 32, 32, 32);
const sf::IntRect Pickup::freezerayRect = sf::IntRect(0, 32, 32, 32);

Pickup::Pickup():
	Entity(),
	fadeBlinker(FD_ALPHA_HI, FD_ALPHA_LO, FD_CYCLE)
{
	// Do nothing
}

Pickup::~Pickup()
{
	// Do nothing
}

int Pickup::getType() const
{
	return type;
}

float Pickup::getSize() const
{
	return size;
}

//=======================================
// Pickup::init()
// Sets the sprite's texture and origin.
//=======================================
void Pickup::init(int pType)
{
	type = pType;

	sprite.setTexture(*texture);

	sf::IntRect rect;
	switch(type)
	{
	case P_HEALTH:
		rect = healthRect;
		break;
	case P_GRAV_BOMB:
		rect = gBombRect;
		break;
	case P_FLAME_E:
		rect = flameRect;
		break;
	case P_FREEZE_E:
		rect = freezeRect;
		break;
	case P_FLAMETHROWER:
		rect = flamethrowerRect;
		break;
	case P_FREEZERAY:
		rect = freezerayRect;
		break;
	default:
		break;
	}

	sprite.setTextureRect(rect);

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
}


void Pickup::activate(sf::Vector2f pos, float size)
{
	this->size = size;

	sprite.setColor(sf::Color::White);

	// Scale the sprite according to pickup size
	//if (type == P_FLAME_E || type == P_FREEZE_E)
		//sprite.setScale(0.75f * size, 0.75f * size);
	//else
		sprite.setScale(size, size);

	// Set the sprite's position
	sprite.setPosition(pos);

	// Set the hitbox
	hitbox = sprite.getGlobalBounds();

	// Set the active flag to true
	active = true;

	time = 0.0f;
	fadeBlinker.reset();
}

//===============================
// Pickup::deactivate()
// Deactivates the Pickup.
//===============================
void Pickup::deactivate()
{
	active = false;
}


//=======================================================================
// GravPickup::update(float)
//
//=======================================================================
bool Pickup::update(float dt)
{
	time += dt;

	if (time > TIME_TILL_FADE + FADE_TIME)
		return true;
	else if (time > TIME_TILL_FADE)
	{
		fadeBlinker.update(dt);
		sprite.setColor(sf::Color(255, 255, 255, fadeBlinker.getAlpha()));
	}
	return false;
}

void Pickup::copy(Pickup& p)
{
	sprite.setOrigin(p.sprite.getOrigin());
	sprite.setPosition(p.sprite.getPosition());
	sprite.setScale(p.sprite.getScale());
	type = p.type;
	size = p.size;
	time = p.time;
	hitbox = p.hitbox;
	active = p.active;
	fadeBlinker = p.fadeBlinker;
}
