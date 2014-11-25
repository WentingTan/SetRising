//==========================//
// GravityBomb.cpp          //
// Author: Matthew Stephens //
//==========================//
#include "GravityBomb.h"
#include "Constants.h"
#include "EventManager.h"

#include <fstream>


void GBResetHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::RESET_GRAV_BOMB)
		pGB->setReady();
}


GravityBomb::GravityBomb():
	Entity()
{
	resetHandler = NULL;
}

GravityBomb::~GravityBomb()
{
	if (resetHandler)
		delete resetHandler;
}

float GravityBomb::getDir() const
{
	return dir;
}

void GravityBomb::deactivate()
{
    active = false;
}

void GravityBomb::init()
{
	sprite.setTexture(*texture);
	//sprite.setTextureRect(Weapons::LASER_TEXT_RECT);

	//damage = Weapons::LASER_DAMAGE;
	//speed = Weapons::LASER_SPEED;
	dir = 0.0f;
	speed = GRAV_BOMB_SPEED;
	ready = true;

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	resetHandler = new GBResetHandler(this);
	EventManager::addHandler(Event::RESET_GRAV_BOMB, resetHandler);
}

bool GravityBomb::isReady() const
{
	return ready;
}

void GravityBomb::setReady()
{
	ready = true;
}

void GravityBomb::activate(sf::Vector2f pos, float d)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setPosition(pos);
	dir = d;
	active = true;
	ready = false;
	imploding = false;
	dist = 0.0f;
	sprite.setScale(GB_MAX_SCALE, GB_MAX_SCALE);
}

void GravityBomb::update(float dt)
{
	if (!imploding)
	{
		sprite.move(dir * speed * dt, 0.0f);
		dist += dt * speed;

		if (dist > 0.3f * SCREEN_WIDTH)
		{
			imploding = true;
			timer = 0.0f;
		}
	}
	else
	{
		timer += dt;

		float scale = GB_MAX_SCALE - ((GB_MAX_SCALE - GB_MIN_SCALE) / GB_IMPLODE_TIME) * timer;
		sprite.setScale(scale, scale);

		if (timer > GB_IMPLODE_TIME)
		{
			Event::Data e;
			e.type = Event::GRAV_BOMB_IMPLODE;
			e.posX = sprite.getPosition().x;
			e.posY = sprite.getPosition().y;
			EventManager::triggerEvent(e);
			active = false;
		}
	}
}

