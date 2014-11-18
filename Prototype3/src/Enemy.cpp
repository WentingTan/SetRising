//==========================//
// Enemy.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Enemy.h"

#include <fstream>


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
	sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
}

sf::Vector2i Enemy::getSpawnTile()
{
	return spawnTile;
}

void Enemy::deactivate()
{
	active = false;
}

void Enemy::update(float dt)
{
	timer += dt;

	sf::IntRect rect = sf::IntRect(0, 0, 128, 128);

	if (timer > 0.225f)
	{
		frame = (frame + 1) % 4;
		rect.left = frame * 128;
		sprite.setTextureRect(rect);
		timer = 0.0f;
	}
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
	frame = 0;
	timer = 0.0f;

	sf::IntRect rect = sf::IntRect(0, 0, 128, 128);
	sprite.setTextureRect(rect);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	pos.y -= 0.5f * 94.0f;
	sprite.setPosition(pos);
	spawnTile = tile;
	health = 25;
	active = true;

	bounds = sprite.getGlobalBounds();
	hitbox.left = pos.x - 0.5f * 94.0f;
	hitbox.top = pos.y - 0.5f * 94.0f;
	hitbox.width = 94.0f;
	hitbox.height = 94.0f;

	bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	sprite.setScale(dir, 1.0f);
}

void Enemy::copy(Enemy& e)
{
    texture = e.texture;
	sprite = e.sprite;
	hitbox = e.hitbox;
	active = e.active;
    spawnTile = e.spawnTile;
	health = e.health;
	frame = e.frame;
	timer = e.timer;
}

