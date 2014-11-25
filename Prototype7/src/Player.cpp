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
#include "AlphaOscillator.h"
#include "BarrierManager.h"



#include <fstream>

void PNewMapHandler::handleEvent(Event::Data e)
{
	// Ensure that this was triggered by the correct event type
	if (e.type == Event::NEW_MAP)
	{
		pP->setTileMap((TileMap*)e.map);
		sf::Vector2f pos = pP->getPosition();
		switch (e.reposition)
		{
		case MAINTAIN_X:
			pP->setPosition(pos.x, e.posY);
			break;
		case MAINTAIN_Y:
			pP->setPosition(e.posX, pos.y);
			break;
		case CENTER_TILE:
			pP->setPosition(e.posX, e.posY);
			break;
		default:
			break;
		}
	}

	// Generate a PLAYER_MOVED event with the player's new coordinates
	Event::Data m;
	m.type = Event::PLAYER_MOVED;
	m.posX = pP->getPosition().x;
	m.posY = pP->getPosition().y;
	EventManager::triggerEvent(m);

	// Generate an INITIAL_ENEMY_SPAWN event
	m.type = Event::INITIAL_ENEMY_SPAWN;
	EventManager::triggerEvent(m);
}

void PResetGBHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::RESET_GRAV_BOMB)
		pP->resetGravBomb();
}

void PContinueHandler::handleEvent(Event::Data e)
{
	if (e.type == Event::CONTINUE)
		pP->onContinue();
}

//===============
// Constructor()
//===============
Player::Player()
{
	standing = NULL;
	walking = NULL;
	jumping = NULL;
	falling = NULL;
	climbing = NULL;
	newMapHandler = NULL;
	resetGBHandler = NULL;
	continueHandler = NULL;
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
	if (climbing)
		delete climbing;
	if (newMapHandler)
		delete newMapHandler;
	if (resetGBHandler)
		delete resetGBHandler;
	if (continueHandler)
		delete continueHandler;
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

//=================================================================================
// Player::isDamaged()
// Indicates whether the player is damaged.  The player is invulnerable to further
// damage for a short period of time after taking damage.
//=================================================================================
bool Player::isDamaged() const
{
	return damaged;
}

//==========//
// Mutators //
//==========//

//====================================
// Player::setTileMap(TileMap*)
// Sets the Player's TileMap pointer.
//====================================
void Player::setTileMap(TileMap *m)
{
	map = m;
}

//===========================================================================
// Player::setEnemyManger(EnemyManager*)
// Sets the Player's EnemyManager pointer which is used to detect collisions
// between the player and frozen enemies.
//===========================================================================
void Player::setEnemyManager(EnemyManager *e)
{
	enemies = e;
}

void Player::setBarrierManager(BarrierManager *b)
{
	barriers = b;
}

//============================================
// Player::setPosition(float,float)
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

	// Set the sprite texture rect
	sprite.setTextureRect(rect);
	// Set the sprite's origin
	//sf::FloatRect bounds = sprite.getGlobalBounds();
	//sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	// The images face right by default, set scale in x direction to flip if necessary
	sprite.setScale(dir, 1.0f);
}

//void Player::setProjectiles(PlayerProjectiles *p)
//{
  //  projectiles = p;
//}

