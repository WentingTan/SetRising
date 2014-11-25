//==========================//
// Flame.cpp                //
// Author: Matthew Stephens //
//==========================//
#include "Flame.h"
#include "Constants.h"

Flame::Flame():
	Entity()
{
	hitbox.width = FLAME_HB_WIDTH;
	hitbox.height = (float)FLAME_IMG_HEIGHT;
}

Flame::~Flame()
{

}

int Flame::getDamage() const
{
	return damage;
}

void Flame::deactivate()
{
    active = false;
}

void Flame::init()
{
	sprite.setTexture(*texture);
	//sprite.setTextureRect(Weapons::LASER_TEXT_RECT);

	//damage = Weapons::LASER_DAMAGE;
	//speed = Weapons::LASER_SPEED;
	damage = (int)FLAME_DAMAGE;
	animTimer = 0.0f;

	frame = 0;
	sf::IntRect rect = sf::IntRect(0, 0, FLAME_IMG_WIDTH, FLAME_IMG_HEIGHT);
	sprite.setTextureRect(rect);

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(0.0f, 0.94f * bounds.height);
}

void Flame::activate(sf::Vector2f pos, float dir)
{
	pos.y -= 1.0f;
	pos.x += dir * 5.0f;
	sprite.setPosition(pos);
	sprite.setScale(dir, 1.0f);
	
	sf::FloatRect bounds = sprite.getGlobalBounds();

	hitbox.top = bounds.top;
	if (dir == D_RIGHT)
		hitbox.left = bounds.left;
	else
		hitbox.left = bounds.left + ((float)FLAME_IMG_WIDTH - hitbox.width);

	setInactive = false;
	active = true;
}

void Flame::update(float dt)
{
	if (setInactive)
		active = false;
	else
	{
		animTimer += dt;

		sf::IntRect rect = sf::IntRect(0, 0, FLAME_IMG_WIDTH, FLAME_IMG_HEIGHT);

		if (animTimer > FLAME_FRAME_TIME)
		{
			frame = (frame + 1) % FLAME_FRAMES;
			rect.left = frame * FLAME_IMG_WIDTH;
			sprite.setTextureRect(rect);
			animTimer = 0.0f;
		}

		setInactive = true;

	}
}

