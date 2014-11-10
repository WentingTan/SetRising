//==========================//
// Player.cpp               //
// Author: Matthew Stephens //
//==========================//
#include "Player.h"
#include "StandState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "FallState.h"
#include "ClimbState.h"
#include "PlayerProjectiles.h"
#include "EventManager.h"

//===============
// Constructor()
//===============
Player::Player()
{
	// Do nothing
}

//==============================================
// Destructor()
// Deallocates storage for the Player's states.
//==============================================
Player::~Player()
{
	if (standing)
		delete standing;
	if (walking)
		delete walking;
	if (jumping)
		delete jumping;
	if (falling)
		delete falling;
}


//===========//
// Accessors //
//===========//

//===============================================
// getPosition()
// Returns the screen coordinates of the Player.
//===============================================
sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

//============================================================================
// getHitBox()
// Returns the hitbox (rectangle used for collision detection) of the Player.
//============================================================================
sf::FloatRect Player::getHitBox() const
{
	return hitbox;
}

void Player::setHitboxWidth(float w)
{
	hitbox.width = w;
}


//==========//
// Mutators //
//==========//

//====================================
// setTileMap(TileMap*)
// Sets the Player's TileMap pointer.
//====================================
void Player::setTileMap(TileMap *m)
{
	map = m;
}

//============================================
// setPosition(float,float)
// Sets the screen coordinates of the Player.
//============================================
void Player::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

//===================================================================================
// setState(PlayerNS::state, float)
// Sets the Player's state pointer to the given state, and then calls the state's
// enter method, which initializes the state. The direction argument specifies which
// direction the character is facing upon entering the state.
//===================================================================================
void Player::setState(PlayerNS::state s, float dir)
{
	switch (s)
	{
	case PlayerNS::S_STAND:
		state = standing;
		break;
	case PlayerNS::S_WALK:
		state = walking;
		break;
	case PlayerNS::S_JUMP:
		state = jumping;
		break;
	case PlayerNS::S_CLIMB:
		state = climbing;
		break;
	default: // S_FALL
		state = falling;
		break;
	}

	state->enter(dir);
}

//==================================================================================
// setGraphics(PlayerNS::graphics, float)
// Sets the Player's sprite to the specified image, facing the specified direction.
//==================================================================================
void Player::setGraphics(PlayerNS::graphics g, float dir)
{
	// Calculate texture rect for the requested image
	int row = (int)g / PlayerNS::IRP;
	int col = (int)g % PlayerNS::IRP;

	sf::IntRect rect;
	rect.top = row * PlayerNS::IMG_SIZE.y;
	rect.left = col * PlayerNS::IMG_SIZE.x;
	rect.width = PlayerNS::IMG_SIZE.x;
	rect.height = PlayerNS::IMG_SIZE.y;
	
	// Now set the sprite texture rect
	sprite.setTextureRect(rect);
	sprite.setOrigin(64.0f, 64.0f);

	// The images face right by default, set scale in x direction to flip if necessary
	sprite.setScale(dir, 1.0f);
}

void Player::setProjectiles(PlayerProjectiles *p)
{
    projectiles = p;
}

//=========//
// Methods //
//=========//

void Player::setTexture(sf::Texture *t)
{
	texture = t;
}

//==============================================================================================
// init()
// Initializes the Player object. Loads the Player texture, sets the Player's hitbox, allocates
// storage for the Player's states, and sets the initial state of the Player. Returns true if
// successful, false otherwise.
//==============================================================================================
bool Player::init()
{
	sprite.setTexture(*texture);

	// Allocate space for the Player's states
	standing = new StandState(this);
	walking = new WalkState(this, 0.095f);
	jumping = new JumpState(this, 160.0f);
	falling = new FallState(this);
	climbing = new ClimbState(this, 0.175f);
	//jumping = new AirState(this, -400.0f);
	//falling = new AirState(this, 250.0f);


	// Set Player's hitbox
	hitbox.width = 64.0f;
	hitbox.height = 92.0f;

	// Set initial Player state and position
	setState(PlayerNS::S_FALL, PlayerNS::RIGHT);
	sprite.setPosition(400.0f, 300.0f);

	return true;
}