//=====================================================================================
// Player::damage()
// Sets the damaged flag to true, and sets the damageTimer to its initial value, which
// is the duration for which the player will be invulnerable to further damage.
//=====================================================================================
void Player::damage(float amount)
{
	damaged = true;
	damageTimer = PlayerNS::DAMAGE_TIME;

	health -= amount;

	Event::Data e;
	e.type = Event::PLAYER_HIT;
	e.energy = health;
	EventManager::triggerEvent(e);

	if (health <= 0.0f)
	{
		dead = true;
		e.type = Event::PLAYER_DEATH;
		e.posX = sprite.getPosition().x;
		e.posY = sprite.getPosition().y;
		e.dir = state->getDir();
		EventManager::triggerEvent(e);
	}
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

	// Set Player's hitbox
	hitbox.width = PlayerNS::HITBOX_DIM.x;
	hitbox.height = PlayerNS::HITBOX_DIM.y;
	hitbox.top = sprite.getPosition().y - 0.45f * PlayerNS::HITBOX_DIM.y;
	hitbox.left = sprite.getPosition().x - 0.5f * PlayerNS::HITBOX_DIM.x;

	// Set initial Player state and position
	setState(PlayerNS::S_FALL, PlayerNS::RIGHT);
	sprite.setPosition(0.5f * SCREEN_WIDTH, 0.5f * SCREEN_HEIGHT);

	// Set the sprite's origin
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(0.5f * bounds.width, 0.5f * bounds.height);

	// Set the damaged flag to false
	damaged = false;
	damageTimer = 0.0f;
	dead = false;

	selectedWeapon = W_LASER;
	hasFlame = false;
	hasFreeze = false;
	gBombReady = true;
	lastDt = 0.0f;

	// Register EventHandlers
	newMapHandler = new PNewMapHandler(this);
	resetGBHandler = new PResetGBHandler(this);
	continueHandler = new PContinueHandler(this);
	EventManager::addHandler(Event::NEW_MAP, newMapHandler);
	EventManager::addHandler(Event::RESET_GRAV_BOMB, resetGBHandler);
	EventManager::addHandler(Event::CONTINUE, continueHandler);

	health = MAX_HEALTH;
	flameEnergy = MAX_FLAME_ENERGY;
	freezeEnergy = MAX_FREEZE_ENERGY;
	nGravBombs = MAX_GRAV_BOMBS;

	damageFlash = new AlphaOscillator(PlayerNS::DMG_HI_ALPHA, PlayerNS::DMG_LO_ALPHA, PlayerNS::DMG_CYCLE);

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
	bool moveX = false;
	bool moveY = false;
	sf::Vector2f newPos;
	sf::Vector2f scroll;

	bool leftEdge = map->isAtBoundary(LEFT_EDGE);
	bool rightEdge = map->isAtBoundary(RIGHT_EDGE);
	bool bottomEdge = map->isAtBoundary(BOTTOM_EDGE);
	bool topEdge = map->isAtBoundary(TOP_EDGE);

	sf::Vector2f pos = sprite.getPosition();

	if (leftEdge && rightEdge)
		moveX = true;
	else if (leftEdge && (x < 0.0f || pos.x < 0.5f * SCREEN_WIDTH))
		moveX = true;
	else if (rightEdge && (x > 0.0f || pos.x > 0.5f * SCREEN_WIDTH))
		moveX = true;

	if (topEdge && bottomEdge)
		moveY = true;
	//else if (topEdge && (y < 0.0f || pos.y < 0.667f * SCREEN_HEIGHT))
	else if (topEdge && (y < 0.0f || pos.y < 0.6f * SCREEN_HEIGHT))
		moveY = true;
	//else if (bottomEdge && (y > 0.0f || pos.y > 0.333f * SCREEN_HEIGHT))
	else if (bottomEdge && (y > 0.0f || pos.y > 0.4f * SCREEN_HEIGHT))
		moveY = true;

	//else if (y > 0.0f && pos.y < 0.667f * SCREEN_HEIGHT)
	else if (y > 0.0f && pos.y < 0.6f * SCREEN_HEIGHT)
		moveY = true;
	//else if (y < 0.0f && pos.y + y < 0.667f * SCREEN_HEIGHT && pos.y + y > 0.333f * SCREEN_HEIGHT)
	else if (y < 0.0f && pos.y + y < 0.6f * SCREEN_HEIGHT && pos.y + y > 0.4f * SCREEN_HEIGHT)
		moveY = true;


	if (moveX)
		sprite.move(x, 0.0f);
	else
	{
		sprite.setPosition(0.5f * SCREEN_WIDTH, sprite.getPosition().y);
		map->scroll(x, 0.0f);
	}

	if (moveY)
		sprite.move(0.0f, y);
	else
		map->scroll(0.0f, y);

	pos = sprite.getPosition();

	// Update position of Player's hitbox
	hitbox.top = pos.y - 0.45f * hitbox.height;
	hitbox.left = pos.x - 0.5f * hitbox.width;

	// Generate a PLAYER_MOVED event with the player's new coordinates
	Event::Data e;
	e.type = Event::PLAYER_MOVED;
	e.posX = pos.x;
	e.posY = pos.y;
	EventManager::triggerEvent(e);

	// Check for a transition to a new TileMap
	Tile *tile;
	if (isOffscreen(x, y))
	{
		tile = map->getTileByPos(sprite.getPosition().x, sprite.getPosition().y);
		if (tile != NULL && tile->exit != -1)
		{
			e.type = Event::TM_TRANSITION;
			e.entrance = tile->exit;
			EventManager::triggerEvent(e);
		}
	}

}

