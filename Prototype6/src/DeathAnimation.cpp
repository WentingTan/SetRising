//==========================//
// DeathAnimation.h         //
// Author: Matthew Stephens //
//==========================//
#include "DeathAnimation.h"
#include "Constants.h"

const int DeathAnimation::NUM_FRAMES = 5;
const float DeathAnimation::FRAME_TIME = 0.125f;
const sf::IntRect DeathAnimation::SM_RECT = sf::IntRect(0, 128, 64, 64);
const sf::IntRect DeathAnimation::LG_RECT = sf::IntRect(0, 0, 128, 128);

DeathAnimation::DeathAnimation()
{
	// Do nothing
}

DeathAnimation::~DeathAnimation()
{
	// Do nothing
}

void DeathAnimation::init(sf::Texture *t)
{
	sprite.setTexture(*t);
	inProgress = false;
}

bool DeathAnimation::isInProgress() const
{
	return inProgress;
}

void DeathAnimation::deactivate()
{
	inProgress = false;
}

void DeathAnimation::startAnimation(float x, float y, float dir, int type)
{
	if (type == E_PATROLLING_SNAKE || type == E_STATIONARY_SNAKE)
		sprite.setTextureRect(LG_RECT);
	else
		sprite.setTextureRect(SM_RECT);

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
	sprite.setPosition(x, y);
	sprite.setScale(dir, 1.0f);

	inProgress = true;
	sprite.setPosition(x, y);
	timer = 0.0f;
	frame = 0;
}

void DeathAnimation::scroll(sf::Vector2f ds)
{
	sprite.move(-1.0f * ds);
}

bool DeathAnimation::update(float dt)
{
	timer += dt;

	if (timer > FRAME_TIME)
	{
		timer = 0.0f;

		if (++frame == NUM_FRAMES)
			inProgress = false;
		else
		{
			sf::IntRect rect = sprite.getTextureRect();
			rect.left += frame * rect.width;
			sprite.setTextureRect(rect);
		}
	}

	return !inProgress;
}

void DeathAnimation::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void DeathAnimation::copy(DeathAnimation& d)
{
	sprite.setTextureRect(d.sprite.getTextureRect());
	sprite.setOrigin(d.sprite.getOrigin());
	sprite.setPosition(d.sprite.getPosition());
	timer = d.timer;
	frame = d.frame;
	inProgress = d.inProgress;
}

