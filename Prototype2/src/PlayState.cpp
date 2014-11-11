//==========================//
// PlayState.cpp            //
// Author: Matthew Stephens //
//==========================//
#include "PlayState.h"
#include "Game.h"

//================================
// Constructor
//================================
PlayState::PlayState(Game *game):
	GameState(game),
	healthbar(Health::MAX_HEALTH, Health::MAX_HEALTH)
{

}

//==============================
// Destructor
//==============================
PlayState::~PlayState()
{

}

// Methods
bool PlayState::init()
{
	tmap.setTexture(pGame->getTexture(TILES));
	tmap.loadFromFile("enemymap.txt");
	tmap.init();

	player.setTexture(pGame->getTexture(PLAYER));
	player.init();
	player.setTileMap(&tmap);
	
	enemies.init(pGame->getTexture(ENEMY));

	pickups.init(pGame->getTexture(HP));

    pProjectiles.init(pGame->getTexture(LASER));

    player.setProjectiles(&pProjectiles);

	healthbar.setTexture(pGame->getTexture(HBAR));
	healthbar.init();

	return true;
}

void PlayState::handleInput(Input *input)
{
	player.handleInput(*input);
}

void PlayState::update(float dt)
{
	player.update(dt);
	tmap.update(dt);
	enemies.update(dt);
    pProjectiles.update(dt);
	pickups.update(dt);

	pProjectiles.checkCollisions(&enemies);

	pickups.checkCollisions(&player);

	if (!player.isDamaged())
		enemies.checkCollisions(&player);
}

void PlayState::draw(sf::RenderWindow& window)
{
	tmap.draw(window);
	pProjectiles.draw(window);
	player.draw(window);
	enemies.draw(window);
	pickups.draw(window);
	healthbar.draw(window);
}