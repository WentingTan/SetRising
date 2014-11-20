//==========================//
// Blackhole.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "Blackhole.h"
#include "Constants.h"
#include "EventManager.h"

void BHImplodeHHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::GRAV_BOMB_IMPLODE)
		pBH->activate(sf::Vector2f(e.posX, e.posY));
}

void BHScrollHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::SCROLL)
		pBH->scroll(sf::Vector2f(e.scrollX, e.scrollY));
}

void BHTransitionHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::TM_TRANSITION)
		pBH->deactivate();
}

void BHDeathHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::ENEMY_DEATH && e.weaponType == W_GRAVITY_BOMB)
		pBH->decInField();
}

Blackhole::Blackhole():
	Entity()
{
	scrollHandler = NULL;
	implodeHandler = NULL;
	deathHandler = NULL;
	transitionHandler = NULL;
}

Blackhole::~Blackhole()
{
	if (scrollHandler)
		delete scrollHandler;
	if (implodeHandler)
		delete implodeHandler;
	if (deathHandler)
		delete deathHandler;
	if (transitionHandler)
		delete transitionHandler;
}


void Blackhole::deactivate()
{
    active = false;
	Event::Data e;
	e.type = Event::RESET_GRAV_BOMB;
	EventManager::triggerEvent(e);
}

float Blackhole::getFieldRadius() const
{
	return 0.7f * sprite.getGlobalBounds().width;
}

void Blackhole::incInField()
{
	nInField++;
}

void Blackhole::decInField()
{
	nInField--;
}

void Blackhole::update(float dt)
{
	hole.setPosition(sprite.getPosition());
	sprite.rotate(dt * BH_ANG_VEL);

	timer += dt;
	if (timer > BH_TIME && nInField == 0)
	//if (timer > BH_TIME)
		deactivate();
	else if (timer < BH_EXPAND_TIME)
	{
		float scale = BH_MIN_SCALE + ((BH_MAX_SCALE - BH_MIN_SCALE) / BH_EXPAND_TIME) * timer;
		sprite.setScale(scale, scale);
		hole.setScale(0.5f * scale, 0.5f * scale);
	}
	else
	{
		sprite.setScale(BH_MAX_SCALE, BH_MAX_SCALE);
		hole.setScale(0.5f * BH_MAX_SCALE, 0.5f * BH_MAX_SCALE);
	}
}


void Blackhole::init()
{
	sprite.setTexture(*texture);
	timer = 0.0f;
	sprite.setColor(sf::Color(255, 255, 255, BH_ALPHA));

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	sprite.setScale(2.5f, 2.5f);

	hole.setRadius(0.5f * 0.5f * sprite.getGlobalBounds().width);
	//hole.setRadius(4.0f);
	bounds = hole.getGlobalBounds();

	hole.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	hole.setFillColor(sf::Color::Black);

	active = false;

	scrollHandler = new BHScrollHandler(this);
	implodeHandler = new BHImplodeHHandler(this);
	deathHandler = new BHDeathHandler(this);
	transitionHandler = new BHTransitionHandler(this);
	EventManager::addHandler(Event::SCROLL, scrollHandler);
	EventManager::addHandler(Event::GRAV_BOMB_IMPLODE, implodeHandler);
	EventManager::addHandler(Event::ENEMY_DEATH, deathHandler);
	EventManager::addHandler(Event::TM_TRANSITION, transitionHandler);

	//sprite.scale(2.0f, 2.0f);
}

void Blackhole::activate(sf::Vector2f pos)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	timer = 0.0f;
	nInField = 0;
	sprite.setPosition(pos);
	hole.setPosition(pos);
	active = true;
	sprite.setScale(BH_MIN_SCALE, BH_MIN_SCALE);
	hole.setScale(BH_MIN_SCALE, BH_MIN_SCALE);
}

void Blackhole::draw(sf::RenderWindow& window)
{
	//window.draw(hole);
	window.draw(sprite);
	window.draw(hole);
}

/*
void Blackhole::scroll(sf::Vector2f ds)
{
	ds *= -1.0f;
	sprite.move(ds);
	hole.move(ds);
}
*/

