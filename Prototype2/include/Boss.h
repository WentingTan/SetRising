//==========================//
// Player.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _BOSS_H_
#define _BOSS_H_

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "BossState.h"
#include "Input.h"

// Forward declarations
class BossStandState;
class BossWalkState;

namespace BossNS
{
	enum state
	{
		S_STAND,
		S_WALK,
		S_DIG,
		S_JUMP,
		S_FALL,
		S_ATTACK
	};
	enum graphics
	{
		G_WALK0 = 0,
		G_WALK1 = 1,
		G_WALK2 = 2,
		G_DIG0 = 6,
		G_DIG1 = 7,
		G_DIG2 = 8,
		G_ATTACK0 = 12,
		G_ATTACK1 = 13,
		G_ATTACK2 = 14,
		G_ATTACK3 = 15,
		G_ATTACK4 = 16,
		G_ATTACK5 = 17,
		G_JUMP0 = 18,
		G_JUMP1 = 19,
		G_JUMP2 = 20,
		G_JUMP3 = 21,
		G_STAND = 22,
		G_DIE1 = 25,
	};
	// Images per row in Boss texture
	const int IRP = 6;
	// Image size
	const sf::Vector2i IMG_SIZE = sf::Vector2i(138, 138);

	const float LEFT = -1.0f;
	const float RIGHT = 1.0f;
}


class Boss
{
public:
	// Constructor
	Boss();
	// Destructor
	~Boss();

	// Accessors
	sf::Vector2f getPosition() const;
	sf::FloatRect getHitBox() const;

	void setHitboxWidth(float w);


	// Mutators
	void setTileMap(TileMap *m);
	void setPosition(float x, float y);
	void setState(BossNS::state s, float dir);
	void setTexture(sf::Texture *t);
	void setGraphics(BossNS::graphics g, float dir);

	// Methods
	bool init();
	void move(float x, float y);
	void handleInput(Input& input);
	void update(float dt);
	void draw(sf::RenderWindow& backBuffer);

	bool isOnGround();
	bool isOnLadderTop(float& xCoord);
	bool hasHitWall(float direction);
	bool hasHitCeiling();
	bool isTouchingLadder(float& xCoord);

private:
	sf::Sprite sprite;
	sf::Texture *texture;
	TileMap *map;
	sf::FloatRect hitbox;

	// Boss states
	BossState *state;
	BossStandState *standing;
	BossWalkState *walking;
	//BossFallState *falling;
	//BossDigState *digging;

	//AirState *jumping;
	//AirState *falling;
};

#endif