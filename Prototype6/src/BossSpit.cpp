//==========================//
// BossSpit.cpp             //
// Author: Jinri Hong //
//==========================//
#include "BossSpit.h"

BossSpit::BossSpit() :
Entity()
{
	// Do nothing
}

BossSpit::~BossSpit()
{

}

int BossSpit::getDamage() const
{
	return damage;
}

float BossSpit::getDir() const
{
	return dir;
}

void BossSpit::deactivate()
{
	active = false;
}

void BossSpit::init()
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

float BossSpit::getSpeed() const
{
	return speed;
}

void BossSpit::activate(sf::Vector2f pos, float d)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * bounds.height;
	sprite.setPosition(pos);
	dir = d;
	active = true;
	bounds = sprite.getGlobalBounds();
	hitbox = bounds;
	sprite.setScale(dir, 1.0f);
}

void BossSpit::copy(BossSpit& as)
{
	texture = as.texture;
	sprite = as.sprite;
	hitbox = as.hitbox;
	active = as.active;
	damage = as.damage;
	speed = as.speed;
	dir = as.dir;
}