//=================================================================================
// move(float, float)
// Move's the Player by the given amount. If the Player is at one end or the other
// of the TileMap, the Player will actually change screen coordinates. Otherwise,
// the Player's x-corrdinate is kept centered relative the screen, and the TileMap
// is scrolled to give the appearance of movement.
//=================================================================================
void Player::move(float x, float y)
{
	// Determine if the movement should be accomplished by moving the sprite's
	// screen coordinates or by scrolling the tile map.
	bool moveSprite = false;
	if (x == 0.0f)
		moveSprite = true;
	else if (map->isAtLeftEdge())
	{
		if ((x < 0.0f) || (sprite.getPosition().x < 400.0f))
			moveSprite = true;
	}
	else if (map->isAtRightEdge())
	{
		if ((x > 0.0f) || (sprite.getPosition().x > 400.0f))
			moveSprite = true;
	}
	
	if (moveSprite)
		sprite.move(x, y);
	else
	{
		sprite.setPosition(400.0f, sprite.getPosition().y + y);
		map->scroll(x, 0.0f);
	}

	// Update position of Player's hitbox
	hitbox.top = sprite.getPosition().y - 0.5f * hitbox.height;
	hitbox.left = sprite.getPosition().x - 0.5f * hitbox.width;
}

//========================================================
// handleInput()
// Delegate input handling to the Player's current state.
//========================================================
void Player::handleInput(Input& input)
{
	state->handleInput(input);
}

//=========================================
// update(float)
// Delegate to the Player's current state.
//=========================================
void Player::update(float dt)
{
	state->update(dt);
}

void Player::shoot(float dir)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	Event::Data e;

	e.type = Event::PLAYER_SHOOT;
	if (dir > 0.0f)
		e.posX = bounds.left + 0.8f * bounds.width;
	else
		e.posX = bounds.left + 0.2f * bounds.width;
    e.posY = bounds.top + 0.5f * bounds.height;
	e.dir = dir;

	EventManager::triggerEvent(e);

    //projectiles->spawn(pos, dir);
}

//=======================================
// draw(sf::RenderWindow&)
// Draws the Player to the RenderWindow.
//=======================================
void Player::draw(sf::RenderWindow& backBuffer)
{
	backBuffer.draw(sprite);
}

//=================================================================================
// isOnGround()
// Returns true if the bottom of the Player's hitbox is currently colliding with a
// solid tile's hitbox, false otherwise. Given the following diagram representing
// tiles of the TileMap, where the center of the Player's hitbox is somewhere in
// tile 5, only tiles 7, 8, and 9 are checked.
//	+---+---+---+
//	| 1 | 2 | 3 |
//	+---+---+---+
//	| 4 | 5 | 6 |
//	+---+---+---+
//	| 7 | 8 | 9 |
//	+---+---+---+
//=================================================================================
bool Player::isOnGround()
{
	// Get the index of the tile that coincides with the center of the Player
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2i index = map->getTileIndex(pos.x, pos.y);
	
	sf::FloatRect box;
	sf::FloatRect overlap;

	// Check tiles labelled 7, 8, and 9 in the above diagram 
	int y = index.y + 1;
	for (int x = index.x - 1; x < index.x + 2; x++)
	{
		// Get the hitbox of the tile if it is collidable
		if (map->isTileObstactle(x, y))
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.width > 1.0f)
			{
				move(0.0f, -overlap.height + 1.0f);
				return true;
			}
		}
	}
	return false;
}

