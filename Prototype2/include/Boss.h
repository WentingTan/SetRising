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
class BossJumpState;
class BossFallState;
class TileMap;
class BossDigState;

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
		G_DIG0 = 3,
		G_DIG1 = 4,
		G_DIG2 = 5,
		G_JUMP0 = 6,
		G_JUMP1 = 7,
		G_JUMP2 = 8,
		G_JUMP3 = 9,
		G_STAND = 10,
		G_DIE1 = 11,
	};
	// Images per row in Boss texture
	const int IRP = 6;
	// Image size
	const sf::Vector2i IMG_SIZE = sf::Vector2i(134, 134);

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

		void activate(sf::Vector2f pos, sf::Vector2i tile, float dir);

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
	bool isActive();
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
	bool active = false;
	// Boss states
	BossState *state;
	BossStandState *standing;
	BossWalkState *walking;
	BossFallState *falling;
	BossJumpState *jumping;
	BossDigState *digging;

	//AirState *jumping;
	//AirState *falling;
};

#endif