//==========================//
// PlayState.h              //
// Author: Matthew Stephens //
//==========================//
#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include "GameState.h"
#include "TileMap.h"
#include "Player.h"
#include "EnemyManager.h"
#include "PlayerProjectiles.h"
#include "EnemyProjectiles.h"
#include "HUD.h"
#include "PickupManager.h"
#include "GameWorld.h"
#include "DeathAnimator.h"
#include "EventHandler.h"
#include "Blackhole.h"
#include "BarrierManager.h"

// Forward declarations
class PlayState;

//=================================================
// PlayState EventHandler for Event::PLAYER_PICKUP
//=================================================
class PSPickupHandler : public EventHandler
{
public:
	// Constructor
	explicit PSPickupHandler(PlayState *ps): pPS(ps) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	PlayState *pPS;
};

//==========================================================
// PlayState EventHandler for Event::PLAYER_DEATH_ANIM_DONE
//==========================================================
class PSPDeathAnimDoneHandler : public EventHandler
{
public:
	// Constructor
	explicit PSPDeathAnimDoneHandler(PlayState *ps): pPS(ps) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	PlayState *pPS;
};

//============================================
// PlayState EventHandler for Event::CONTINUE
//============================================
class PSContinueHandler : public EventHandler
{
public:
	// Constructor
	explicit PSContinueHandler(PlayState *ps): pPS(ps) {}
	
	// Methods
	virtual void handleEvent(Event::Data e);

private:
	PlayState *pPS;
};

class PlayState : public GameState
{
public:
	// Constructor
	PlayState(Game *game);
	// Destructor
	virtual ~PlayState();

	// Methods
	virtual bool init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

	void pushMessage(int type);
	void setGameOver(bool go);

protected:
	EventHandler *pickupHandler;
	EventHandler *continueHandler;
	EventHandler *deathAnimDoneHandler;

	bool gameOver;
	float timer;

	Blackhole blackhole;


	GameWorld world;
	Player player;
	EnemyManager enemies;
    PlayerProjectiles pProjectiles;
	EnemyProjectiles eProjectiles;
	HUD hud;
	PickupManager pickups;
	DeathAnimator deathAnimator;
	BarrierManager barriers;
	
	static const float GAME_OVER_DELAY;
};

#endif