//==========================//
// Player.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "PlayerState.h"

// Forward declarations
class StandState;
class WalkState;
class JumpState;
class FallState;

namespace PlayerNS
{
	enum state
	{
		S_STAND,
		S_WALK,
		S_JUMP,
		S_FALL
	};
	enum graphics
	{
		G_STAND = 0,
		G_WALK0 = 1,
		G_WALK1 = 2,
		G_WALK2 = 3,
		G_WALK3 = 4,
		G_AIR = 5
	};
	// Images per row in Player texture
	const int IRP = 6;
	// Image size
	const sf::Vector2i IMG_SIZE = sf::Vector2i(128, 128);

	const float LEFT = -1.0f;
	const float RIGHT = 1.0f;
}

class Player
{
public:
	// Constructor
	Player();
	// Destructor
	~Player();

	// Accessors
	sf::Vector2f getPosition() const;
	sf::FloatRect getHitBox() const;

	// Mutators
	void setTileMap(TileMap *m);
	void setPosition(float x, float y);
	void setState(PlayerNS::state s, float dir);
	void setGraphics(PlayerNS::graphics g, float dir);

	// Methods
	bool init();
	void move(float x, float y);
	void handleInput();
	void update(float dt);
	void draw(sf::RenderWindow& backBuffer);

	bool isOnGround();
	bool hasHitWall(float direction);
	bool hasHitCeiling();

private:
	sf::Sprite sprite;
	sf::Texture texture;
	TileMap *map;
	sf::FloatRect hitbox;

	// Player states
	PlayerState *state;
	StandState *standing;
	WalkState *walking;
	JumpState *jumping;
	FallState *falling;
	//AirState *jumping;
	//AirState *falling;
};

#endif