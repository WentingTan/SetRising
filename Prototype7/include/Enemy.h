//==========================//
// Enemy.h                  //
// Author: Matthew Stephens //
//==========================//
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GravEntity.h"
#include <string>
#include "AlphaOscillator.h"

// Forward declarations
class Blackhole;
class Flame;
class FreezeRay;
class Laser;
class Player;
class TileMap;

class Enemy : public GravEntity
{
public:
	// Constructor
	Enemy(int type, float maxHealth);
	// Destructor
	virtual ~Enemy();

	// Accessors
	bool isFrozen() const;
	sf::Vector2i getSpawnTile() const;

	// Methods
	void init(std::string filename);
	void deactivate();
	void freeze();
	void unfreeze();
	void burn();
	void move(sf::Vector2f ds);
	void scroll(sf::Vector2f ds);
	void despawn();

	bool checkCollision(Laser *l, bool& collide);
	void checkCollision(Flame *f);
	bool checkCollision(FreezeRay *fr, bool& collide);
	bool checkCollision(Player *p, sf::FloatRect& overlap) const;
	bool damage(float amount);

protected:
	const float MAX_HEALTH;
	int type;
	sf::Vector2i spawnTile;
	float health;
	int frame;
	bool frozen;
	float freezeTimer;	
	AlphaOscillator freezeBlinker;
	bool onFire;
	float flameTimer;



	int nExtraHBs;
	sf::FloatRect *extraHB;
	sf::FloatRect *perFrameHBCoords;

	// Animation stuff
	int startFrame;
	int endFrame;
	float animTimer;
	float frameTime;

	// Helpers
	void animate(float dt);
	void updateHitboxes();
	void updateFreeze(float dt);
	bool updateFlame(float dt);
	bool updateGravity(float dt);
	void commonActivate(sf::Vector2f pos, sf::Vector2i tile, sf::Vector2f playerPos);
	void kill(int weapon);
	bool isOffscreen();
	bool isTouchingFloor(TileMap *tm);
};

#endif