//=====================================================================================
// hasHitWall(float)
// Returns true if the left or right side (depending on direction argument) of the
// Player's hitbox is currently colliding with a solid tile's hitbox, false otherwise.
// Given the following diagram representing tiles of the TileMap, where the center of 
// the Player's hitbox is somewhere in tile 5, then for dir == RIGHT, only tiles 3, 6,
// and 9 are checked, and for dir == LEFT, only tiles 1, 4, and 7 are checked.
//	+---+---+---+
//	| 1 | 2 | 3 |
//	+---+---+---+
//	| 4 | 5 | 6 |
//	+---+---+---+
//	| 7 | 8 | 9 |
//	+---+---+---+
//=====================================================================================
bool Player::hasHitWall(float direction)
{
	// Get the index of the tile that coincides with the center of the Player
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2i index = map->getTileIndex(pos.x, pos.y);
	sf::FloatRect box;
	sf::FloatRect overlap;

	// If dir == RIGHT, check tiles labelled 3, 6, and 9 in the above diagram
	// If dir == LEFT, check tiles labelled 1, 4, and 7 in the above diagram
	int x = index.x + (int)direction;
	for (int y = index.y - 1; y < index.y + 2; y++)
	{
		// Get the hitbox of the tile if it is collidable
		if (map->isTileObstactle(x, y))
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.height > 2.5f)
			{
				move(-direction * overlap.width, 0.0f);
				return true;
			}
		}
	}
	return false;
}

//================================================================================
// hasHitCeiling()
// Returns true if the top of the Player's hitbox is currently colliding with a
// solid tile's hitbox, false otherwise. Given the following diagram representing
// tiles of the TileMap, where the center of the Player's hitbox is somewhere in
// tile 5, only tiles 1, 2, and 3 are checked.
//	+---+---+---+
//	| 1 | 2 | 3 |
//	+---+---+---+
//	| 4 | 5 | 6 |
//	+---+---+---+
//	| 7 | 8 | 9 |
//	+---+---+---+
//================================================================================
bool Player::hasHitCeiling()
{
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2i index = map->getTileIndex(pos.x, pos.y);

	sf::FloatRect box;
	sf::FloatRect overlap;

	int y = index.y + -1;
	for (int x = index.x - 1; x < index.x + 2; x++)
	{
		// Get the hitbox of the tile if it is collidable
		if (map->isTileObstactle(x, y))
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.width > 1.0f)
			{
				move(0.0f, overlap.height + 0.5f);
				return true;
			}
		}
	}
	return false;
}

bool Player::isOnLadderTop(float& xCoord)
{
	// Get the index of the tile that coincides with the center of the Player
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2i index = map->getTileIndex(pos.x, pos.y);
	
	sf::FloatRect box;
	sf::FloatRect overlap;

	// Check tiles labelled 7, 8, and 9 in the above diagram 
	int y = index.y + 1;
	for (int x = index.x - 1; x < index.x + 2; x++)
	{
		// Get the hitbox of the tile if it is a ladder top
		if (map->getTileType(x, y) == TileNS::LADDER_TOP)
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.width > 30.0f)
			{
				xCoord = box.left + 0.5f * box.width;
				move(0.0f, -overlap.height + 1.0f);
				return true;
			}
		}
	}
	return false;
}

bool Player::isTouchingLadder(float& xCoord)
{
	sf::Vector2f pos = sprite.getPosition();
	sf::Vector2i index = map->getTileIndex(pos.x, pos.y);

	sf::FloatRect box;
	sf::FloatRect overlap;

	for (int y = index.y - 1; y < index.y + 2; y++)
	{
		for (int x = index.x - 1; x < index.x + 2; x++)
		{
			// Get the hitbox of the tile if it is collidable
			if (map->getTileType(x, y) == TileNS::LADDER)
			{
				box = map->getTileHitBox(x, y);

				if (hitbox.intersects(box, overlap) && overlap.width > 30.0f)
				{
					xCoord = box.left + 0.5f * box.width;
					return true;
				}
			}
		}
	}
	return false;
}
