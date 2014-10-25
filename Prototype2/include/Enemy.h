//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SFML/Graphics.hpp>

class Enemy
{
public:
	// Constructor
	Enemy();
	// Destructor
	~Enemy();

	void scroll(sf::Vector2f ds);
	void init();
	bool isActive();
	void activate(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);

private:
	bool active;
	sf::Sprite sprite;
	sf::Texture texture;
};

#endif