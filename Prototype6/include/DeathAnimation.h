//==========================//
// DeathAnimation.h         //
// Author: Matthew Stephens //
//==========================//
#ifndef _DEATH_ANIMATION_H_
#define _DEATH_ANIMATION_H_

#include <SFML/Graphics.hpp>

class DeathAnimation
{
public:
	// Constructor
	DeathAnimation();
	// Destructor
	~DeathAnimation();

	void init(sf::Texture *t);
	bool isInProgress() const;
	void startAnimation(float x, float y, float dir, int type);
	void scroll(sf::Vector2f ds);
	void deactivate();
	bool update(float dt);
	void draw(sf::RenderWindow& window);
	void copy(DeathAnimation& d);

private:
	sf::Sprite sprite;
	float timer;
	int frame;
	bool inProgress;

	static const int NUM_FRAMES;
	static const float FRAME_TIME;
	static const sf::IntRect SM_RECT;
	static const sf::IntRect LG_RECT;
};

#endif