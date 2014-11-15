//==========================//
// Laser.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Laser.h"

Laser::Laser():
	Entity()
{
	// Do nothing
}

Laser::~Laser()
{

}

int Laser::getDamage() const
{
	return damage;
}

float Laser::getDir() const
{
	return dir;
}

void Laser::deactivate()
{
    active = false;
}

void Laser::init()
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

float Laser::getSpeed() const
{
    return speed;
}

void Laser::activate(sf::Vector2f pos, float d)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * bounds.height;
	sprite.setPosition(pos);
	dir = d;
	active = true;
	bounds = sprite.getGlobalBounds();
	hitbox = bounds;
}

void Laser::copy(Laser& l)
{
    texture = l.texture;
    sprite = l.sprite;
    hitbox = l.hitbox;
    active = l.active;
    damage = l.damage;
    speed = l.speed;
    dir = l.dir;
}

