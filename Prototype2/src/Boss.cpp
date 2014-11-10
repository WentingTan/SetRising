//==========================//
// Boss.cpp               //
// Author: Jinri Hong //
//==========================//
#include "Boss.h"
#include "BossStandState.h"
#include "BossDigState.h"
#include "BossFallState.h"
#include "BossWalkState.h"
#include "BossJumpState.h"



//===============
// Constructor()
//===============
Boss::Boss()
{
	// Do nothing
}

//==============================================
// Destructor()
// Deallocates storage for the Boss's states.
//==============================================
Boss::~Boss()
{
	if (standing)
		delete standing;
	
}


//===========//
// Accessors //
//===========//

//===============================================
// getPosition()
// Returns the screen coordinates of the Boss.
//===============================================
sf::Vector2f Boss::getPosition() const
{
	return sprite.getPosition();
}

//============================================================================
// getHitBox()
// Returns the hitbox (rectangle used for collision detection) of the Boss.
//============================================================================
sf::FloatRect Boss::getHitBox() const
{
	return hitbox;
}

void Boss::setHitboxWidth(float w)
{
	hitbox.width = w;
}


//==========//
// Mutators //
//==========//

//====================================
// setTileMap(TileMap*)
// Sets the Boss's TileMap pointer.
//====================================
void Boss::setTileMap(TileMap *m)
{
	map = m;
	// Set initial Boss state and position
	setState(BossNS::S_FALL, BossNS::RIGHT);
	sprite.setPosition(400.0f, 158.0f);
}

//============================================
// setPosition(float,float)
// Sets the screen coordinates of the Boss.
//============================================
void Boss::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

//===================================================================================
// setState(BossNS::state, float)
// Sets the Boss's state pointer to the given state, and then calls the state's
// enter method, which initializes the state. The direction argument specifies which
// direction the character is facing upon entering the state.
//===================================================================================
void Boss::setState(BossNS::state s, float dir)
{
	switch (s)
	{
	case BossNS::S_STAND:
		state = standing;
		break;
	case BossNS::S_WALK:
		state = walking;
		break;
	case BossNS::S_DIG:
		state = digging;
		break;
	case BossNS::S_FALL:
		state = falling;
		break;
	case BossNS::S_JUMP:
		state = jumping;
		break;
	default:
		state = standing;
		break;
	
	}
	
	state->enter(dir);

}

//==================================================================================
// setGraphics(BossNS::graphics, float)
// Sets the Boss's sprite to the specified image, facing the specified direction.
//==================================================================================
void Boss::setGraphics(BossNS::graphics g, float dir)
{
	// Calculate texture rect for the requested image
	int row = (int)g / BossNS::IRP;
	int col = (int)g % BossNS::IRP;

	sf::IntRect rect;
	rect.top = row * BossNS::IMG_SIZE.y;
	rect.left = col * BossNS::IMG_SIZE.x;
	rect.width = BossNS::IMG_SIZE.x;
	rect.height = BossNS::IMG_SIZE.y;

	// Now set the sprite texture rect
	sprite.setTextureRect(rect);
	sprite.setOrigin(67.0f, 67.0f);

	// The images face right by default, set scale in x direction to flip if necessary
	sprite.setScale(dir, 1.0f);
}


//=========//
// Methods //
//=========//

void Boss::setTexture(sf::Texture *t)
{
	texture = t;
}

//==============================================================================================
// init()
// Initializes the Boss object. Loads the Boss texture, sets the Boss's hitbox, allocates
// storage for the Boss's states, and sets the initial state of the Boss. Returns true if
// successful, false otherwise.
//==============================================================================================
bool Boss::init()
{
	sprite.setTexture(*texture);

	// Allocate space for the Boss's states
	standing = new BossStandState(this);
	walking = new BossWalkState(this, 0.175f);
	digging = new BossDigState(this, 1.0f, 100.0f);
	jumping = new BossJumpState(this, 200.0f, 0.15f);
	falling = new BossFallState(this, 0.15f);
	//jumping = new AirState(this, -400.0f);
	//falling = new AirState(this, 250.0f);


	// Set Boss's hitbox
	hitbox.width = 90.0f;
	hitbox.height = 90.0f;

	

	return true;
}

//=================================================================================
// move(float, float)
// Move's the Boss by the given amount. If the Boss is at one end or the other
// of the TileMap, the Boss will actually change screen coordinates. Otherwise,
// the Boss's x-corrdinate is kept centered relative the screen, and the TileMap
// is scrolled to give the appearance of movement.
//=================================================================================
void Boss::move(float x, float y)
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

	// Update position of Boss's hitbox
	hitbox.top = sprite.getPosition().y - 0.5f * hitbox.height;
	hitbox.left = sprite.getPosition().x - 0.5f * hitbox.width;
}

//========================================================
// handleInput()
// Delegate input handling to the Boss's current state.
//========================================================
void Boss::handleInput(Input& input)
{
	state->handleInput(input);
}

//=========================================
// update(float)
// Delegate to the Boss's current state.
//=========================================
void Boss::update(float dt)
{
	state->update(dt);
}


//=======================================
// draw(sf::RenderWindow&)
// Draws the Boss to the RenderWindow.
//=======================================
void Boss::draw(sf::RenderWindow& backBuffer)
{
	backBuffer.draw(sprite);
}

//=================================================================================
// isOnGround()
// Returns true if the bottom of the Boss's hitbox is currently colliding with a
// solid tile's hitbox, false otherwise. Given the following diagram representing
// tiles of the TileMap, where the center of the Boss's hitbox is somewhere in
// tile 5, only tiles 7, 8, and 9 are checked.
//	+---+---+---+
//	| 1 | 2 | 3 |
//	+---+---+---+
//	| 4 | 5 | 6 |
//	+---+---+---+
//	| 7 | 8 | 9 |
//	+---+---+---+
//=================================================================================
bool Boss::isOnGround()
{
	// Get the index of the tile that coincides with the center of the Boss
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
// Boss's hitbox is currently colliding with a solid tile's hitbox, false otherwise.
// Given the following diagram representing tiles of the TileMap, where the center of 
// the Boss's hitbox is somewhere in tile 5, then for dir == RIGHT, only tiles 3, 6,
// and 9 are checked, and for dir == LEFT, only tiles 1, 4, and 7 are checked.
//	+---+---+---+
//	| 1 | 2 | 3 |
//	+---+---+---+
//	| 4 | 5 | 6 |
//	+---+---+---+
//	| 7 | 8 | 9 |
//	+---+---+---+
//=====================================================================================
bool Boss::hasHitWall(float direction)
{
	// Get the index of the tile that coincides with the center of the Boss
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
// Returns true if the top of the Boss's hitbox is currently colliding with a
// solid tile's hitbox, false otherwise. Given the following diagram representing
// tiles of the TileMap, where the center of the Boss's hitbox is somewhere in
// tile 5, only tiles 1, 2, and 3 are checked.
//	+---+---+---+
//	| 1 | 2 | 3 |
//	+---+---+---+
//	| 4 | 5 | 6 |
//	+---+---+---+
//	| 7 | 8 | 9 |
//	+---+---+---+
//================================================================================
bool Boss::hasHitCeiling()
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

bool Boss::isOnLadderTop(float& xCoord)
{
	// Get the index of the tile that coincides with the center of the Boss
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

bool Boss::isTouchingLadder(float& xCoord)
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
