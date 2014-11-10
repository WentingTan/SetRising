//==========================//
// Enemy.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Enemy.h"

Enemy::Enemy():
	Entity()
{
	// Do nothing
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	sprite.setTexture(*texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	sprite.scale(2.0f, 2.0f);
}

sf::Vector2i Enemy::getSpawnTile()
{
	return spawnTile;
}

void Enemy::deactivate()
{
	active = false;
}

bool Enemy::damage(int amount)
{
	health -= amount;
	if (health <= 0)
		return true;
	else
		return false;
}

void Enemy::activate(sf::Vector2f pos, sf::Vector2i tile, float dir)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * bounds.height;
	sprite.setPosition(pos);
	spawnTile = tile;
	health = 25;
	active = true;

	bounds = sprite.getGlobalBounds();
	hitbox.left = pos.x - 0.25f * bounds.width;
	hitbox.top = pos.y - 0.5f * bounds.height;
	hitbox.width = 0.5f * bounds.width;
	hitbox.height = bounds.height;

	bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	sprite.setScale(2.0f * dir, 2.0f);
}

void Enemy::copy(Enemy& e)
{
    texture = e.texture;
	sprite = e.sprite;
	hitbox = e.hitbox;
	active = e.active;
    spawnTile = e.spawnTile;
	health = e.health;
}

