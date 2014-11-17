//==========================//
// FreezeRay.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "FreezeRay.h"
#include "Constants.h"

FreezeRay::FreezeRay():
	Entity()
{
	// Do nothing
}

FreezeRay::~FreezeRay()
{

}

int FreezeRay::getDamage() const
{
	return damage;
}

float FreezeRay::getDir() const
{
	return dir;
}

void FreezeRay::deactivate()
{
    active = false;
}

bool FreezeRay::update(float dt)
{
	distance += dt * speed;

	if (distance >= 0.3f * SCREEN_WIDTH)
		return true;
	return false;
}


void FreezeRay::init()
{
	sprite.setTexture(*texture);
	//sprite.setTextureRect(Weapons::LASER_TEXT_RECT);

	//damage = Weapons::LASER_DAMAGE;
	//speed = Weapons::LASER_SPEED;
	damage = 10;
    speed = 500.0f;
	dir = 0.0f;

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	//sprite.scale(2.0f, 2.0f);
}

float FreezeRay::getSpeed() const
{
    return speed;
}

void FreezeRay::activate(sf::Vector2f pos, float d)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * bounds.height;
	sprite.setPosition(pos);
	dir = d;
	active = true;
	bounds = sprite.getGlobalBounds();
	hitbox = bounds;
	distance = 0.0f;
}

void FreezeRay::copy(FreezeRay& f)
{
	texture = f.texture;
    sprite = f.sprite;
    hitbox = f.hitbox;
    active = f.active;
    damage = f.damage;
    speed = f.speed;
    dir = f.dir;
	distance = f.distance;
}