void Player::selectWeapon(int type)
{
	selectedWeapon = type;

	Event::Data e;
	e.type = Event::WEAPON_SEL;
	e.weaponType = selectedWeapon;
	EventManager::triggerEvent(e);
}

void Player::resetGravBomb()
{
	gBombReady = true;
}

void Player::onContinue()
{
	dead = false;
	damaged = false;
	gBombReady = true;
	health = MAX_HEALTH;
	nGravBombs = MAX_GRAV_BOMBS;
	flameEnergy = MAX_FLAME_ENERGY;
	freezeEnergy = MAX_FREEZE_ENERGY;
	selectedWeapon = W_LASER;
}

//========================================================
// handleInput()
// Delegate input handling to the Player's current state.
//========================================================
void Player::handleInput(Input& input)
{
	if (dead)
		return;

	state->handleInput(input);

	if (input.isPressed(InputNS::SEL_LASER))
		selectWeapon(W_LASER);
	else if (input.isPressed(InputNS::SEL_FREEZE) && hasFreeze)
		selectWeapon(W_FREEZE_RAY);
	else if (input.isPressed(InputNS::SEL_FLAME) && hasFlame)
		selectWeapon(W_FLAMETHROWER);
	else if (input.isPressed(InputNS::SEL_GRAV))
		selectWeapon(W_GRAVITY_BOMB);

	// Cycle through available weapons
	if (input.wasPressed(InputNS::CYCLE_SEL))
	{
		if (hasFreeze)
			selectWeapon((selectedWeapon + 1) % (W_FREEZE_RAY + 1));
		else if (hasFlame)
			selectWeapon((selectedWeapon + 1) % (W_FLAMETHROWER + 1));
		else
			selectWeapon((selectedWeapon + 1) % (W_GRAVITY_BOMB + 1));
	}

	// Handle shooting
	if (state != climbing)
	{
		if (selectedWeapon == W_FLAMETHROWER)
		{
			if (input.isPressed(InputNS::SHOOT))
				shoot(state->getDir());
		}
		else
		{
			if (input.wasPressed(InputNS::SHOOT))
				shoot(state->getDir());
		}
	}

}

void Player::getPickup(int type, float size)
{
	Event::Data e;
	e.type = Event::PLAYER_PICKUP;
	e.pickupType = type;

	switch (type)
	{
	case P_HEALTH:
		health += (size == P_SMALL ? SM_HEALTH_VAL : LG_HEALTH_VAL);
		if (health > MAX_HEALTH)
			health = MAX_HEALTH;
		e.energy = health;
		break;
	case P_GRAV_BOMB:
		nGravBombs++;
		if (nGravBombs > MAX_GRAV_BOMBS)
			nGravBombs = MAX_GRAV_BOMBS;
		e.energy = (float)nGravBombs;
		break;
	case P_FLAME_E:
		flameEnergy += (size == P_SMALL ? SM_FLAME_E_VAL : LG_FLAME_E_VAL);
		if (flameEnergy > MAX_FLAME_ENERGY)
			flameEnergy = MAX_FLAME_ENERGY;
		e.energy = flameEnergy;
		break;
	case P_FREEZE_E:
		freezeEnergy += (size == P_SMALL ? SM_FREEZE_E_VAL : LG_FREEZE_E_VAL);
		if (freezeEnergy > MAX_FREEZE_ENERGY)
			freezeEnergy = MAX_FREEZE_ENERGY;
		e.energy = freezeEnergy;
		break;
	case P_FLAMETHROWER:
		hasFlame = true;
		break;
	case P_FREEZERAY:
		hasFreeze = true;
		break;
	default:
		break;
	}

	EventManager::triggerEvent(e);
}

//=========================================
// update(float)
// Delegate to the Player's current state.
//=========================================
void Player::update(float dt)
{
	if (dead)
		return;

	state->update(dt);

	lastDt = dt;

	if (damaged)
	{
		damageTimer -= dt;

		damageFlash->update(dt);
		sprite.setColor(sf::Color(255, 255, 255, damageFlash->getAlpha()));

		if (damageTimer < 0.0f)
		{
			damaged = false;
			sprite.setColor(sf::Color::White);
		}
	}

}

