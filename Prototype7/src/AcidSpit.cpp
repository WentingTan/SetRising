//==========================//
// AcidSpit.cpp             //
// Author: Matthew Stephens //
//==========================//
#include "AcidSpit.h"

AcidSpit::AcidSpit():
	Entity()
{
	// Do nothing
}

AcidSpit::~AcidSpit()
{

}

int AcidSpit::getDamage() const
{
	return damage;
}

float AcidSpit::getDir() const
{
	return dir;
}

void AcidSpit::deactivate()
{
    active = false;
}

void AcidSpit::init()
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

float AcidSpit::getSpeed() const
{
    return speed;
}

void AcidSpit::activate(sf::Vector2f pos, float d)
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

void AcidSpit::copy(AcidSpit& as)
{
    texture = as.texture;
    sprite = as.sprite;
    hitbox = as.hitbox;
    active = as.active;
    damage = as.damage;
    speed = as.speed;
    dir = as.dir;
}

