//==========================//
// Player.h                 //
// Author: Matthew Stephens //
//==========================//
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "PlayerState.h"
#include "Input.h"
#include "EventHandler.h"
#include "Constants.h"

// Forward declarations
class StandState;
class WalkState;
class JumpState;
class FallState;
class ClimbState;
class PlayerProjectiles;
class Player;
class AlphaOscillator;
class EnemyManager;
class BarrierManager;

//========================================
// Player EventHandler for Event::NEW_MAP
//========================================
class PNewMapHandler : public EventHandler
{
public:
	// Constructor
	explicit PNewMapHandler(Player *p): pP(p) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Player *pP;
};

//=========================================
// Player EventHandler for Event::CONTINUE
//=========================================
class PContinueHandler : public EventHandler
{
public:
	// Constructor
	explicit PContinueHandler(Player *p): pP(p) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Player *pP;
};

//================================================
// Player EventHandler for Event::RESET_GRAV_BOMB
//================================================
class PResetGBHandler : public EventHandler
{
public:
	// Constructor
	explicit PResetGBHandler(Player *p): pP(p) {}
	// Methods
	virtual void handleEvent(Event::Data e);
private:
	Player *pP;
};


namespace PlayerNS
{
	enum state
	{
		S_STAND,
		S_WALK,
		S_JUMP,
		S_FALL,
		S_CLIMB
	};
	enum graphics
	{
		G_STAND = 0,
		G_WALK0 = 1,
		G_WALK1 = 2,
		G_WALK2 = 3,
		G_WALK3 = 4,
		G_WALK4 = 5,
		G_WALK5 = 6,
		G_WALK6 = 7,
		G_WALK7 = 8,
		G_WALK8 = 9,
		G_CLIMB0 = 10,
		G_CLIMB1 = 11,
		G_AIR = 12
	};
	// Images per row in Player texture
	const int IRP = 13;
	// Image size
	const sf::Vector2i IMG_SIZE = sf::Vector2i(64, 64);
	const sf::Vector2f HITBOX_DIM = sf::Vector2f(30.0f, 56.0f);

	const float LEFT = -1.0f;
	const float RIGHT = 1.0f;

	const float DAMAGE_TIME = 1.25f;
	const float DMG_HI_ALPHA = 255.0f;
	const float DMG_LO_ALPHA = 100.0f;
	const float DMG_CYCLE = 0.1f;
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
	bool isDamaged() const;

	//void setHitboxWidth(float w);


	// Mutators
	void setTileMap(TileMap *m);
	void setPosition(float x, float y);
	void setState(PlayerNS::state s, float dir);
	void setTexture(sf::Texture *t);
	void setGraphics(PlayerNS::graphics g, float dir);
   // void setProjectiles(PlayerProjectiles *p);
	void setEnemyManager(EnemyManager *e);
	void setBarrierManager(BarrierManager *b);
	void damage(float amount);
	bool isOffscreen(float x, float y);
	void resetGravBomb();
	float getDir() const;

	// Methods
	bool init();
	void move(float x, float y);
	void handleInput(Input& input);
	void update(float dt);
	void draw(sf::RenderWindow& backBuffer);
    void shoot(float dir);
	void getPickup(int type, float size);
	void onContinue();

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
    PlayerProjectiles *projectiles;
	bool damaged;
	float damageTimer;
	AlphaOscillator *damageFlash;

	EventHandler *newMapHandler;
	EventHandler *resetGBHandler;
	EventHandler *continueHandler;

	bool dead;
	int selectedWeapon;
	bool hasFlame;
	bool hasFreeze;
	float health;
	float flameEnergy;
	float freezeEnergy;
	int nGravBombs;
	bool gBombReady;
	float lastDt;

	// For collision detection
	EnemyManager *enemies;
	BarrierManager *barriers;

	// Player states
	PlayerState *state;
	StandState *standing;
	WalkState *walking;
	JumpState *jumping;
	FallState *falling;
	ClimbState *climbing;
	//AirState *jumping;
	//AirState *falling;

	// Helpers
	void selectWeapon(int type);
};

#endif