bool Player::isOffscreen(float x, float y)
{
	sf::Vector2f pos = sprite.getPosition();

	if (pos.x < 0.0f && x < 0.0f)
		return true;
	if (pos.x > SCREEN_WIDTH && x > 0.0f)
		return true;
	if (pos.y < 0.0f && y < 0.0f)
		return true;
	if (pos.y > SCREEN_HEIGHT && y > 0.0f)
		return true;
	return false;
}

//===============================================================================
// Player::shoot(float)
// Generates a PLAYER_SHOOT event with the coordinates and direction at which to
// spawn the projectile.
//===============================================================================
void Player::shoot(float dir)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	Event::Data e;

	switch (selectedWeapon)
	{
	case W_LASER:
		break;
	case W_FLAMETHROWER:
		if (flameEnergy <= 0.0f)
			return;
		flameEnergy -= lastDt * FLAME_ENERGY_PER_SEC;
		e.energy = flameEnergy;
		break;
	case W_FREEZE_RAY:
		if (freezeEnergy <= 0.0f)
			return;
		freezeEnergy -= FREEZE_ENERGY_PER_SHOT;
		e.energy = freezeEnergy;
		break;
	case W_GRAVITY_BOMB:
		if (nGravBombs == 0 || !gBombReady)
			return;
		nGravBombs--;
		gBombReady = false;
		e.energy = (float)nGravBombs;
		break;
	default:
		break;
	}

	e.type = Event::PLAYER_SHOOT;
	e.weaponType = selectedWeapon;
	if (dir > 0.0f)
		e.posX = bounds.left + 0.8f * bounds.width;
	else
		e.posX = bounds.left + 0.2f * bounds.width;
    e.posY = bounds.top + 0.5f * bounds.height;
	e.dir = dir;

	EventManager::triggerEvent(e);
}

float Player::getDir() const
{
	return state->getDir();
}

//=======================================
// draw(sf::RenderWindow&)
// Draws the Player to the RenderWindow.
//=======================================
void Player::draw(sf::RenderWindow& backBuffer)
{
	if (dead)
		return;

	backBuffer.draw(sprite);


	//sf::RectangleShape hb;
	//hb.setFillColor(sf::Color(255, 0, 0, 200));
	//hb.setPosition(hitbox.left, hitbox.top);
	//hb.setSize(sf::Vector2f(hitbox.width, hitbox.height));

	//backBuffer.draw(hb);
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
		if (map->isTileObstacle(x, y) || (map->getTileType(x, y) == TileNS::LADDER_TOP && state != climbing))
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.width > 1.0f)
			{
				move(0.0f, -overlap.height + 1.0f);
				return true;
			}
		}
	}

	// Check if the player is standing on top of a frozen enemy
	if (enemies->checkFrozenCollisions(this, overlap) && overlap.width > 1.0f)
	{
		move(0.0f, -overlap.height + 1.0f);
		return true;
	}

	if (barriers->checkFloorBlocks(this))
		return true;


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
		if (map->isTileObstacle(x, y))
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.height > 2.5f)
			{
				move(-direction * overlap.width, 0.0f);
				return true;
			}
		}
	}

	// Check if the player has run into a frozen enemy
	if (enemies->checkFrozenCollisions(this, overlap) && overlap.height > 2.5f)
	{
		move(-direction * overlap.width, 0.0f);
		return true;
	}

	if (barriers->checkWallBlocks(this))
		return true;


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
		if (map->isTileObstacle(x, y))
		{
			box = map->getTileHitBox(x, y);

			if (hitbox.intersects(box, overlap) && overlap.width > 1.0f)
			{
				move(0.0f, overlap.height + 0.5f);
				return true;
			}
		}
	}

	if (barriers->checkCeilingBlocks(this))
		return true;

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

			if (hitbox.intersects(box, overlap) && overlap.width > 0.6f * hitbox.width)
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

				if (hitbox.intersects(box, overlap) && overlap.width > 0.6f * hitbox.width)
				{
					xCoord = box.left + 0.5f * box.width;
					return true;
				}
			}
		}
	}
	return false;
}
