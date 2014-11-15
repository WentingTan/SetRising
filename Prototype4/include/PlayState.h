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
#include "Healthbar.h"
#include "PickupManager.h"
#include "GameWorld.h"

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

protected:
	//TileMap tmap;
	GameWorld world;
	Player player;
	EnemyManager enemies;
    PlayerProjectiles pProjectiles;
	Healthbar healthbar;
	PickupManager pickups;
	sf::Sprite background;
};

#endif