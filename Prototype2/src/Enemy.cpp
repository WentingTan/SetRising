//==========================//
// Enemy.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Enemy.h"

Enemy::Enemy()
{
	active = false;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	texture.loadFromFile("set.png");
	sprite.setTexture(texture);

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	sprite.scale(2.0f, 2.0f);
}

void Enemy::scroll(sf::Vector2f ds)
{
	sprite.move(-1.0f * ds);
}

bool Enemy::isActive()
{
	return active;
}

void Enemy::activate(sf::Vector2f pos)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * bounds.height;
	sprite.setPosition(pos);
	active = true;
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
