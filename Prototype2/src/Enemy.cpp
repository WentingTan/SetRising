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
void Enemy::setGraphics(EnemyNS::graphics g, float dir)
{
	// Calculate texture rect for the requested image
	int row = (int)g / EnemyNS::IRP;
	int col = (int)g % EnemyNS::IRP;

	sf::IntRect rect;
	rect.top = row * EnemyNS::IMG_SIZE.y;
	rect.left = col * EnemyNS::IMG_SIZE.x;
	rect.width = EnemyNS::IMG_SIZE.x;
	rect.height = EnemyNS::IMG_SIZE.y;

	// Now set the sprite texture rect
	sprite.setTextureRect(rect);
	sprite.setOrigin(64.0f, 64.0f);

	// The images face right by default, set scale in x direction to flip if necessary
	sprite.setScale(dir, 1.0f);
}


