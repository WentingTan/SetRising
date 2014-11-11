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
#include "Boss.h"
#include "PlayerProjectiles.h"

class PlayState : public GameState
{
public:
	// Constructor
	PlayState(Game *game);
	// Destructor
	virtual ~PlayState();

	// Methods
	void spawnBoss();
	virtual bool init();
	virtual void handleInput(Input *input);
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);

protected:
	TileMap tmap;
	Boss boss;
	bool bossSpawn = false;
	Player player;
	EnemyManager enemies;
    PlayerProjectiles pProjectiles;
};

#endif